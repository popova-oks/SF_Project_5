#include "../headers/ClientCode.h"
#include "../headers/ConnectionTCP.h"
#include "../headers/Messages.h"
#include "../headers/User.h"

#include <algorithm>
#include <exception>
#include <string>

void ClientCode::start() {
    std::cin.exceptions(std::istream::failbit);
    User* user = nullptr;
    bool flag = true;

    while(flag) {
        if(user == nullptr) {
            std::cout << "\nNo current User";
        } else {
            std::cout << "\nThe current user:";
                     // << "\nname - " << user->get_name() << "\nlogin - " << user->get_login()
                      //<< "\nuser_ID - " << user->get_userID();
        }
        std::cout << "\n\nSelect an action:" << std::endl;
        std::cout << "1 - registration, 2 - log in the chat,";
        std::cout << "\n3 - send messages, 4 - exit the chat,  5 - quit from the program: ";
        char ch;
        std::cin >> ch;

        switch(ch) {
        case '1': {
            user = make_user();
            if(user != nullptr) {
                std::cout << "\nUser was created!";
                //user->display_Messages();

            }
            break;
        }
        /*
        case '2': {
            chat->display_listObservers();
            if(chat->is_Users()) {
                user = login_user(chat);
                if(user != nullptr) {
                    user->display_Messages();
                }
            } else {
                std::cout << "\nUsers were not found!\nYou'll need to register in the chat!\n";
            }
            break;
        }
        case '3': {
            chat->display_listObservers();
            if(user == nullptr) {
                std::cout << "\nYou need to log in!";
            } else {
                if(chat->is_Observes()) {
                    user->exchange_messages();
                } else {
                    std::cout << "\nNo authorized users!\n";
                }
            }
            break;
        }
        case '4': {
            if(user == nullptr) {
                std::cout << "\nYou need to log in!";
            } else {
                user->leave_chat(chat);
                user = nullptr;
            }
            break;
        }
        */
        case '5': {
            flag = false;
            if (user != nullptr) {                
            //закрыть сокет на сервере!!! Послать сообщение exit
            //user->leave_chat(chat);
            //delete user;
            //user = nullptr;
            }
            break;
        }
        default: {
            std::cout << "\nTry agan.";
            break;
        }
        }
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
    std::cout << "\nSee you soon agan! " << std::endl;
}

User* ClientCode::make_user() {
    try {
        User* user = new User;
        if(user->update(1)) {
            return user;
        } else {
            delete user;
            return nullptr;
        }
    } catch(const std::istream::failure& ex) {
        std::cerr << "Failed to input: " << ex.what() << "\n";
    } catch(...) {
        std::cerr << "Some other exception\n";
    }
}

/*
User* ClientCode::login_user() {
    std::cin.clear();
    std::cin.ignore(32767, '\n');

    std::string login;
    std::cout << "\nEnter your login: ";
    std::cin >> login;

    std::string password;
    std::cout << "Enter your password: ";
    std::cin >> password;
    password = sha1(password);

    User* user = dynamic_cast<User*>(chat->find_user(login));
    if(user == nullptr) {
        std::cout << "\nSuch user wasn't found! You'll need to register in the chat!\n";
        return nullptr;
    } else {
        if(chat->is_check_Observer(user, login, password)) {
            return user->log_in(chat);
        } else {
            std::cout << "\nTry again!\n ";
            return nullptr;
        }
    }
}
*/
