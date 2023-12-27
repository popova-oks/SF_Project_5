#pragma once
#include "User.h"
#include <iostream>

class ClientCode {
  public:
    void start();
  private:
    //void make_user(User* user);
    //void attach_toChat(User *user);
    //void detach_toChat(User *user);
    void answFromServ(User *user);
};