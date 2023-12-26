#include "../headers/ClientCode.h"
#include "../headers/ConnectionTCP.h"
#include <exception>

void ClientCode::start() {
    std::cin.exceptions(std::istream::failbit);

    Chat* chat = nullptr;
    try {
        chat = new Chat();
    } catch(const std::bad_alloc& ex) {
        std::cout << "Allocation failed: " << ex.what() << '\n';
    }
    bool flag = true;

    if(chat == nullptr) {
        std::cout << "Chat not created!" << std::endl;
        return;
    }
    TCP_Server::processRequest();
    TCP_Server::connection = accept(TCP_Server::socket_file_descriptor,
                                    (struct sockaddr*)&TCP_Server::client, &TCP_Server::length);
    if(TCP_Server::connection == -1) {
        std::cout << "Server is unable to accept the data from client!" << std::endl;
        flag = false;
    }
    while(flag) {
        if(chat != nullptr) {
            if(TCP_Server::connection != -1) {
                chat->send_listUsers_toClient();
                flag = chat->notify();
            }
        }
    }
    // закрываем сокет, завершаем соединение
    close(TCP_Server::socket_file_descriptor);

    std::cout << "\nSee you soon agan! " << std::endl;
    delete chat;
}
