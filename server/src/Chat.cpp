#include "../headers/Chat.h"
#include <cstring>
#include <iostream>
#include <limits>

Chat::Chat() {
    Messages<std::string>* messages_ = new Messages<std::string>;
    // Подкдючаем базу данных
    handler_mysql_ = new Handler_MySQL;
}
Chat::~Chat() {
    if(messages_ != nullptr) {
        delete messages_;
    }
};

bool Chat::notify() {
    if(messages_ == nullptr) {
        messages_ = new Messages<std::string>;
    }
    std::string mess_from_client = messages_->get_messages();
    if(!mess_from_client.empty()) {
        if(strncmp(mess_from_client.c_str(), "exit", strlen(mess_from_client.c_str())) == 0) {
            return false;
        } else if(strncmp(mess_from_client.c_str(), "Error receiving data from client!",
                          strlen(mess_from_client.c_str())) != 0) {
            int event = mess_from_client.c_str()[0] - '0';
            mess_from_client.erase(0, 1);
            std::cout << mess_from_client << "\n";
            switch(event) {
            case 1: {
                if (handler_mysql_->add_User(mess_from_client))
                {
                    send_toClient("User is created!");
                } else {
                    send_toClient("Fail!");
                }
                break;
            }
            case 2: {
                if (handler_mysql_->attach_User(mess_from_client)) {
                    send_toClient("User is attached!");
                } else {
                    send_toClient("Fail!");
                }
                break;
            }
            case 3: {
                if (handler_mysql_->add_message(mess_from_client)){
                    send_toClient("Message was saved! Then click ENTER!");
                } else {
                    send_toClient("Fail!");
                }
                break;
            }
            case 4: {
                if (handler_mysql_->detach_User(mess_from_client)) {
                    send_toClient("User is detached!");
                } else {
                    send_toClient("Fail!");
                }                
                break;
            }
            case 9: {
                std::string messages = handler_mysql_->get_mess_forUser(mess_from_client);
                if (!messages.empty()) {
                    send_toClient(messages);
                } else {
                    send_toClient("Fail!");
                }
                break;
            }
            default: {
                break;
            }
            }
        }
        return true;
    }
}

void Chat::send_toClient(std::string mess)
{
    if (mess.empty()){
        mess.append("No message!");
    }
    if(!messages_->send_message(mess)) {
        std::cout << "Data sending to the client failed!" << std::endl;
    }
}

void Chat::send_listUsers_toClient() {
    std::string listUsers = handler_mysql_->attachedUsers();
    if (listUsers.empty()){
        listUsers.append("No attached users!");
    }
    if(!messages_->send_message(listUsers)) {
        std::cout << "Data sending to the client failed!" << std::endl;
    }
}
