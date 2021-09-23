#ifndef PLAYER_H
#define PLAYER_H
#include <optional>

/*!
 * \brief Represents all the class that participates in the
 * logic of the game
 */
namespace model {

/*!
 * \brief The Player class represent the Players of the game
 */
class Player{

    /*!
     * \brief nbBallsOut represents the number of balls of the opposite player that have been ejected
     * from the board
     */
    unsigned nbBallsOut ;

    /*!
     * \brief state represent the color of the balls assigned to a player
     */
    std::optional<bool> state ;

    public:
    /*!
         * \brief Player constructor of a Player
         * \param state the color of the balls to assign to the Player
         */
        Player(std::optional<bool> state);

        /*!
        * \brief getNbBallsOut simple getter of nbBallsOut
        * \return the number of balls of the opposite player that have been ejected
        * from the board
        */
       unsigned getNbBallsOut();
       /*!
        * \brief getState simple getter of the state of a player
        * \return the state of the player
        */
       std::optional<bool>& getState();


       /*!
        * \brief addBallOut increments the number of ball of the opposite player that have been ejected
        * from the board
        */
       void addBallOut();

       Player & operator=(const Player & other)  = default;

       /*!
        * \brief Tests equality between 2 players
        * \param a first player.
        * \param b second player.
        * \return true if the players are the same ,false otherwise.
        */
       inline bool operator == (const Player& other);




};

    bool Player::operator == (const Player& other){
        return state.value() == other.state.value();
    }
}
#endif // PLAYER_H
