
#include "observable.h"
#include "observer.h"
#include "game_data.h"
namespace model {
Observable::Observable(){
    observers={};
}

    void Observable::addObserver(Observer *observer){
        observers.insert(observer);
    }

    void Observable::notifyObservers(GameData& data)const{
        for (Observer * observer : observers)
        {
            observer->update(data);
        }
    }
    void Observable::notifyObservers(std::string messageError)const{
        for (Observer * observer : observers)
        {
            observer->update(messageError);
        }
    }
    Observable::~Observable(){}
}
