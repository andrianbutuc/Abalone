#ifndef OBSERVABLE_H
#define OBSERVABLE_
#include <set>
#include "game_data.h"

/*!
 * \brief Represents all the class that participates in the
 * logic of the game
 */
namespace model {

class Observer;

/*!
* \brief The Observable class represents the object that will be observated by observers .
*/
class Observable{
    /*!
    * \brief observers the list of observers
    */
    protected:
        std::set<Observer *> observers ;

        /*!
         * \brief Observable constructor .
         * Creates the array of observers .
         */
        Observable();

        /*!
         * \brief notifyObservers notify all of it's observers with the a game data object .
         *
         * Each observer has its update method that will be called automatically .
         *
         * \param gameData a GameData
         */
        virtual void notifyObservers(model::GameData& gameData) const final;
        /*!
         * \brief notifyObservers notify all of its observers with an error message ;
         * Each observer has its update method that will be called automatically .
         * \param messageError a string.
         */
        virtual void notifyObservers(std::string messageError) const final;

    public:
        /*!
         * \brief addObserver Adds an observer to the set of the observers for this object ,provided that
         * if is not the same as some observer already in the set .The order in which
         * notifications will be delivered to multiple observers is not specified .
         * \param observer an observer to be added .
         * \throw std::invalid_argument if the parameter is null
         */
        virtual void addObserver(Observer* observer) final;

        Observable & operator=(Observable &&) = default;

        Observable & operator=(const Observable &) = default;

        Observable(Observable &&) = default;

        Observable(const Observable &) = default;

        virtual ~Observable() ;
    };

}

#endif // OBSERVABLE_H
