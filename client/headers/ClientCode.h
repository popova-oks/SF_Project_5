#pragma once
#include "User.h"
#include <iostream>

class ClientCode {
  public:
    void start();
    User* make_user(User* user);
    User* attach_toChat(User *user);
    User* detach_toChat(User *user);
    //User* login_user();
};