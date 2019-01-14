//
// Created by ramon on 05.01.19.
//

#include "../headers/ConnectionInputHandler.h"
#include "../headers/WebMessageParser.h"
#include "../ChatMessage.h"

#define NEW_OWNER "NEW_OWNER"

// this handles straight data from socket (bufor pośredni)
// concatenate inputs until it finds 'STOP' then it parse message
// and passess it to main function for event handling
// (kiedy juz przeczyta wiadomość czyści po sobie bufor)
void ConnectionInputHandler::handleNewInput(int fd, std::string input) {
    if (this->fds_with_messages.count(fd)) {
        this->fds_with_messages[fd] += input;
    } else {
        this->fds_with_messages[fd] = input;
    }
    while (this->fds_with_messages[fd].find("STOP") != std::string::npos) { // handle whole message
        std::string data = this->fds_with_messages[fd];
        int stopIdx = data.find("STOP");
        data = data.substr(0, stopIdx+4);
        this->fds_with_messages[fd].erase(0, stopIdx+4);
        this->handleEvent(fd, this->parser.parse(data));
    }
}

// main function for event handling
// it chooses which function should be used for handling (based on if's xD)
void ConnectionInputHandler::handleEvent(int fd, std::string message) {
    rapidjson::Document d;
    d.Parse(message.c_str());
    rapidjson::Value& name = d["name"];
    rapidjson::Value& type = d["type"];
    rapidjson::Value& content = d["content"];

    auto event_name = std::string(name.GetString());
    auto event_type = std::string(type.GetString());

    if(event_type == ANSWER){
    } else if(intValue(event_type) == intValue(REQUEST)) {
        if (intValue(event_name) == intValue(NEW_USER)) {
            this->handleNewUser(content, fd);
        } else if (intValue(event_name) == intValue(NEW_ROOM)) {
            this->handleNewRoom(content, fd);
        } else if (intValue(event_name) == intValue(GET_ROOM_LIST)) {
            this->sendCurrentRoomsData(fd);
        } else if (intValue(event_name) == intValue(NEW_GAME)) {
             this->handleNewGame(content, fd);
        } else if (intValue(event_name) == intValue(JOIN_ROOM)) {
            this-> handleJoinRoom(content, fd);
        } else if (intValue(event_name) == intValue(SYN_CANVAS)) {
            this->handleCanvasSync(d, fd);
        } else if (event_name == QUIT_ROOM) {
            this->handleUserQuitRoom(content, fd);
        }
    } else if(event_type == INFO) {
        if( event_name == CHAT_MSG) {
            this->handleChatMessage(content, fd);
        }

    }
}

