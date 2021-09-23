#ifndef HEXCELL_H
#define HEXCELL_H
#include <iostream>
#include <algorithm>
#include <utility>
/*!
 * \brief Represents all the class that participates in the
 * logic of the game
 */
namespace model {

/*!
 * \brief The HexCell class represent a cell in the game board.
 *  A cell have 3 coordonates immutable (x,y,z).
 *  The sum of 3 coordonates is zero.
 */

    class HexCell {

        /*!
         * \brief This number represent x coordonate .
         * This number is immutable.
         */
         int x ;

        /*!
         * \brief This number represent y coordonate .
         * This number is immutable.
         */
         int y ;

        /*!
         * \brief This number represent z coordonate .
         * This number is immutable.
         */
         int z ;
    public:
        /*!
         * \brief Constructor.
         *  The sum of coordonates is equal with zero.
         *
         * \param x an integer, the x coordonate.
         * \param y an integer, the y coordonate.
         * \param z an integer, the z coordonate.
         *
         * \throw std::invalid_argument if the sum of the three coordinates is not zero
         */
        HexCell (int x ,int y,int z);

        /*!
         * \brief Calculates the distance between this and \ref other .
         * \param other a Cell in the board .
         * \return the distance between two cells .
         */
        int hexCellDistance(HexCell& other);

        /*!
         * \brief Simple getter of the x coordinate of an HexCell
         * \return x, the x coordinate of an HexCell
         */
        inline int getX()const;
        /*!
         * \brief Simple getter of the y coordinate of an HexCell
         * \return y, the y coordinate of an HexCell
         */
        inline int getY()const;
        /*!
         * \brief Simple getter of the z coordinate of an HexCell
         * \return z, the z coordinate of an HexCell
         */
        inline int getZ()const;

        /*!
         * \brief Operator is less
         * \param other the other cell
         * \return true if the cell is smaller than the other cell, false otherwise.
         */
        inline bool operator<(const HexCell& other) const ;

        /*!
         * \brief Operator is equal
         * \param other the other cell
         * \return true if the cell is equal to the other cell, false otherwise.
         */
        inline HexCell& operator=(const HexCell& other) = default ;

        /*!
         * \brief Operator substract
         * \param other the other cell
         * \return the result HexCell of a substraction between the HexCell and the other HexCell
         */
        inline HexCell operator-(const HexCell& other)const;

        /*!
         * \brief HexCell toString
         * \return a string with the coordinates of an HexCell in a defined format
         */
        inline std::string toString();
    };

    /*!
     * \brief Tests equality between 2 cellls.
     * \param a first cell.
     * \param b second cell.
     * \return true if the cells are equals ,false otherwise.
     */
    inline bool operator == (const HexCell& a,const HexCell& b);

    /*!
     * \brief Tests difference between 2 cells.
     * \param a first cell.
     * \param b second cell.
     * \return true if the cells are differents ,false otherwise.
     */
    inline bool operator != (HexCell& a, HexCell& b);

    /*!
     * \brief Adds two cells.
     * \param a first cell.
     * \param b second cell.
     * \return a new cell that represent the addition.
     */
    inline HexCell operator + (HexCell& a, HexCell& b);

    /*!
     * \brief Stream injection operator, used to display in an output stream.
     * \param out a given stream.
     * \param hexCell a given HexCell.
     * \return an output stream.
     */
    inline std::ostream & operator<<(std::ostream & out,HexCell& hexCell);

    bool HexCell::operator<(const HexCell& other) const {
        if(y>other.y){
            return true;
        }else if(y < other.y){
            return false;
        }else {
            return x < other.x && z > other.z;
        }
    }

    bool operator==(const HexCell& a,const HexCell& b){
        return a.getX()==b.getX() && a.getY()==b.getY() && a.getZ()==b.getZ();
    }

    bool operator!=(HexCell& a, HexCell& b){
        return !(a==b);
    }

    HexCell operator+(HexCell& a, HexCell& b){
        return HexCell(a.getX()+b.getX(),a.getY()+b.getY(),a.getZ()+b.getZ());
    }

    HexCell HexCell::operator-(const HexCell& other)const{
        return HexCell(x-other.x,y-other.y,z-other.z);
    }

    int HexCell::getX()const{
        return x;
    }
    int HexCell::getY()const{
        return y;
    }
    int HexCell::getZ()const{
        return z;
    }

    std::string HexCell::toString(){
        return "X : "+ std::to_string(x)+ " Y : "+ std::to_string(y) + " Z : "+ std::to_string(z);
    }
    std::ostream & operator<<(std::ostream & out,HexCell& hexCell){
        out<<hexCell.toString();
        return out;
    }
}
#endif // HEXCELL_H
