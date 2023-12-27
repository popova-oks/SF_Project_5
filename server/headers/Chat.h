#pragma once
#include "ISubject.h"
#include "Messages.h"
#include "Handler_MySQL.h"

class Chat : public ISubject {
  public:
    Chat();
    virtual ~Chat();
    bool notify() override;
    void send_listUsers_toClient();
    void send_toClient(std::string mess);
  
  private:
    Messages<std::string>* messages_ = nullptr;
    Handler_MySQL *handler_mysql_;    
};
