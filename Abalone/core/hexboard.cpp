#include "hexboard.h"

namespace model {

    HexBoard::HexBoard(const int radius):boardRadius{radius < 1 ? throw std::invalid_argument("Invalid radius : " + std::to_string(radius)):radius},
                                         boardPositions{},
                                         cellDirection{{HexCell(1, 0, -1), HexCell(1, -1, 0), HexCell(0, -1, 1), HexCell(-1, 0, 1), HexCell(-1, 1, 0), HexCell(0, 1, -1)}}
    {
        for (int q = -boardRadius; q <= boardRadius; q++) {
            int r1 = std::max(-boardRadius, -q - boardRadius);
            int r2 = std::min(boardRadius, -q + boardRadius);
            for (int r = r1; r <= r2; r++) {
                HexCell cell{q, r, (-q-r)};
                std::optional<bool> state ;
                if(r < -2){
                    state = std::make_optional(true);
                }else if(r > 2){
                    state= std::make_optional(false);
                }else{
                    state = {} ;
                }
                if(r==2 && q<1 && q>-3){
                    state= std::make_optional(false);
                }
                if(r==-2 && q>-1 && q<3){
                    state= std::make_optional(true);
                }
                boardPositions.insert(std::pair<HexCell,std::optional<bool>>(cell,state));
            }
        }
    }

    std::map<HexCell,std::optional<bool>> HexBoard::getHexBoard(){
        return boardPositions;
    }

    bool HexBoard::isEmpty(const HexCell& position){
        return !boardPositions[position].has_value();
    }

    std::optional<bool>& HexBoard::getHexCellState(std::string& input){
        if(!isAbaProValid(input)){
            throw std::invalid_argument("ABA-PRO invalid");
        }
        HexCell tmp = abaProToHexCell(input);
        return boardPositions[tmp];
    }

    HexCell HexBoard::abaProToHexCell(std::string& input){
        int y = input.at(0)-'A'-boardRadius;
        int z =boardRadius-(input.at(1)-'1');
        return HexCell{(-y-z),y,z};
    }

    bool HexBoard::isAbaProValid(std::string& abaPro){

        if(abaPro.at(0)-LAST_LINE >0){
            return false;
        }
        if(abaPro.at(1)-LAST_COLUMN >0){
            return false;
        }
        HexCell tmp = abaProToHexCell(abaPro);

        return isInside(tmp);
    }

    bool HexBoard::isInside(HexCell& toCheck){
        std::map<HexCell,std::optional<bool>>::iterator it = boardPositions.find(toCheck);
        return it != boardPositions.end();
    }



    int HexBoard::countHexCells(HexCell& firstHexCell ,unsigned direction,std::optional<bool>& state){
        if(!isInside(firstHexCell)){
            throw std::invalid_argument("HexCell out of board : " + firstHexCell.toString());
        }
        if( direction>= cellDirection.size()){
            throw std::invalid_argument("Unknown direction : " + std::to_string(direction));
        }
        if(boardPositions[firstHexCell] != state){
            return 0;
        }

        int cpt = 1;
        HexCell nextCell = nextHexCell(firstHexCell,direction);

        while (isInside(nextCell) && boardPositions[nextCell].has_value() && boardPositions[nextCell].value() == state.value()){
            nextCell=nextHexCell(nextCell,direction);
            cpt++;
        }
        return cpt;
    }

    HexCell HexBoard::nextHexCell(HexCell& currentHexCell,unsigned direction){
        if(!isInside(currentHexCell)){
            throw std::invalid_argument("currentHexCell out of board : " + currentHexCell.toString());
        }
        if( direction>= cellDirection.size()){
            throw std::invalid_argument("Unknown direction : " + std::to_string(direction));
        }

        return  currentHexCell+cellDirection.at(direction);
    }

    bool HexBoard::isValidMove(std::vector<std::string>& input){
        bool valid = true ;

        for (std::string& position : input) {

            valid  = isAbaProValid(position);
            if(!valid){
                break;
            }
        }

        if(input.size()==2 && valid){
            HexCell first = abaProToHexCell(input.at(0));
            HexCell second = abaProToHexCell(input.at(1));
            valid = first.hexCellDistance(second) == 1 ? true : false ;

        }else if(valid){

            HexCell first = abaProToHexCell(input.at(0));
            HexCell second = abaProToHexCell(input.at(1));
            HexCell arrival = abaProToHexCell(input.at(2));

            if(first.hexCellDistance(arrival) != 1 || first.hexCellDistance(second)>2){
                valid =false ;
            }else if(first.hexCellDistance(arrival) == 1 && first.hexCellDistance(second)==2 && second.hexCellDistance(arrival) <2 ){
                valid =false ;
            }else{
                if(first.getY()==second.getY()){
                    valid = arrival.getY()!=first.getY();
                }else if(first.getZ()==second.getZ()){
                    valid = arrival.getZ()!=first.getZ();
                }else{
                    valid = arrival.getX()!=first.getX();
                }
            }
        }
        return valid;
    }

