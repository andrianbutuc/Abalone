#ifndef GAME_DATA_H
#define GAME_DATA_H
#include <map>
#include <optional>
#include "hexcell.h"
#include "player.h"
namespace model {

/*!
 * \brief GameData represents the data of the game that needs to be displayed.
 *
 */
struct GameData{
    /*!
     * \brief state represents all the cells in the board and their respective states
     *
     */
     std::map<HexCell,std::optional<bool>> board;

    /*!
     * \brief the current player
     *
     */
    model::Player currentPlayer ;

    /*!
     * \brief firstPlayer the first player
     */
    model::Player firstPlayer ;

    /*!
     * \brief firstPlayer the second player
     */
    model::Player secondPlayer ;


    /*!
     * \brief GameData constructor for GameData
     * \param board the entire HexBoard of the game
     * \param player the current player
     * \param first the first player
     * \param second the second player
     */
    inline GameData(std::map<HexCell,std::optional<bool>> board,model::Player player,model::Player first,model::Player second);

};


GameData::GameData(std::map<HexCell,std::optional<bool>> board,model::Player player,
                   model::Player first,model::Player second):board{board},
                    currentPlayer{player},firstPlayer{first},secondPlayer{second}
{}
}
#endif // GAME_DATA_H
