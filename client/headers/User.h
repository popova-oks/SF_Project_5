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
    //void show_messFromServer();
    void show_attachedUser();

    //void display_Messages();

    const std::string& get_login() { return login_; }
    void set_empty_login() {login_.clear();}
  /*
    const std::string& get_name() const override { return name_; }
    
    const std::string& get_password() const override { return password_; }
    const int get_userID() const override { return user_ID_; }

    User* log_in(Chat* chat);
    void exchange_messages();
    void leave_chat(Chat* chat);
    

    void set_name(const std::string& name) { name_ = name; }
    void set_login(const std::string& login) { login_ = login; }
    void set_password(const std::string& password) { password_ = password; }
    void set_isAutorization() { is_autorization_ = true; }
    void set_notAutorization() { is_autorization_ = false; }
  */

  private:    
    Messages<std::string>* messages_ = nullptr;
    bool containsOnlyLettersNum(std::string const& str);
    std::string login_{};
  /*
    Chat* chat_ = nullptr;
    std::string name_{};
  
    std::string password_{};
    int user_ID_{0};
    bool is_autorization_{false};
  */
};
