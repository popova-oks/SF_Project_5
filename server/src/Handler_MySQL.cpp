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

bool Handler_MySQL::add_User(const std::string& data) {
    std::string query_toBD1 = "INSERT users (id, name, login, password) values (default, ";
    query_toBD1.append(data);
    query_toBD1.append(")");
    query_to_BD(query_toBD1);

    // Получить логин пользователя из строки data
    int pos = data.find("', '") + 3;
    int count = data.find("', '", pos) - pos + 1;
    std::string login = data.substr(pos, count);

    // Получить данные с логином и паролем пользователя
    std::string data2 = data.substr(pos);

    // Присоединение пользователя к чату
    if(attach_User(data2)) {
        return true;
    } else {
        return false;
    }
}

bool Handler_MySQL::attach_User(const std::string& data) {
    // Получить логин пользователя из строки data
    int pos = 0;
    int count = data.find("', '", pos) + 1;
    std::string login = data.substr(pos, count);

    // Получить пароль пользователя из строки data
    pos = count + 2;
    std::string password = data.substr(pos);

    if(check_user(login, password)) {
        // Присоединение пользователя к чату
        std::string query_toBD = "UPDATE users SET attach=TRUE WHERE login=";
        query_toBD.append(login.c_str());
        query_toBD.append("AND password=");
        query_toBD.append(password.c_str());
        query_to_BD(query_toBD);
        return true;
    } else {
        return false;
    }
}

bool Handler_MySQL::detach_User(const std::string& data) {
    // Получить логин пользователя из строки data
    int pos = 0;
    int count = data.find("', '", pos) + 1;
    std::string login = data.substr(pos, count);

    // Получить пароль пользователя из строки data
    pos = count + 2;
    std::string password = data.substr(pos);

    if(check_user(login, password)) {
        // Отсоединение пользователя от чата
        std::string query_toBD = "UPDATE users SET attach=FALSE WHERE login=";
        query_toBD.append(login.c_str());
        query_toBD.append("AND password=");
        query_toBD.append(password.c_str());
        query_to_BD(query_toBD);
        return true;
    } else {
        return false;
    }
}

bool Handler_MySQL::check_user(const std::string& login, const std::string& password) {
    std::string users;
    std::string query_toBD = "SELECT login FROM users WHERE login=";
    query_toBD.append(login.c_str());
    query_toBD.append("AND password=");
    query_toBD.append(password.c_str());

    mysql_query(mysql_, query_toBD.c_str()); //Делаем запрос к таблице
    if(res_ = mysql_store_result(mysql_)) {
        MYSQL_ROW row = mysql_fetch_row(res_);
        if(row) {
            // Освобождаем память, занятую результирующей таблицей
            mysql_free_result(res_);
            return true;
        } else {
            // Освобождаем память, занятую результирующей таблицей
            mysql_free_result(res_);
            return false;
        }
    }
    return false;
}

std::string Handler_MySQL::attachedUsers() {
    std::string users;
    mysql_query(mysql_,
                "SELECT name, login FROM users WHERE attach=TRUE"); //Делаем запрос к таблице
    if(res_ = mysql_store_result(mysql_)) {
        MYSQL_ROW row; // Объявление строки результата
        while(row = mysql_fetch_row(res_)) { //Выводим все что есть в таблице через цикл
            for(int i = 0; i < mysql_num_fields(res_); i++) {
                users.append(row[i]);
                if((i + 1) % 2 == 0) {
                    users.append("\n");
                } else {
                    users.append("\t");
                }
            }
            // std::cout << std::endl;
        }
    } else {
        std::cout << "Ошибка MySql номер " << mysql_error(mysql_);
    }
    // Освобождаем память, занятую результирующей таблицей
    mysql_free_result(res_);
    return users;
}

