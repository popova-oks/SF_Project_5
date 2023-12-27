#pragma once

template <typename T> class Messages {
  public:
    Messages(){};
    ~Messages(){};    
    T get_messages();
    bool send_message(T& answ_message);
  private:
    T mess_from_client_;
};