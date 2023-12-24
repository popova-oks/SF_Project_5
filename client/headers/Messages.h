#pragma once
#include <string>


template <typename T> class Messages {
  public:
    Messages(){};
    ~Messages(){};
    int send_message(const T &message);
    T& recive_message();


    //nlohmann::json create_message(const std::string &sender, const std::string &receiver, T message);    
    //void save_message(const nlohmann::json &json);
    
    //void get_messages();
    //void update_JSON(const char* message);
    //const std::string& get_pathJSON () {return pathJSON_;}

  private:
    std::string mess_from_server_;
};