bool Handler_MySQL::add_message(const std::string& data) {
    // Получить логин отправителя из строки data
    int pos = 0;
    int count = data.find("', '", pos) + 1;
    std::string sender = data.substr(pos, count);

    // Получить логин получателя из строки data
    pos = data.find("', '") + 3;
    count = data.find("', '", pos) - pos + 1;
    std::string reciver = data.substr(pos, count);

    std::string query_toBD = "SELECT id FROM users WHERE login=";
    query_toBD.append(sender.c_str());

    std::string id_sender;
    mysql_query(mysql_, query_toBD.c_str()); //Делаем запрос к таблице
    if(res_ = mysql_store_result(mysql_)) {
        MYSQL_ROW row;
        while(row = mysql_fetch_row(res_)) {
            for(int i = 0; i < mysql_num_fields(res_); i++) {
                id_sender.append(row[i]);
            }
        }
    } else {
        std::cout << "Ошибка MySql номер " << mysql_error(mysql_);
    }
    // Освобождаем память, занятую результирующей таблицей
    mysql_free_result(res_);

    std::string query_toBD2 = "SELECT id FROM users WHERE login=";
    query_toBD2.append(reciver.c_str());
    std::string id_reciver;
    mysql_query(mysql_, query_toBD2.c_str()); //Делаем запрос к таблице
    if(res_ = mysql_store_result(mysql_)) {
        MYSQL_ROW row;
        while(row = mysql_fetch_row(res_)) {
            for(int i = 0; i < mysql_num_fields(res_); i++) {
                id_reciver.append(row[i]);
            }
        }
    } else {
        std::cout << "Ошибка MySql номер " << mysql_error(mysql_);
    }
    // Освобождаем память, занятую результирующей таблицей
    mysql_free_result(res_);

    // Получить сщщбщение из строки data
    pos = pos + count + 2;
    std::string message = data.substr(pos);

    std::string query_toBD3 = "INSERT messages (id_sender, id_reciver, message) VALUES (";
    query_toBD3.append(id_sender.c_str());
    query_toBD3.append(", ");
    query_toBD3.append(id_reciver.c_str());
    query_toBD3.append(", ");
    query_toBD3.append(message.c_str());
    query_toBD3.append(")");
    if(query_to_BD(query_toBD3)) {
        return true;
    } else {
        return false;
    }
}

std::string Handler_MySQL::get_mess_forUser(const std::string& data) {
    std::string query_toBD = "SELECT login, messages.message FROM users JOIN messages ON "
                             "users.id = messages.id_sender "
                             "WHERE messages.id_reciver = (SELECT id FROM users WHERE login=";
    query_toBD.append(data.c_str());
    query_toBD.append(")");

    std::string mess_forUser;
    mysql_query(mysql_, query_toBD.c_str()); //Делаем запрос к таблице
    if(res_ = mysql_store_result(mysql_)) {
        MYSQL_ROW row;
        while(row = mysql_fetch_row(res_)) {
            for(int i = 0; i < mysql_num_fields(res_); i++) {
                mess_forUser.append(row[i]);
                if((i + 1) % 2 == 0) {
                    mess_forUser.append("\n");
                } else {
                    mess_forUser.append("\t");
                }
            }
        }
    } else {
        std::cout << "Ошибка MySql номер " << mysql_error(mysql_);
    }
    // Освобождаем память, занятую результирующей таблицей
    mysql_free_result(res_);
    return mess_forUser;
}

void Handler_MySQL::create_tables() {
    std::string query_toBD1 =
        "CREATE TABLE IF NOT EXISTS users(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(100) "
        "NOT "
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
bool Handler_MySQL::query_to_BD(std::string& query) {
    // Подготовка запроса для таблицы users
    if(mysql_stmt_prepare(stmt_, query.c_str(), query.length()) != 0) {
        std::cout << "Error: can't prepare statement for users table" << std::endl;
        return false;
    }
    // Выполнение подготовленного запроса для таблицы users
    if(mysql_stmt_execute(stmt_) != 0) {
        std::cout << "Error: can't execute statement for users table" << std::endl;
        return false;
    }
    return true;
}
