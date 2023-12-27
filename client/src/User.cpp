#include "../headers/User.h"
#include "../headers/sha1.h"
#include <algorithm>
#include <iostream>

User::User() { messages_ = new Messages<std::string>(); }

void User::update(int event) {
    if(event == 1) {
        std::string name;
        std::string login;
        std::string password;
        bool OnlyLettersNum = false;
        while(!OnlyLettersNum) {
            std::cout << "\nEnter only letters or numbers without using spaces or other symbols!\n";

            std::cout << "Enter your name: ";
            std::cin >> name;
            OnlyLettersNum = containsOnlyLettersNum(name);
            if(!OnlyLettersNum) {
                continue;
            }
            std::cout << "Enter your login: ";
            std::cin >> login;
            OnlyLettersNum = containsOnlyLettersNum(login);
            if(!OnlyLettersNum) {
                continue;
            }

            std::cout << "Enter your password: ";
            std::cin >> password;
            OnlyLettersNum = containsOnlyLettersNum(password);
            if(!OnlyLettersNum) {
                continue;
            }
        }
        password = sha1(password);
        std::string mess_new_user = "1'" + name + "', '" + login + "', '" + password + "'";
        if(messages_->send_message(mess_new_user) >= 0) {
            login_ = login;
        }
    } else if(event == 2 || event == 4) {
        std::string login;
        std::string password;
        bool OnlyLettersNum = false;
        while(!OnlyLettersNum) {
            std::cout << "\nEnter only letters or numbers without using spaces or other symbols!\n";

            std::cout << "Enter your login: ";
            std::cin >> login;
            OnlyLettersNum = containsOnlyLettersNum(login);
            if(!OnlyLettersNum) {
                continue;
            }
            std::cout << "Enter your password: ";
            std::cin >> password;
            OnlyLettersNum = containsOnlyLettersNum(password);
            if(!OnlyLettersNum) {
                continue;
            }
        }
        password = sha1(password);
        std::string mess_new_user;
        if(event == 2) {
            mess_new_user = "2'" + login + "', '" + password + "'";
        } else if(event == 4) {
            mess_new_user = "4'" + login + "', '" + password + "'";
        }
        if(messages_->send_message(mess_new_user) >= 0) {
            login_ = login;
        }
    } else if(event == 3) {
        char act;
        std::cout << "\nEnter an action: s - send a message, r - recive messages: ";
        std::cin >> act;

        if(act == 's') {
            std::string login;
            bool OnlyLettersNum = false;
            while(!OnlyLettersNum) {
                std::cout << "\nEnter only letters or numbers without using spaces or other "
                             "symbols!\n";
                std::cout << "\nSend to a user. Enter login : ";
                std::cin >> login;

                OnlyLettersNum = containsOnlyLettersNum(login);
                if(!OnlyLettersNum) {
                    continue;
                }
            }
            std::string message;
            std::cout << "Enter your message: ";
            std::getline(std::cin >> std::ws, message);

            std::string mess_for_user = "3'" + login_ + "', '" + login + "', '" + message + "'";
            // отсылаем сообщение серверу
            messages_->send_message(mess_for_user);
        } else if(act == 'r') {
            std::string mess = "9'" + login_ + "'";
            messages_->send_message(mess);
            std::cout << "Your messages:" << std::endl;
        }
    } else if(event == 5) {
        messages_->send_message("exit");
    } else {
        std::cout << "\nTry agan!\n";
        messages_->send_message("0");
    }
}

std::string User::get_messFromServer() {
    std::string mess = messages_->recive_message();
    return mess;
}

void User::show_attachedUser() {
    std::string users = messages_->recive_message();
    if(!users.empty()) {
        std::cout << users << std::endl;
    }
}

bool User::containsOnlyLettersNum(std::string const& str) {
    return std::all_of(str.begin(), str.end(), [](char const& c) { return std::isalnum(c); });
}