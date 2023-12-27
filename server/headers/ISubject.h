#pragma once
#include <string>

class ISubject {
  public:
    virtual ~ISubject(){};
    virtual bool notify() = 0;
   };