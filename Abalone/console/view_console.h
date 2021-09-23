#ifndef VIEW_CONSOLE_H
#define VIEW_CONSOLE_H
#include <string>
#include <optional>
#include "player.h"
#include "observer.h"
/*!
 * \brief The View_Console class represents the console view of Abalone game .
 */
class View_Console : public model::Observer{

public:
    View_Console()=default ;

    /*!
     * \brief readInPut reads the user input and return them .
     * \return the input .
     */
    std::string readInPut();

    /*!
     * \brief printAbaloneBoard prints the board for Abalone game with 61 hexcell .
     * \param stateVector
     */
    void printAbaloneBoard( std::map<model::HexCell,std::optional<bool>>& board);


    /*!
     * \brief printPlayers prints the players and their respective score.
     * \param currentPlayer the current player
     * \param player1 the first player
     * \param player2 the second player
     */
    void printPlayers(model::Player& currentPlayer,model::Player& player1,model::Player& player2);

    /*!
     * \brief update updates the data. This method is called
     * when the move has passed.
     * \param gameData the data of the game that needs to be updated.
     */
    virtual void update(model::GameData& gameData) override;

    /*!
     * \brief update update updates the data. This method is called
     * when the move has not passed.
     * \param messageError the error message to be displayed
     */
    virtual void update(std::string messageError)override;

    /*!
     * \brief Destructor of View_Console
     */
    virtual ~View_Console() = default;
};
std::ostream & operator<<(std::ostream & out,std::optional<bool> s);
#endif // VIEW_CONSOLE_H
