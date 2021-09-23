#include "console_controller.h"

Controller::Controller(View_Console* view,model::Game* game):console{view},game{game}
{}

void Controller::play(){
    std::map<model::HexCell,std::optional<bool>> board = game->getBoard();
    console->printAbaloneBoard(board);
    console->printPlayers(game->getCurrentPlayer(), game->getPlayer1(), game->getPlayer2());
    while(!game->checkWinner()){
        std::string move = console->readInPut();
        game->move(move);
    }
}
