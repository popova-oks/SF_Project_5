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

    if (chat == nullptr) {
        std::cout << "Chat not created!" << std::endl;
        return;
    }
    TCP_Server::processRequest();
    while(flag) {
        if(chat != nullptr) {
            flag = chat->notify();
            if (flag) {
                chat->display_listObservers();
                std::cout << "/nYou are attached!";
            }
        }
    }
    // закрываем сокет, завершаем соединение
    close(TCP_Server::socket_file_descriptor);

    std::cout << "\nSee you soon agan! " << std::endl;
    delete chat;
}
