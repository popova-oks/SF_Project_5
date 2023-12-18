#include "../headers/User.h"
#include "../headers/sha1.h"
#include <algorithm>
#include <iostream>

User::User() { 
    messages_ = new Messages<std::string>(); 
}

bool User::update(int event) {
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

            std::cout << "Enter your username: ";
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
        std::string mess_new_user = "1'"+ name + "', '" + login + "', '" + password + "'";
        if (messages_->send_message (mess_new_user) >= 0) {
            return true;
        } else {
            return false;
        }        
    } else if(event == 2) {
    } else {
        return false;
    }
}

bool User::containsOnlyLettersNum(std::string const& str) {
    return std::all_of(str.begin(), str.end(), [](char const& c) { return std::isalnum(c); });
}

/*
User* User::log_in(Chat* chat) {
    if(is_autorization_) {
        std::cout << "\nYou are login!\n";
    } else {
        chat->attach(this);
    }
    return this;
}
*/

/*
void User::exchange_messages() {
    char event;
    while(true) {
        std::cout << "\nEnter an action: s - send a message to any user, q - quit: ";
        std::cin >> event;
        if(event == 'q') {
            return;
        } else if(event == 's') {
            chat_->notify(this, event);
        } else {
            std::cout << "\nTry agan!\n";
        }
    }
}
*/

/*
void User::display_Messages() {
    chat_->display_Messages_fromJSON(this);
}
*/

/*
void User::leave_chat(Chat* chat) {
    chat->detach(this);
    set_notAutorization();
    std::cout << "\nYou are detached from the chat!\n";
}
*/

// int User::static_counter = 0;