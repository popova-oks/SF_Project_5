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

    // открываем сокет клиента, создаем соединение с сервером
    TCP_Client::processMessage();
    user = new User;

    while(flag) {
        std::cout << "\nAttached users:" << std::endl;
        user->show_attachedUser();

        if(user->get_login().empty()) {
            std::cout << "No current user!" << std::endl;
        } else {
            std::cout << "The current user: " << user->get_login();
            // << "\nname - " << user->get_name() << "\nlogin - " << user->get_login()
            //<< "\nuser_ID - " << user->get_userID();
        }
        std::cout << "\n\nSelect an action:" << std::endl;
        std::cout << "1 - registration, 2 - attach in the chat,";
        std::cout
            << "\n3 - send or recive messages, 4 - exit the chat,  5 - quit from the program: ";
        char ch;
        std::cin >> ch;

        switch(ch) {
        case '1': {
            user->update(1);
            // user->show_messFromServer();
            answFromServ(user);
            break;
        }
        case '2': {
            user->update(2);
            // user->show_messFromServer();
            answFromServ(user);
            break;
        }
        case '3': {
            if(!user->get_login().empty()) {
                user->update(3);
                answFromServ(user);
            } else {
                user->update(0);
            }
            break;
        }
        case '4': {
            user->update(4);
            // user->show_messFromServer();
            std::string answ = user->get_messFromServer();
            if(answ != "Fail!") {
                user->set_empty_login();
            }
            std::cout << answ << std::endl;
            break;
        }
        case '5': {
            flag = false;
            if(user != nullptr) {
                //закрыть сокет на сервере!!! Послать сообщение exit
                user->update(5);
                delete user;
                user = nullptr;
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
    //закрываем сокет, завершаем соединение
    close(TCP_Client::socket_file_descriptor);
    std::cout << "\nSee you soon agan! " << std::endl;
}

/*
void ClientCode::make_user(User* user) {
    if(user->update(1)) {
        return user;
    } else {
        return nullptr;
    }
}

void ClientCode::attach_toChat(User* user) {
    if(user->update(2)) {
        return user;
    } else {
        return nullptr;
    }
}

void ClientCode::detach_toChat(User* user) {
    if(user->update(4)) {
        return user;
    } else {
        return nullptr;
    }
}
*/

void ClientCode::answFromServ(User* user) {
    std::string answ = user->get_messFromServer();
    if(answ == "Fail!") {
        user->set_empty_login();
    }
    std::cout << answ << std::endl;
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
