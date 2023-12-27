#pragma once
#include "User.h"
#include <iostream>

class ClientCode {
  public:
    void start();
  private:
    void answFromServ(User *user);
};