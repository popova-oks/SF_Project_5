#pragma once
#include <map>
#include <string>
#include "IObserver.h"
#include "Messages.h"

class User : public IObserver {
  public:
    User();
    virtual ~User() {}
    void update (int event) override;
    std::string get_messFromServer() override;
    void show_attachedUser();

    const std::string& get_login() { return login_; }
    void set_empty_login() {login_.clear();}

  private:    
    Messages<std::string>* messages_ = nullptr;
    bool containsOnlyLettersNum(std::string const& str);
    std::string login_{};
};
