#pragma once
#include <string>


template <typename T> class Messages {
  public:
    Messages(){};
    ~Messages(){};
    int send_message(const T &message);
    T& recive_message();
  private:
    std::string mess_from_server_;
};