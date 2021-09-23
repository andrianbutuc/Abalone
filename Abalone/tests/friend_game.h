#ifndef FRIEND_GAME_H
#define FRIEND_GAME_H
#include "game.h"

namespace model {

/*!
 * \brief The FriendGame class represents a class used to test private methods from Game.
 */
    class FriendGame : public Game {



    public:

        inline FriendGame();

        std ::vector<std::string> testReadPlayerMove(std::string& input);

        bool testIsInputValid(std::vector<std::string>& inputs);

        void testSwitchPlayer();



    };

    FriendGame:: FriendGame(){}

    std ::vector<std::string> FriendGame::testReadPlayerMove(std::string& input){
        return readPlayerMove(input);
    }

    bool FriendGame::testIsInputValid(std::vector<std::string>& inputs){
        return isInputValid(inputs);
    }

    void FriendGame::testSwitchPlayer(){
        switchPlayer();
    }


}



#endif // FRIEND_GAME_H
