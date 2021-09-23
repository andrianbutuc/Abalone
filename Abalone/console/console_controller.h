#ifndef CONSOLE_CONTROLLER_H
#define CONSOLE_CONTROLLER_H
#include "view_console.h"
#include "game.h"
/*!
 * \brief The Controller class is the controller of game Abalone (console version)
 */
class Controller{
    /*!
     * \brief console a View_Console .
     */
    View_Console * console ;

    /*!
     * \brief game a Game ;
     */
    model::Game * game ;

    public:
    /*!
     * \brief Controller constructor.
     * \param view a View_Console.
     * \param game a Game.
     */
    Controller(View_Console* view,model::Game* game );

    /*!
     * \brief play starts the game until one of the players had won .
     */
    void play();
};

#endif // CONSOLE_CONTROLLER_H
