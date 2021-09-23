#include "player.h"
#include <iostream>

namespace model {

    Player::Player(std::optional<bool> state):
        nbBallsOut{0},
        state{ !state.has_value() ? throw std::invalid_argument("Invalide state "): state}
    {}

    unsigned Player::getNbBallsOut(){
        return nbBallsOut;
    }

    std::optional<bool>& Player::getState(){
        return state;
    }

    void Player::addBallOut(){
        nbBallsOut++;
    }
}
