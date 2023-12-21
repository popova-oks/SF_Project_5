#include "../headers/Handler_MySQL.h"

Handler_MySQL::Handler_MySQL() : mysql_(mysql_init(nullptr)), res_(nullptr), stmt_(nullptr) {
    create_connection_BD();
}

Handler_MySQL::~Handler_MySQL() {
    // Закрываем соединение с сервером базы данных
    mysql_close(mysql_);
}

void Handler_MySQL::create_connection_BD() {
    
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
    std::string query_toBD1 = "INSERT users (id, name, login, password) values (default, ";
    query_toBD1.append(data);
    query_toBD1.append(")");
    query_to_BD(query_toBD1);

    // Получить логин пользователя из строки data
    int pos = data.find("', '") + 4;
    int count = data.find("', '", pos) - pos;
    std::string login = data.substr(pos, count);

    // Присоединение пользователя к чату
    std::string query_toBD2 = "UPDATE users SET attach=TRUE WHERE login='";
    query_toBD2.append(login.c_str());
    query_toBD2.append("'");
    query_to_BD(query_toBD2);
    return 0;
}

void Handler_MySQL::show_attachedUsers() {
    mysql_query(mysql_, "SELECT * FROM users");     //Делаем запрос к таблице                                                    
    if(res_ = mysql_store_result(mysql_)) {
        MYSQL_ROW row;                              // Объявление строки результата
        while(row = mysql_fetch_row(res_)) {        //Выводим все что есть в таблице через цикл
            for(int i = 0; i < mysql_num_fields(res_); i++) {
                std::cout << row[i] << "  ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Ошибка MySql номер " << mysql_error(mysql_);
    }
    // Освобождаем память, занятую результирующей таблицей
    mysql_free_result(res_);
}

void Handler_MySQL::create_tables() {
    std::string query_toBD1 =
        "CREATE TABLE IF NOT EXISTS users(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(100) NOT "
        "NULL, login VARCHAR(100) UNIQUE NOT NULL, password VARCHAR(100) NOT NULL, "
        "attach BOOLEAN DEFAULT(FALSE) NOT NULL)";

    query_to_BD(query_toBD1);

    std::string query_toBD2 =
        "CREATE TABLE IF NOT EXISTS messages(id INT AUTO_INCREMENT PRIMARY "
        "KEY, id_reciver INT NOT NULL, id_sender INT NOT NULL, message VARCHAR(100))";
    query_to_BD(query_toBD2);

    std::string query_toBD3 =
        "ALTER TABLE messages ADD FOREIGN KEY (id_reciver) REFERENCES users(id)";
    query_to_BD(query_toBD3);
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

bool Handler_MySQL::check_user(std::string& data)
{
    mysql_query(mysql_, "SELECT * FROM users");     //Делаем запрос к таблице                                                    
    if(res_ = mysql_store_result(mysql_)) {





        MYSQL_ROW row;                              // Объявление строки результата
        while(row = mysql_fetch_row(res_)) {        //Выводим все что есть в таблице через цикл
            for(int i = 0; i < mysql_num_fields(res_); i++) {
                std::cout << row[i] << "  ";
            }
            std::cout << std::endl;
        }
    } else
        std::cout << "Ошибка MySql номер " << mysql_error(mysql_);
}