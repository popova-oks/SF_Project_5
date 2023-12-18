#pragma once
#include "ISubject.h"
#include "Messages.h"
#include "Handler_MySQL.h"

class Chat : public ISubject {
  public:
    Chat() {Messages<std::string>* messages_ = new Messages<std::string>;}
    virtual ~Chat() {if (messages_ != nullptr) {delete messages_;}};
    bool notify() override;
    void set_User(std::string &date) override;
  
  /*    
    
    void attach(IObserver* observer) override;
    void detach(IObserver* observer) override;
    
    bool is_check_Observer(IObserver* observer, std::string &login, std::string &password) override;
    IObserver* find_user(std::string login) override;

    bool is_Users() { return !all_users_.empty(); }
    bool is_Observes() { return !list_observers_.empty(); }
    void display_listObservers();
    void display_Messages_fromJSON(IObserver* user);
    bool receive_message();
  */
  private:
  /*
    std::vector<IObserver*> all_users_{};
    std::list<IObserver*> list_observers_{};
  */
    Messages<std::string>* messages_ = nullptr;
    Handler_MySQL *handler_mysql_;
};
