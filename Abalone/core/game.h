#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "hexboard.h"
#include "observable.h"

#define WINNER_NB_OF_BALLS 6
/*!
 * \brief Represents all the class that participates in the
 * logic of the game
 */
namespace model {

    /*!
     * \brief The Game class represents the game and it's content (rules).
     *  He knows about the Board of the game, about the two players of the game and which one of those players is currently playing.
     *
     * The balls can be moved in 6 differents directions.
     * There is two types of legit moves : in-line move and side-step move.
     *
     * The maximum amount of balls of the same color that can be moved is three.
     * If there is adjacents balls of the opposite color,
     * two balls of the same color can push one ball of the opposite color.
     * Three balls of the same color can push one or two balls of the opposite color.
     *
     *
     */
    class Game : public Observable{
        /*!
         * \brief board represents the board of the game
         */
        HexBoard board ;
        /*!
         * \brief player1 represents the one of the two players
         */
        Player player1 ;
        /*!
         * \brief player2 represents the other player
         */
        Player player2 ;
        /*!
         * \brief currentPlayer represents the player who's currrently making his move.
         */
        Player* currentPlayer ;

        public:
        /*!
             * \brief Game constructor of Game
             */
            Game();


            /*!
             * \brief reset reinitializes the game
             */
            void reset();


            /*!
             * \brief isMoveValid checks if all positions implies a valid move
             * \param inputs the given vector of positions
             * \return true if all positions can be used in a valid move, false otherwise.
             */

            void move(std::string&  input);
            /*!
             * \brief checkWinner checks if the current player has won.
             * \return true if the current player has won, false otherwise.
             */
            bool checkWinner();



            /*!
             * \brief Simple getter of the current player
             *
             */
            Player& getCurrentPlayer();

            //add doc
            /*!
             * \brief getPlayer1 simple getter of the player1
             * \return a reference to player1
             */
            Player& getPlayer1();

            /*!
             * \brief getPlayer1 simple getter of the player2
             * \return a reference to player2
             */
            Player& getPlayer2();

            /*!
             * \brief Simple getter of the State of the game
             *
             */
            std::map<HexCell,std::optional<bool>> getBoard();

    protected:
            /*!
             * \brief readPlayerMove reads the input of the player in ABA-PRO format
             * \param input the given user input in ABA-PRO format
             * \return an array of maximum three Strings depending on the length of the input
             */
            std ::vector<std::string> readPlayerMove(std::string& input);

            /*!
             * \brief isInputValid checks if all positions in a given vector are valid (inside the board).
             * \param inputs the given vector of positions
             * \return true if all positions are valid, false otherwise.
             */
            bool isInputValid(std::vector<std::string>& inputs);

            /*!
             * \brief switchPlayer switch from the current player to the adversary.
             *
             */
            void switchPlayer();


    };

}

#endif // GAME_H
