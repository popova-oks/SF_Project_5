#include <mysql.h>
#include <iostream>
#include <string>

class Handler_MySQL {
public:
    Handler_MySQL();
    ~Handler_MySQL();
    int add_User (std::string &data);

private:
// Объекты для работы с БД
    MYSQL *mysql_;    
    MYSQL_RES *res_; // Объявление указателя на результат
    MYSQL_ROW *row_;  // Объявление строки результата
    MYSQL_STMT *stmt_; // Объявление указателя на запрос

    void create_connection_BD ();
    void query_to_BD (std::string &query);
    void create_tables ();  
};