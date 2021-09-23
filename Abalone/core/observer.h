#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>
#include <optional>
#include "game_data.h"
/*!
 * This namespace contains designs patterns used in the game Abalone .
 */
namespace model {
    class Observable;
    /*!
     * \brief The Observer class represent a view of the game
     */
    class Observer{

        public:
           /*!
            * \brief update method is called whenever the observed object is changed.
            * An application calls an Observable object's  notifyObservers method to have all the objects observers
            * notified of the change.
            * Updates the view.
            * \param observable the observable object.
            * \throw std::invalid_argument if the parameter is null.
            */
            virtual void update(GameData& gameData) = 0;
           /*!
            * \brief second update method is called whenever an error occurs.
           */
            virtual void update(std::string messageError) = 0;

            /*!
            * \brief default operator is equal
            */
            Observer & operator=(Observer &&) = default;

            Observer & operator=(const Observer &) = default;


            Observer(Observer &&) = default;

            Observer(const Observer &) = default;
            /*!
            * \brief virtual destructor of Observer
            */
            virtual ~Observer() = default;

    protected:

        /*!
         * \brief Constructeur protégé pour éviter l'instanciation
         *        hors héritage.
         *
         * Le destructeur virtuel par défaut a des effets en cascade.
         *
         */
        Observer() = default;
    };

}

#endif // OBSERVER_H
