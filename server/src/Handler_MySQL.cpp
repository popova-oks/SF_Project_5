#include "../headers/Handler_MySQL.h"

Handler_MySQL::Handler_MySQL()
    : mysql_(mysql_init(nullptr)), res_(nullptr), row_(nullptr), stmt_(nullptr) {
    create_connection_BD();
}

Handler_MySQL::~Handler_MySQL() {
    // Закрываем соединение с сервером базы данных
    mysql_close(mysql_);
}

void Handler_MySQL::create_connection_BD() {
    // Получаем дескриптор соединения
    // mysql_init(mysql_);
    if(mysql_ == nullptr) {
        // Если дескриптор не получен — выводим сообщение об ошибке
        std::cout << "Error: can't create MySQL-descriptor" << std::endl;
    }
    // Подключаемся к серверу
    if(!mysql_real_connect(mysql_, "localhost", "root", "HazovA", "project_5", NULL, NULL, 0)) {
        // Если нет возможности установить соединение с БД выводим сообщение об ошибке
        std::cout << "Error: can't connect to database " << mysql_error(mysql_) << std::endl;
    }
    // Инициализация подготовленного запроса
    stmt_ = mysql_stmt_init(mysql_);
    if(stmt_ == nullptr) {
        // Обработка ошибки
        std::cout << "Error: can't create MySQL statement" << std::endl;
        return;
    }
    // Создаем таблицы в БД
    create_tables();
}

int Handler_MySQL::add_User(std::string& data) {
    std::string query_toBD = "INSERT INTO users(id, name, login, password) values(default, ";
    query_toBD.append(data);
    query_toBD.append(")");
    mysql_query(mysql_, query_toBD.c_str());
    mysql_query(mysql_, "SELECT * FROM users"); //Делаем запрос к таблице

    //Выводим все что есть в таблице через цикл
    if(res_ = mysql_store_result(mysql_)) {
        while(*row_ = mysql_fetch_row(res_)) {
            for(int i = 0; i < mysql_num_fields(res_); i++) {
                std::cout << row_[i] << "  ";
            }
            std::cout << std::endl;
        }
    } else
        std::cout << "Ошибка MySql номер " << mysql_error(mysql_);
    return 0;
}

void Handler_MySQL::create_tables() {
    std::string query_toBD1 =
        "CREATE TABLE IF NOT EXISTS users(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(100) NOT "
        "NULL, login VARCHAR(100) NOT NULL, password VARCHAR(100) NOT NULL)";

    query_to_BD(query_toBD1);

    std::string query_toBD2 = "CREATE TABLE IF NOT EXISTS messages(id INT AUTO_INCREMENT PRIMARY "
                              "KEY, id_reciver INT NOT NULL "
                              "REFERENCES users(id), id_sender INT NOT NULL REFERENCES users(id), "
                              "message VARCHAR(100) NOT NULL)";

   query_to_BD(query_toBD2);
}

// Cоздание запроса к БД
void Handler_MySQL::query_to_BD(std::string& query) {
    // Подготовка запроса для таблицы users
    if(mysql_stmt_prepare(stmt_, query.c_str(), query.length()) != 0) {
        std::cout << "Error: can't prepare statement for users table" << std::endl;
        return;
    }

    // Выполнение подготовленного запроса для таблицы users
    if(mysql_stmt_execute(stmt_) != 0) {
        std::cout << "Error: can't execute statement for users table" << std::endl;
        return;
    }
}