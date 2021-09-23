#include "game.h"
#include "game_data.h"

namespace model {

    Game::Game():board{HexBoard(4)},
                 player1(std::make_optional(true)),
                 player2(std::make_optional(false)),
                 currentPlayer{&player1}
    {}

    std::vector<std::string> Game::readPlayerMove(std::string& input){
        std ::vector<std::string> vectorResult{};
        if(input.size() == 4 || input.size()==6){
            for (unsigned i =0 ;i < input.size();i+=2 ){
                std::string inp = input.substr (i,2);
                vectorResult.push_back(inp);
            }
        }
        else{
            throw std::invalid_argument("Invalid move : input size is incorrect");
        }
        return vectorResult;
    }

    bool Game::isInputValid(std ::vector<std::string>& inputs){
        bool isValid = true;

        for (auto & in : inputs) {
            if(in.size()!= 2){
                throw std::invalid_argument("Invalid move : input size is incorrect");
            }
            if(!isalpha(in.at(0)) || !isdigit(in.at(1))){
                isValid = false;
                break;
             }
        }
        return isValid;
    }

    bool Game::checkWinner(){
        return (currentPlayer->getNbBallsOut()==WINNER_NB_OF_BALLS);
    }

    void Game::move(std::string&  input){
        try {
            std::vector<std::string> inputs = readPlayerMove(input);
            if (isInputValid(inputs)&& board.isValidMove(inputs)){
                if(board.move(inputs,currentPlayer->getState())){
                    currentPlayer->addBallOut();
                }
                switchPlayer();
                std::map<HexCell,std::optional<bool>> updatedBoard = board.getHexBoard();
                GameData date {updatedBoard,*currentPlayer,player1,player2};
                notifyObservers(date);
            }else{
                notifyObservers("not a valid input");
            }
        }  catch (std::invalid_argument& ex) {
            notifyObservers(ex.what());
        }
    }



    void Game::switchPlayer(){
        if (*currentPlayer == player1){

            currentPlayer = &player2;
        }else{
            currentPlayer = &player1;
        }
    }

    Player& Game::getCurrentPlayer(){
        return *currentPlayer;
    }
    Player& Game::getPlayer1(){
        return player1;
    }
    Player& Game::getPlayer2(){
        return player2;
    }
    std::map<HexCell,std::optional<bool>> Game::getBoard(){
        return board.getHexBoard();
    }
    void Game::reset(){
        board = HexBoard{4};
        player1 =std::make_optional(true);
        player2=std::make_optional(false);
        currentPlayer = &player1 ;
    }
}



