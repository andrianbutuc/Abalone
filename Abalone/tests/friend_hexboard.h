#ifndef FRIEND_HEXBOARD_H
#define FRIEND_HEXBOARD_H
#include "hexboard.h"


namespace model {

/*!
 * \brief The FriendHexBoard class represents is a class used to test private methods from HexBoard.
 */
    class FriendHexBoard : public HexBoard {


    public:

        inline FriendHexBoard();

        inline model::HexCell testAbaProToHexCell(std::string& input);

        inline bool testinLineMove( model::HexCell& startHexCell , model::HexCell& arrivalHexCell);

        inline void testsideStepMove( model::HexCell& firstHexCell, model::HexCell& lastHexCell, model::HexCell& arrivalHexCell);

        inline void setStateInPosition(model::HexCell hexCell ,std::optional<bool> state);

        inline void testChangePosition(std::vector<HexCell>& cells, unsigned direction);

        bool testIsInside(HexCell& toCheck);

        bool testIsEmpty(const HexCell& position);

        bool testIsAbaProValid(std::string& abaPro);

        int testDetermineDirection(HexCell& from ,HexCell& to);

        HexCell testNextHexCell(HexCell& currentHexCell,unsigned direction);

        int testCountHexCells(HexCell& firstHexCell ,unsigned direction,std::optional<bool>& state);


    };
    FriendHexBoard::FriendHexBoard(){

    }

    model::HexCell FriendHexBoard::testAbaProToHexCell(std::string& input){
        return this->abaProToHexCell(input);
    }
    bool FriendHexBoard::testinLineMove( model::HexCell& startHexCell , model::HexCell& arrivalHexCell){
        return this->inLineMove(startHexCell,arrivalHexCell);
    }
    void FriendHexBoard::testsideStepMove( model::HexCell& firstHexCell, model::HexCell& lastHexCell, model::HexCell& arrivalHexCell){
        this->sideStepMove(firstHexCell,lastHexCell,arrivalHexCell);
    }
    void FriendHexBoard::setStateInPosition(model::HexCell hexCell ,std::optional<bool> state){
        boardPositions[hexCell] =state ;
    }
    void FriendHexBoard::testChangePosition(std::vector<HexCell>& cells, unsigned direction){
        this->changePosition(cells,direction);
    }

    bool FriendHexBoard::testIsInside(HexCell& toCheck){
        return isInside(toCheck);
    }

    bool FriendHexBoard::testIsEmpty(const HexCell& position){
        return isEmpty(position);
    }

    bool FriendHexBoard::testIsAbaProValid(std::string& abaPro){
        return isAbaProValid(abaPro);
    }

    int FriendHexBoard::testDetermineDirection(HexCell& from ,HexCell& to){
        return determineDirection(from,to);
    }

    HexCell FriendHexBoard::testNextHexCell(HexCell& currentHexCell,unsigned direction){
        return nextHexCell(currentHexCell, direction);
    }

    int FriendHexBoard::testCountHexCells(HexCell& firstHexCell ,unsigned direction,std::optional<bool>& state){
        return countHexCells(firstHexCell, direction, state);
    }






}

#endif // FRIEND_HEXBOARD_H
