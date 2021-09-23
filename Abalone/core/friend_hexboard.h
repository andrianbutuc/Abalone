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
}

#endif // FRIEND_HEXBOARD_H
