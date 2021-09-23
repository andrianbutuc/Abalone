#include "gui_controller.h"
#include <QApplication>
#include <QMessageBox>

Gui_Controller::Gui_Controller(MainWindow* gui,model::Game* game):gui{gui},game{game}
{}
void Gui_Controller::play(){
        model::Player* currentPlayer = &game->getCurrentPlayer();
        game->move(gui->getMove());
        gui->clear_move();
        if(currentPlayer->getNbBallsOut()==WINNER_NB_OF_BALLS){
            displayPopup(currentPlayer);
        }
}

void Gui_Controller::reset(){
    game->reset();
    model::GameData data {game->getBoard(),game->getCurrentPlayer(),game->getPlayer1(),game->getPlayer2()};
    gui->update(data);

}

void Gui_Controller::exit(){
    QApplication::exit();
}

void Gui_Controller::displayPopup(model::Player* winner){
    QMessageBox msgBox;
    msgBox.setWindowTitle("WINNER WINNER CHICKEN DINNER");
    msgBox.setText(QString("Félicitations la partie a été gagnée par le joueur de couleur : ") +(winner->getState().value()?"White":"Black") );
    msgBox.setInformativeText("Voulez vous rejouer ou quitter le jeu ?");
    msgBox.setStandardButtons(QMessageBox::Reset | QMessageBox::Close );

    int ret = msgBox.exec();
    switch (ret) {
       case QMessageBox::Reset:
           reset();
           break;
       case QMessageBox::Close:
           exit();
           break;
     }
}
