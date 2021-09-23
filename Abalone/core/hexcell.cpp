#include "hexcell.h"
#include <stdlib.h>
namespace model {

        HexCell::HexCell(  int x , int y,  int z):
            x{x+y+z==0? x: throw std::invalid_argument("The sum of the tree coordinates is not zero : " + std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) )},
            y{y},
            z{z}
            {}

        int HexCell::hexCellDistance(HexCell& other){
              return ((abs(x-other.x) + abs(y - other.y) + abs(z - other.z)) / 2);
        }
}
