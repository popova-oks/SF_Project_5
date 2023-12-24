#pragma once

class IObserver {
  public:
    virtual ~IObserver(){};
    virtual bool update(int event) = 0;
    virtual const std::string& get_login() const = 0;
    
    /*
    virtual const std::string& get_name() const = 0;    
    virtual const std::string& get_password() const = 0;
    virtual const int get_userID() const = 0;
    */
};