// sorki nie wiedzialem tego wcześniej niech jeszcze zostanie
constexpr unsigned int ConnectionInputHandler::str2int(const char* str, int h){
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

// handles new user
// adds user to data storage
void ConnectionInputHandler::handleNewUser(rapidjson::Value &name, int id) {
    User user(id, name["name"].GetString());
    this->dataStorage.addUser(user);
}

// handles new room msg
// if user type name that already exist server sends error msg that room already exists
// else add new room and send msg to all clients that new room was added
void ConnectionInputHandler::handleNewRoom(rapidjson::Value &data, int fd) {
    if (data["name"].IsString()) {
        std::string name = data["name"].GetString();
        if (this->dataStorage.doesRoomAlreadyExists(name)) {
            server->sendMessage(fd, this->parser.createErrorMessage("Room with given name already exits"));
        } else {
            RoomData roomData(name, this->dataStorage.getUserName(fd), fd, this->dataStorage.rollNewPassword());
            this->dataStorage.addRoom(roomData);
            this->dataStorage.startNewGameForRoom(name, fd);
            server->sendMessageToAllExceptOne(this->parser.createInfoMessage(NEW_ROOM, roomData), fd);
            server->sendMessage(fd, this->parser.createInfoMessage(NEW_GAME, roomData));
        }
    }
}

// handles chat messeage
// sends this message to all room users and
// checks if 'text' written on chat is current password
// if yes sens victory message that and handles victory (doc over method)
void ConnectionInputHandler::handleChatMessage(rapidjson::Value &data, int fd) {
    std::string text = data["text"].GetString();
    std::string roomName = data["currentRoom"].GetString();
    ChatMessage message(text, roomName);
    server->sendMessageToExceptOne(this->dataStorage.getRoomGuests(roomName),
            this->parser.createInfoMessage(CHAT_MSG, message), fd);
//    if(this->dataStorage.isThatPassword(roomName, text)) {
//        this->handleVictory(roomName, fd);
//    }

}

void ConnectionInputHandler::handleJoinRoom(rapidjson::Value &value, int fd) {
    std::string roomName = value["roomName"].GetString();
    if(this->dataStorage.addGuestToRoom(roomName, fd)) {
        this->server->sendMessage(fd, this->parser.createOKMessage());
    } else {
        this->server->sendMessage(fd, this->parser.createErrorMessage("Room too crowded"));
    }
}


// handles canvas sync msg
// just passes this message to all room guests
void ConnectionInputHandler::handleCanvasSync(rapidjson::Document &d, int fd) {
    d["type"].SetString(INFO);
    rapidjson::Value& content = d["content"];

    std::string roomName = content["currentRoom"].GetString();
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    std::string final = buffer.GetString();
    final = START + final + STOP;
    server->sendMessageTo(this->dataStorage.getRoomGuests(roomName), final);
}

void ConnectionInputHandler::handleVictory(std::string roomName, int fd) {
    std::string data = this->parser.createVictoryMessage(roomName, fd);
    this->server->sendMessageTo(this->dataStorage.getRoomGuests(roomName), data);
//    this->server->sendMessage(this->dataStorage.getRoomOwnerId(roomName), data);
    this->dataStorage.startNewGameForRoom(roomName, fd);
// TODO send msg that new game started
}

// when user creates new room should send new game request to initiate new game
// new password is rolled and new owner is set
// !! new game event should be sent after event creation !!
void ConnectionInputHandler::handleNewGame(rapidjson::Value &d, int fd) {
    std::string roomName = d["roomName"].GetString();
    int ownerId = d["ownerId"].GetInt(); //new room owner
    this->dataStorage.startNewGameForRoom(roomName, ownerId);
    // TODO send answer with current password
}

// sends current roomw list after get-room-list request
void ConnectionInputHandler::sendCurrentRoomsData(int fd) {
    std::string all = "[";
    int i = 0;
    for (const auto &entry: *this->dataStorage.getRooms()) {
        if(i != 0) {
            all += ',';
        }
        RoomData roomData = entry.second;
        all += roomData.toString();
        i++;
    }
    all += "]";
    server->sendMessage(fd, this->parser.createAnswerMessage(GET_ROOM_LIST, all));

}

// hash value of string i'm not sure if we need this but sometimes string with '==' does not work
size_t ConnectionInputHandler::intValue(const std::string &value) {
    return std::hash<std::string>{}(value);
}

ConnectionInputHandler::ConnectionInputHandler() = default;

ConnectionInputHandler::~ConnectionInputHandler() = default;

void ConnectionInputHandler::setServer(Server *server) {
    this->server = server;
}

void ConnectionInputHandler::handleUserQuit(int fd) {
    // sprwadzamy czy byl ownerem pokoju
    // jeżeli był ownerem i nie ma gości -> zamknij pokój
    // jeżeli był ownerem i są goście -> wybierz nowego ownera (zacznij nową gre)
    // sprawdzamy czy jest na liście gości, jeżeli tak to go usuwamy
    // usuwamy go z listy userów
    std::string userName = this->dataStorage.getUserName(fd);
    for(auto room: *this->dataStorage.getRooms()) {
        RoomData &roomData = room.second;
        if(room.second.getOwnerName() == userName) {
            if(!room.second.getGuests().empty()) {
                int newOwner = room.second.getGuests()[0];
                std::string name = this->dataStorage.getUserName(newOwner);
                room.second.setOwner(name);
                room.second.setOwnerId(newOwner);
                room.second.getGuests().erase(room.second.getGuests().begin());
                this->sendNewGameInfo(room.second, newOwner);
            } else {
                this->dataStorage.removeRoom(room.second.getName());
                break;
            }
        } else {
            room.second.removeGuest(fd);
        }
    }
    this->dataStorage.removeUser(fd);
    this->fds_with_messages.erase(fd);

}

void ConnectionInputHandler::handleUserQuitRoom(rapidjson::Value &value, int fd) {
    std::string userName = this->dataStorage.getUserName(fd);
    for(auto &room: *this->dataStorage.getRooms()) {
        RoomData &roomData = room.second;
        if(room.second.getOwnerName() == userName) {
            if(!room.second.getGuests().empty()) {
                int newOwner = room.second.getGuests()[0];
                std::string name = this->dataStorage.getUserName(newOwner);
                room.second.setOwnerId(newOwner);
                room.second.setOwner(name);
                room.second.getGuests().erase(room.second.getGuests().begin());
                this->sendNewGameInfo(room.second, fd);
            } else {
                this->dataStorage.removeRoom(room.second.getName());
                break;
            }
        } else {
            room.second.removeGuest(fd);
        }
    }
}

void ConnectionInputHandler::sendNewGameInfo(RoomData &data, int fd) {
    this->server->sendMessageTo(data.getGuests(), this->parser.createInfoMessage(NEW_GAME,data));
    this->server->sendMessage(data.getOwnerId(),this->parser.createInfoMessage(NEW_OWNER, data));
}