    bool HexBoard::move(std::vector<std::string>& input,std::optional<bool>& currentState){
        if(!currentState.has_value()){
            throw std::invalid_argument("Invalid current state ");
        }
        bool ballEjected = false ;
        if(input.size()>2){
            //side step move
            HexCell first =abaProToHexCell(input.at(0)) ;
            HexCell last = abaProToHexCell(input.at(1));
            HexCell arrival = abaProToHexCell(input.at(2));
            if(boardPositions[first].has_value() && boardPositions[first]==currentState && boardPositions[last].has_value() && boardPositions[last]==currentState){
                sideStepMove(first,last,arrival);
            }else{
                throw std::invalid_argument(std::string("Trying to move opposite state : ") + toString(currentState));
            }
        }else{
            //in line move
            HexCell start = abaProToHexCell(input.at(0));
            HexCell arrival = abaProToHexCell(input.at(1));
            if(boardPositions[start].has_value() && boardPositions[start]==currentState){
                ballEjected = inLineMove(start,arrival);
            }else{
                throw std::invalid_argument(std::string("Trying to move opposite state : ") + toString(currentState));
            }
        }
        return ballEjected;
    }

    int HexBoard::determineDirection(HexCell& from ,HexCell& to){
        if(from.hexCellDistance(to)>1){
            throw std::invalid_argument("Too much distance between HexCell from "+ from.toString()+ " to HexCell to "  + to.toString());
        }

        HexCell tmp = to-from;
        unsigned index =0 ;
        bool find = false ;
        while (index < cellDirection.size()&& !find) {
            if(tmp == cellDirection.at(index)){
                find = true;
            }else{
                index++;
            }
        }

        return index;
    }

    bool HexBoard::inLineMove(HexCell& startHexCell ,HexCell& arrivalHexCell){
        // 1->0
        if(boardPositions[startHexCell].has_value() && !boardPositions[arrivalHexCell].has_value()){
            boardPositions[arrivalHexCell] = boardPositions[startHexCell];
            boardPositions[startHexCell] = {};
            return false;
        }
        bool ballEjected = false ;

        int indexDirection = determineDirection(startHexCell,arrivalHexCell);
        int nbHexCell = countHexCells(startHexCell,indexDirection,boardPositions[startHexCell]);

        if(nbHexCell<4){
            HexCell directionCell = cellDirection[indexDirection];
            HexCell last = startHexCell ;
            int i = 0;
            while (i<nbHexCell){
                last = last + directionCell ;
                i++ ;
            }
            if(isInside(last) && boardPositions[last].has_value()){
                std::optional<bool> state = boardPositions[last] ;
                int nbHexCellOposite = countHexCells(last,indexDirection,state);
                if(nbHexCell>nbHexCellOposite){
                    // 2->1 , 3->2 // 3->1
                    int indexOposite = 0;
                    HexCell lastOposite = last ;
                    while (indexOposite <nbHexCellOposite){
                        lastOposite = lastOposite + directionCell ;
                        indexOposite++ ;
                    }
                    if(isInside(lastOposite)){
                        if(boardPositions[lastOposite] != boardPositions[arrivalHexCell]){
                            boardPositions[last] = boardPositions[startHexCell];
                            boardPositions[startHexCell] = {};
                            boardPositions[lastOposite] = state;
                        }else{
                            throw std::invalid_argument("apres les boules du joueur adverse il y a une boule du joueur courrant : move imposible");
                        }
                     }else{
                            boardPositions[last] = boardPositions[startHexCell];
                            boardPositions[startHexCell] = {};
                            ballEjected = true ;
                     }
                 }else{
                    throw std::invalid_argument("Vous n'etes pas dans une situation SUMITO ");
                 }
            }else{
                 if(isInside(last)){
                    boardPositions[last] = boardPositions[startHexCell];
                    boardPositions[startHexCell] = {};
                 }else{
                    throw std::invalid_argument("Ce n'est pas possible d'ejecter ses boules ");
                 }
            }
        }else {
            throw std::invalid_argument("Vous ne pouvez deplacer que maximum 3 de vos boules");
        }
        return ballEjected;
    }

    void HexBoard::sideStepMove(HexCell& firstHexCell,HexCell& lastHexCell,HexCell& arrivalHexCell){

        int distance = firstHexCell.hexCellDistance(lastHexCell);
        std::optional<bool>& state = boardPositions[firstHexCell];
        std::vector<HexCell> cells = {firstHexCell,lastHexCell};
        int indexDirection = determineDirection(firstHexCell,arrivalHexCell);

        if(state.has_value() && boardPositions[lastHexCell].has_value() && boardPositions[lastHexCell].value() == state.value()){
            if(distance==2){
                //direction to last from first
                HexCell directionCell = (firstHexCell+lastHexCell) ;
               // between is the hexcell between first and last hexcell
                HexCell between {directionCell.getX()/2,directionCell.getY()/2,directionCell.getZ()/2};
                if(boardPositions[between].has_value()&& boardPositions[between].value() == state.value()){
                    cells.push_back(between);
                    changePosition(cells,indexDirection);
                }
            }else if(distance==1){
                changePosition( cells,indexDirection);
            }
        }else{
            throw std::invalid_argument("some of the balls that you move isn't yours");
        }
    }

    char toString(std::optional<bool> state){
        if(state.has_value() && state.value()){
            return 'w';
        }else if(state.has_value() && !state.value()){
            return'b';
        }else {
            return '.';
        }
    }

    std::ostream & operator<<(std::ostream & out,std::optional<bool>  s){
        out << model::toString(s);
        return out;
    }

    void HexBoard::changePosition(std::vector<HexCell>& cells, unsigned direction){
        for(HexCell& c : cells){
            HexCell next = c+cellDirection[direction];
            if(boardPositions[c].has_value()&& !boardPositions[next].has_value()){
                boardPositions[next] = boardPositions[c];
                boardPositions[c] ={};
            }else {
                throw std::invalid_argument("you move the balls in occupied cells ");
            }
        }
    }
}
