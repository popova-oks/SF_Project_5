#include <iostream>
#include <mysql.h>
#include <string>

class Handler_MySQL {
  public:
    Handler_MySQL();
    ~Handler_MySQL();
    bool add_User(const std::string& data);
    bool attach_User(const std::string& data);
    bool detach_User(const std::string& data);
    bool add_message(const std::string& data);
  
    std::string attachedUsers();
    std::string get_mess_forUser(const std::string &data);
  private:
    // Объекты для работы с БД
    MYSQL* mysql_;
    MYSQL_RES* res_ = nullptr; // Объявление указателя на результат
    MYSQL_STMT* stmt_;         // Объявление указателя на запрос

    void create_connection_BD();
    bool query_to_BD(std::string& query);
    void create_tables();
    bool check_user(const std::string& login, const std::string& password);
};