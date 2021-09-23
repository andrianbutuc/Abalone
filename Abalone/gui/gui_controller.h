#ifndef GUI_CONTROLLER_H
#define GUI_CONTROLLER_H
#include "mainwindow.h"
#include "game.h"

/*!
 * \brief The Gui_Controller class is the controller of the game Abalone (GUI version)
 */
class Gui_Controller:public QObject{

    Q_OBJECT

    /*!
     * \brief gui a graphical-user-interface typed View
     */
    MainWindow* gui ;

    /*!
     * \brief game a Game
     */
    model::Game* game ;
public:

    /*!
     * \brief Controller constructor.
     * \param gui a graphical-user-interface typed View
     * \param game a Game.
     */
    Gui_Controller(MainWindow * gui,model::Game* game);

    /*!
     * \brief play starts the game until one of the players has won .
     */
    void play();

    /*!
     * \brief reset restarts the game if the user decide to restart the game when prompted
     */
    void reset();

private:

    /*!
     * \brief exit quits the game if the user decide to quit the game when prompted
     */
    void exit();

    /*!
     * \brief displayPopup asks the user at the end of a game if he wants to start a new game or leave the game.
     */
    void displayPopup(model::Player* winner);
};
#endif // GUI_CONTROLLER_H
