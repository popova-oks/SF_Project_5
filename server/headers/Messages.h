#pragma once

template <typename T> class Messages {
  public:
    Messages(){};
    ~Messages(){};    
    T get_messages();
    //nlohmann::json create_message(const std::string &sender, const std::string &receiver, T message);    
    //void save_message(const nlohmann::json &json);
    //void send_message(const nlohmann::json &json);
    
    //void update_JSON(const char* message);
    //const std::string& get_pathJSON () {return pathJSON_;}
  private:
    //std::string pathJSON_;
    T mess_from_client_;
};