#include "catch.hpp"
#include "hexcell.h"
using namespace model;
TEST_CASE("Test hexcell instanciation"){

    SECTION("Test corect case"){
        HexCell c{1,0,-1};
        REQUIRE((c.getX()==1 && c.getY()==0 && c.getZ()==-1));
    }

    SECTION("Test wrong params"){
        REQUIRE_THROWS_AS(HexCell(1,1,1),std::invalid_argument&);
    }
}
TEST_CASE("Test hexcell overloaded operators"){

    SECTION("equality of 2 hexcells"){
        HexCell a{1,0,-1};
        HexCell b{1,0,-1};
        REQUIRE((a.getX()==b.getX() && a.getY()==b.getY() && a.getZ()==b.getZ()));
    }
    SECTION("assign operator"){
        HexCell a{1,0,-1};
        HexCell b=a;
        REQUIRE(b == a);
    }

    SECTION("adding 2 hexcells"){
        HexCell a{1,0,-1};
        HexCell b{1,0,-1};
        HexCell result = a+b ;
        HexCell expected {2,0,-2};
        REQUIRE(result == expected);
    }
    SECTION("minus operator"){
        HexCell a{2,0,-2};
        HexCell b{-1,0,1};
        HexCell result = a - b ;
        HexCell expected {3,0,-3};
        REQUIRE(result == expected);
    }
    SECTION("first less the second"){
        HexCell first{1,0,-1};
        HexCell second{1,-1,0};
        bool  result = first< second ;
        REQUIRE(result);
    }
    SECTION("different operator"){
        HexCell a{2,0,-2};
        HexCell b{-1,0,1};
        bool result = a != b ;
        REQUIRE(result);
    }
}
TEST_CASE("hexCellDistance"){
    SECTION("nomal case"){
        HexCell a{2,0,-2};
        HexCell b{1,0,-1};
        int result = a.hexCellDistance(b);
        int expected = 1 ;
        REQUIRE(result == expected);
    }
}
