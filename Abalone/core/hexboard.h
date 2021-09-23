#ifndef HEXBOARD_H
#define HEXBOARD_H
#include <map>
#include <vector>
#include "hexcell.h"
#include <string>
#include <optional>
#define LAST_LINE 'I'
#define LAST_COLUMN '9'
/*!
 * \brief Represents all the class that participates in the
 * logic of the game
 */
namespace model {

/*!
 * \brief The Board class represents the board of
 * the game.
 *  A board has 61 Cells. At the start of the game the board
 * contains 14 white balls and 14 black balls.
 *
 */


class HexBoard {

    protected:
    /*!
    * \brief boardRadius represent the radius of the board.
    */
     int boardRadius ;

    /*!
    * \brief boardPositions Represents the positions of the balls on the board.
    * HexCell reprensent a position and State represents the fact that there
    * is a black ball, a white ball or the Cell is empty.
    */
    std::map<HexCell,std::optional<bool>> boardPositions;

    /*!
    * \brief cellDirection contains the HexCells that can be summed with a starting position
    * to calculate the position of the next HexCell in that direction.
    */
    std::vector<HexCell> cellDirection;


    public:
        /*!
         * \brief the constructor for Board
         * \param radius the radius of the board
         * \throw std::invalid_argument if the radius is negative
         */
        HexBoard(const int radius = 4);

        /*!
         * \brief getHexCellState determine the state of HexCell using the ABA-PRO formatted String .
         * \param input the given ABA-PRO formatted String .
         * \return the state of HexCell using the ABA-PRO formatted String .
         * \throw std::invalid_argument if the string is not valid
         */
        std::optional<bool>& getHexCellState(std::string& input);

        /*!
         * \brief move moves the balls on the board according to a given input
         * \param input the given input represented by an array of ABA-PRO formatted String
         * \return true if one ball has been ejected from the board during that move,
         * false otherwise.
         * \throw std::invalid_argument if the move is invalid.
         */
        bool move(std::vector<std::string>& input,std::optional<bool>& currentState);


        /*!
         * \brief getStateVector getter for the states of the board
         * \return the states of the board
         */
         std::map<HexCell,std::optional<bool>> getHexBoard();

        /*!
         * \brief isValidMove checks if a given move is valid
         * \param input the inputs of the move, in ABA-PRO format
         * \return true if the move respects the rules of the game, false otherwise.
         */
        bool isValidMove(std::vector<std::string>& input);


        protected:
        /*!
         * \brief abaProToHexCell Format an ABA-PRO formatted String to a HexCell
         * \param input the given ABA-PRO formatted String
         * \return the HexCell created by formatting the ABA-PRO formatted String
         */
        HexCell abaProToHexCell(std::string& input);


        /*!
         * \brief inLineMove executes an in-line move, return true if one ball has been ejected from the board during that move.
         * \param startHexCell the starting HexCell of the group of balls involved in the in-line move.
         * \param arrivalHexCell the arrival destination of the ball that was on the starting HexCell
         * \return true if one ball has been ejected from the board during that move, false otherwise.
         * \throw std::invalid_argument if the move is invalid
         */
        bool inLineMove(HexCell& startHexCell ,HexCell& arrivalHexCell);


        /*!
         * \brief sideStepMove executes a side-step move.
         * \param firstHexCell the first HexCell of the group of balls involved in the side-step move.
         * \param lastHexCell the last HexCell of the group of balls involved in the side-step move.
         * \param arrivalHexCell the arrival destination of the ball that was on the first HexCell of the group of balls.
         * \throw std::invalid_argument if the move is invalid
         */
        void sideStepMove(HexCell& firstHexCell,HexCell& lastHexCell,HexCell& arrivalHexCell);


        /*!
         * \brief isInside checks if an HexCell is inside the HexBoard
         * \param toCheck the given HexCell
         * \return true if the HexCell is inside the board, false otherwise.
         */
        bool isInside(HexCell& toCheck);


        /*!
         * \brief isEmpty checks if a HexCell is empty or contains a ball
         * \param position the position of the HexCell that will be checked
         * \return true if the given position does not contain a ball, false otherwise (if it contains a black or white ball)
         */
        bool isEmpty(const HexCell& position);

        /*!
         * \brief changePosition moves the balls in the given direction if the arrival HexCells are free. It is used in sideStep move method.
         * \param cells vector of the cells that need to be processed.
         * \param direction the given direction
         * \throws std::invalid_argument if the arrival HexCells are not free.
         */
        void changePosition(std::vector<HexCell>& cells, unsigned direction);

        /*!
         * \brief isAbaProValid checks if a given ABA-PRO formatted String can be converted
         * in tri-dimensional coordinate system to create a HexCell with those coordinates.
         * \param abaPro the given ABA-PRO formatted String .
         * \return true if the ABA-PRO formatted String can be formatted in 3D coordinate system,
         * false otherwise.
         */
        bool isAbaProValid(std::string& abaPro);

        /*!
         * \brief determineDirection calculates and returns the index necessary to acces the HexCell from vector cellDirection
         * to add to move in HexBoard from a HexCell to another HexCell .
         * \param from a start HexCell .
         * \param to the arrival HexCell .
         * \return the index necessary to acces the HexCell from vector cellDirection to add to move in HexBoard .
         * \throw std::invalid_argument if the distance is too great.
         */
        int determineDirection(HexCell& from ,HexCell& to);

        /*!
         * \brief nextHexCell gives the next HexCell of a given HexCell in a given direction
         * \param currentHexCell the given HexCell
         * \param direction the given direction represented by an unsigned int
         * \return the next HexCell of the given HexCell in the given direction
         * \throw std::invalid_argument if the HexCell is not inside the board or
         *  if the direction is uknown
         */
        HexCell nextHexCell(HexCell& currentHexCell,unsigned direction);

        /*!
         * \brief countHexCells counts adjacents hexcells of a given state in a given direction
         * \param firstHexCell the first HexCell that need to be counted
         * \param direction the given direction represented by an unsigned int
         * \param state the given state
         * \return the number of adjacents hexcells of the state in the given direction
         * \throw std::invalid_argument if the HexCell is not inside the board or
         *  if the direction is uknown
         */
        int countHexCells(HexCell& firstHexCell ,unsigned direction,std::optional<bool>& state);



};

    char toString(std::optional<bool> state);
}
#endif // HEXBOARD_H
