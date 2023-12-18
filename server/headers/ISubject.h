#pragma once
#include <string>

class ISubject {
  public:
    virtual ~ISubject(){};
    virtual bool notify() = 0;
    virtual void set_User(std::string &date) = 0;
    /*
    
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;    
    virtual bool is_check_Observer(IObserver* observer, std::string &login,
                                   std::string &password) = 0;
    virtual IObserver* find_user(std::string login) = 0;
    */
   };