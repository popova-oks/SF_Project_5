#pragma once

class IObserver {
  public:
    virtual ~IObserver(){};
    virtual void update(int event) = 0;
    virtual std::string get_messFromServer() = 0;
};