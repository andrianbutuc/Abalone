#include "catch.hpp"
#include "friend_hexboard.h"

using namespace model;
TEST_CASE("Test hexboard instanciation"){
    SECTION("positive radius"){
        REQUIRE_NOTHROW(HexBoard b {2});
    }
    SECTION("negative radius"){
        REQUIRE_THROWS_AS(HexBoard(-1),std::invalid_argument&);
    }
    SECTION("zero radius"){
        REQUIRE_THROWS_AS(HexBoard(0),std::invalid_argument&);
    }
}
TEST_CASE("isEmpty method"){
    FriendHexBoard board {};
    SECTION("isEmpty true"){
        HexCell c {-1,0,1};
        bool result = board.testIsEmpty(c);
        REQUIRE(result);
    }
    SECTION("isEmpty false"){
        HexCell b {-4,4,0};
        bool result = board.testIsEmpty(b);
        REQUIRE(result==false);
    }
}
TEST_CASE("getHexCellState method"){
    HexBoard board {4};
    SECTION("black ball"){
        std::string s = "H5";
        std::optional<bool> result = board.getHexCellState(s);
        std::optional<bool> expected = std::make_optional(false);
        REQUIRE(result==expected);

    }
    SECTION("white ball"){
        std::string s = "A1";
        std::optional<bool> result = board.getHexCellState(s);
        std::optional<bool> expected = std::make_optional(true);
        REQUIRE(result==expected);
    }
    SECTION("empty position"){
        std::string s = "E5";
        std::optional<bool> result = board.getHexCellState(s);
        std::optional<bool> expected = {};
        REQUIRE(result==expected);
    }
}

TEST_CASE("isAbaProValid method"){
    FriendHexBoard board {};
    SECTION("Invalid abaPro"){
        std::string abapro= "J1";
        bool result = board.testIsAbaProValid(abapro);
        bool expected = false ;
        REQUIRE(result==expected);
    }
    SECTION("Invalid abaPro"){
        std::string abapro= "G10";
        bool result = board.testIsAbaProValid(abapro);
        bool expected = false ;
        REQUIRE(result==expected);
    }
    SECTION("Invalid abaPro not in board "){
        std::string abapro= "G1";
        bool result = board.testIsAbaProValid(abapro);
        bool expected = false ;
        REQUIRE(result==expected);
    }
    SECTION("Valid abaPro"){
        std::string abapro= "E1";
        bool result = board.testIsAbaProValid(abapro);
        bool expected = true ;
        REQUIRE(result==expected);
    }
}

TEST_CASE("isInside method"){
    FriendHexBoard board {};
    SECTION("in board"){
        HexCell cell{-4,0,4};
        bool result = board.testIsInside(cell);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("out of board"){
        HexCell cell{-5,0,5};
        bool result = board.testIsInside(cell);
        bool expected = false ;
        REQUIRE(result== expected);
    }
}
TEST_CASE("countHexCells method"){
    FriendHexBoard board {};
    SECTION("HexCell out of board"){
        HexCell tmp{-5,0,5};
        std::optional<bool> state ={};
        REQUIRE_THROWS_AS(board.testCountHexCells(tmp,0,state),std::invalid_argument&);
    }
    SECTION("Unknown direction"){
        HexCell tmp{-4,0,4};
        std::optional<bool> state ={};
        REQUIRE_THROWS_AS(board.testCountHexCells(tmp,6,state),std::invalid_argument&);
    }
    SECTION("Unknown direction"){
        HexCell tmp{-4,0,4};
        std::optional<bool> state ={};
        REQUIRE_THROWS_AS(board.testCountHexCells(tmp,-1,state),std::invalid_argument&);
    }
    SECTION("1 hexcell"){
        HexCell tmp{-1,-3,4};
        std::optional<bool> state =std::make_optional(true);
        int nbHexCell = board.testCountHexCells(tmp,4,state);
        REQUIRE(nbHexCell==1);
    }
    SECTION("0 hexcell"){
        HexCell tmp{-3,-1,4};
        std::optional<bool> state =std::make_optional(false);
        int nbHexCell = board.testCountHexCells(tmp,4,state);
        REQUIRE(nbHexCell==0);
    }
    SECTION("1 hexcell"){
        HexCell tmp{2,-4,2};
        std::optional<bool> state =std::make_optional(true);
        int nbHexCell = board.testCountHexCells(tmp,4,state);
        REQUIRE(nbHexCell==3);
    }


}
TEST_CASE("nextHexCell method"){
    FriendHexBoard board {};
    SECTION("HexCell out of board"){
        HexCell tmp{-5,0,5};
        REQUIRE_THROWS_AS(board.testNextHexCell(tmp,4),std::invalid_argument&);
    }
    SECTION("Unknown direction"){
        HexCell tmp{-4,0,4};
        REQUIRE_THROWS_AS(board.testNextHexCell(tmp,6),std::invalid_argument&);
    }
    SECTION("Unknown direction"){
        HexCell tmp{-4,0,4};
        REQUIRE_THROWS_AS(board.testNextHexCell(tmp,-1),std::invalid_argument&);
    }
    SECTION("correct direction and in board hexcell"){
        HexCell tmp{-1,-3,4};
        HexCell next = board.testNextHexCell(tmp,4);
        HexCell expected {-2,-2,4};
        REQUIRE(next==expected);
    }
}
TEST_CASE("isValidMove method"){
    HexBoard board {4};
    //sidestepmove with 3 hexcell
    SECTION("valid 1"){
        std::vector<std::string> move{"C3","C5","D4"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid 2"){
        std::vector<std::string> move{"C3","C5","B3"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid 3"){
        std::vector<std::string> move{"C3","C5","B2"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid 4"){
        std::vector<std::string> move{"C3","C5","D3"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 1"){
        std::vector<std::string> move{"C3","C5","C2"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }

    SECTION("invalid 2"){
        std::vector<std::string> move{"C3","C5","B4"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 3"){
        std::vector<std::string> move{"C3","C5","D5"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 4"){
        std::vector<std::string> move{"C3","C5","D2"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 5"){
        std::vector<std::string> move{"C3","C5","C1"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 6"){
        std::vector<std::string> move{"C3","C5","B1"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    //sidestepmove with 2 hexcell
    SECTION("valid 1"){
        std::vector<std::string> move{"C3","C4","D4"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid 2"){
        std::vector<std::string> move{"C3","C4","B3"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid 3"){
        std::vector<std::string> move{"C3","C4","B2"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid 4"){
        std::vector<std::string> move{"C3","C4","D3"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 1"){
        std::vector<std::string> move{"C3","C4","C2"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }

    SECTION("invalid 2"){
        std::vector<std::string> move{"C3","C4","B4"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 3"){
        std::vector<std::string> move{"C3","C4","D5"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 4"){
        std::vector<std::string> move{"C3","C4","D2"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 5"){
        std::vector<std::string> move{"C3","C4","C1"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid 6"){
        std::vector<std::string> move{"C3","C4","B1"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    //inlinemove
    SECTION("valid inline 1"){
        std::vector<std::string> move{"C3","C4"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid inline 2"){
        std::vector<std::string> move{"C3","D4"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid inline 3"){
        std::vector<std::string> move{"C3","D3"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid inline 4"){
        std::vector<std::string> move{"C3","C2"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid inline 5"){
        std::vector<std::string> move{"C3","B2"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("valid inline 6"){
        std::vector<std::string> move{"C3","B3"};
        bool result = board.isValidMove(move);
        bool expected = true ;
        REQUIRE(result== expected);
    }
    SECTION("invalid inline 1"){
        std::vector<std::string> move{"C3","C5"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid inline 2"){
        std::vector<std::string> move{"C3","D5"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid inline 3"){
        std::vector<std::string> move{"C3","E4"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid inline 4"){
        std::vector<std::string> move{"C3","D2"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid inline 5"){
        std::vector<std::string> move{"C3","C1"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid inline 6"){
        std::vector<std::string> move{"C3","B1"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid inline 7"){
        std::vector<std::string> move{"C3","B4"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
    SECTION("invalid inline 8"){
        std::vector<std::string> move{"C3","C3"};
        bool result = board.isValidMove(move);
        bool expected = false ;
        REQUIRE(result== expected);
    }
}

SCENARIO("move methode"){
    GIVEN("hexboard with 61 hexcell"){
        FriendHexBoard board {};
        WHEN("current state empty"){
            std::vector<std::string> input ={"C4","C5"};
            std::optional<bool> currentState ={};
            THEN("throw exception invalid current state"){
                REQUIRE_THROWS_AS( board.move(input,currentState),std::invalid_argument&);
            }

        }
        WHEN("trying to move opposite state"){
            std::vector<std::string> input ={"C4","C5","D5"};
            std::optional<bool> currentState =std::make_optional(false);
            THEN("throw exception trying to move opposite state in side step move"){
                REQUIRE_THROWS_AS( board.move(input,currentState),std::invalid_argument&);
            }
        }
        WHEN("trying to move opposite state"){
            std::vector<std::string> input ={"C4","C5"};
            std::optional<bool> currentState =std::make_optional(false);
            THEN("throw exception trying to move opposite state in inline move"){
                REQUIRE_THROWS_AS( board.move(input,currentState),std::invalid_argument&);
            }
        }
        WHEN("normal in line move "){
            std::vector<std::string> input ={"C4","C5"};
            std::optional<bool> currentState =std::make_optional(true);
            THEN("move is done "){
                bool expected = false;

                bool result ;
                REQUIRE_NOTHROW(result = board.move(input,currentState));
                REQUIRE(expected== result);
            }
        }
        WHEN("normal in side step move "){
            std::vector<std::string> input ={"C4","C5","D5"};
            std::optional<bool> currentState =std::make_optional(true);
            THEN("move is done "){
                bool expected = false;

                bool result ;
                REQUIRE_NOTHROW(result = board.move(input,currentState));
                REQUIRE(expected== result);
            }
        }
        WHEN("bal is pushed "){
            board.setStateInPosition(HexCell{3,-2,-1},std::make_optional(true));
            board.setStateInPosition(HexCell{4,-2,-2},std::make_optional(false));
            std::vector<std::string> input ={"C4","C5"};
            std::optional<bool> currentState =std::make_optional(true);
            THEN("bal ejected"){
                bool expected = true;
                bool result ;
                REQUIRE_NOTHROW(result = board.move(input,currentState));
                REQUIRE(expected== result);
            }
        }

    }
}

TEST_CASE("abaProToHexCell method "){

    FriendHexBoard ami {};

    SECTION("normal case"){
        std::string input = "E5";

        HexCell expected {0,0,0};
        HexCell result = ami.testAbaProToHexCell(input);
        REQUIRE(expected== result);
    }
}

SCENARIO("scenario inlinemove method "){
    GIVEN("hexboard with 61 hexcell"){
         FriendHexBoard ami {};
         WHEN("1->0"){
             HexCell from{0,-2,2};
             HexCell to{-1,-1,2};

             THEN("bal had not been moved"){
                bool expected = false;

                bool result ;
                REQUIRE_NOTHROW(result = ami.testinLineMove(from,to));
                REQUIRE(expected== result);
             }
         }
         WHEN("2->0"){
             HexCell from{1,-2,1};
             HexCell to{2,-2,0};

             THEN("bal had not been moved"){
                bool expected = false;

                bool result ;
                REQUIRE_NOTHROW(result = ami.testinLineMove(from,to));
                REQUIRE(expected== result);
             }
         }
         WHEN("3->0"){
             HexCell from{0,-2,2};
             HexCell to{1,-2,1};
             THEN("bal had not been moved"){
                bool expected = false;

                bool result ;
                REQUIRE_NOTHROW(result = ami.testinLineMove(from,to));
                REQUIRE(expected== result);
             }
         }
         WHEN("2->1"){

             ami.setStateInPosition(HexCell{3,-2,-1},std::make_optional(false));
             HexCell from{1,-2,1};
             HexCell to{2,-2,0};
             THEN("bal had been moved"){
                bool expected = false;

                bool result ;
                REQUIRE_NOTHROW(result = ami.testinLineMove(from,to));
                REQUIRE(expected== result);
             }
         }
         WHEN("3->1"){
             ami.setStateInPosition(HexCell{3,-2,-1},std::make_optional(false));
             HexCell from{0,-2,2};
             HexCell to{1,-2,1};
             THEN("bal had been moved"){
                bool expected = false;

                bool result ;
                REQUIRE_NOTHROW(result = ami.testinLineMove(from,to));
                REQUIRE(expected== result);
             }
         }
         WHEN("3->2"){
             ami.setStateInPosition(HexCell{2,-1,-1},std::make_optional(false));
             HexCell from{2,-4,2};
             HexCell to{2,-3,1};
             THEN("bal had been moved"){
                bool expected = false;

                bool result ;
                REQUIRE_NOTHROW(result = ami.testinLineMove(from,to));
                REQUIRE(expected== result);
             }
         }
         WHEN("3 white -> 1 blac and next 1 white"){
             ami.setStateInPosition(HexCell{1,-1,0},std::make_optional(false));
             ami.setStateInPosition(HexCell{1,0,-1},std::make_optional(true));

             HexCell from{1,-4,3};
             HexCell to{1,-3,2};

             THEN("balls had not been moved"){

                REQUIRE_THROWS_AS(ami.testinLineMove(from,to),std::invalid_argument&);

             }
         }
         WHEN("1v1"){
                      ami.setStateInPosition(HexCell{0,0,0},std::make_optional(true));
                      ami.setStateInPosition(HexCell{1,0,-1},std::make_optional(false));


                      HexCell from{0,0,0};
                      HexCell to{1,0,-1};

                      THEN("balls had not been moved : 1v1"){

                         REQUIRE_THROWS_AS(ami.testinLineMove(from,to),std::invalid_argument&);

                      }
                  }
                  WHEN("2v2"){
                      ami.setStateInPosition(HexCell{0,0,0},std::make_optional(true));
                      ami.setStateInPosition(HexCell{-1,0,1},std::make_optional(true));
                      ami.setStateInPosition(HexCell{1,0,-1},std::make_optional(false));
                      ami.setStateInPosition(HexCell{2,0,-2},std::make_optional(false));

                      HexCell from{-1,0,1};
                      HexCell to{0,0,0};

                      THEN("balls had not been moved : 2v2"){
                         REQUIRE_THROWS_AS(ami.testinLineMove(from,to),std::invalid_argument&);

                      }
                  }
                  WHEN("3v3"){
                      ami.setStateInPosition(HexCell{0,0,0},std::make_optional(true));
                      ami.setStateInPosition(HexCell{-1,0,1},std::make_optional(true));
                      ami.setStateInPosition(HexCell{-2,0,2},std::make_optional(true));
                      ami.setStateInPosition(HexCell{1,0,-1},std::make_optional(false));
                      ami.setStateInPosition(HexCell{2,0,-2},std::make_optional(false));
                      ami.setStateInPosition(HexCell{3,0,-3},std::make_optional(false));

                      HexCell from{-2,0,2};
                      HexCell to{-1,0,1};

                      THEN("balls had not been moved : 3v3"){

                         REQUIRE_THROWS_AS(ami.testinLineMove(from,to),std::invalid_argument&);

                      }
                  }
                  WHEN("move more than 3 balls"){
                      ami.setStateInPosition(HexCell{0,0,0},std::make_optional(true));
                      ami.setStateInPosition(HexCell{-1,0,1},std::make_optional(true));
                      ami.setStateInPosition(HexCell{2,0,-2},std::make_optional(true));
                      ami.setStateInPosition(HexCell{1,0,-1},std::make_optional(true));


                      HexCell from{-1,0,1};
                      HexCell to{0,0,0};

                      THEN("balls had not been moved : max 3 balls can be moved"){

                         REQUIRE_THROWS_AS(ami.testinLineMove(from,to),std::invalid_argument&);

                      }
                  }
                  WHEN("eject own ball"){
                      ami.setStateInPosition(HexCell{3,0,-3},std::make_optional(true));
                      ami.setStateInPosition(HexCell{4,0,-4},std::make_optional(true));


                      HexCell from{3,0,-3};
                      HexCell to{4,0,-4};

                      THEN("balls had not been moved : suicide is not an option"){

                         REQUIRE_THROWS_AS(ami.testinLineMove(from,to),std::invalid_argument&);

                      }
                  }
                  WHEN("eject ball"){
                      ami.setStateInPosition(HexCell{2,0,-2},std::make_optional(true));
                      ami.setStateInPosition(HexCell{3,0,-3},std::make_optional(true));
                      ami.setStateInPosition(HexCell{4,0,-4},std::make_optional(false));

                      HexCell from{2,0,-2};
                      HexCell to{3,0,-3};
                      THEN("bal had been moved and a ball has been ejected"){
                         bool expected = true;

                         bool result ;
                         REQUIRE_NOTHROW(result = ami.testinLineMove(from,to));
                         REQUIRE(expected== result);
                      }
                  }
    }
}
SCENARIO("scenario sidestepmove method "){
    GIVEN("hexboard with 61 hexcell"){
         FriendHexBoard ami {};
         WHEN("2 balls sidestepmove"){
             HexCell firstHexCell{0,-2,2};
             HexCell lastHexCell{1,-2,1};
             HexCell arrivalHexCell{0,-1,1};

             THEN("balls had been moved"){
                REQUIRE_NOTHROW(ami.testsideStepMove(firstHexCell,lastHexCell,arrivalHexCell););

             }
         }
         WHEN("3 balls sidestepmove"){
             HexCell firstHexCell{0,-2,2};
             HexCell lastHexCell{2,-2,0};
             HexCell arrivalHexCell{0,-1,1};

             THEN("balls had been moved"){
                REQUIRE_NOTHROW( ami.testsideStepMove(firstHexCell,lastHexCell,arrivalHexCell));

             }
         }
         WHEN("2 balls : destination not empty"){
             ami.setStateInPosition(HexCell{0,0,0},std::make_optional(true));
             ami.setStateInPosition(HexCell{1,0,-1},std::make_optional(true));
             ami.setStateInPosition(HexCell{0,1,-1},std::make_optional(false));
             ami.setStateInPosition(HexCell{1,1,-2},std::make_optional(true));

             HexCell firstHexCell{0,0,0};
             HexCell lastHexCell{1,0,-1};
             HexCell arrivalHexCell{0,1,-1};
             THEN("bal has not been moved : destination not free"){

                REQUIRE_THROWS_AS( ami.testsideStepMove(firstHexCell,lastHexCell,arrivalHexCell),std::invalid_argument&);

             }
         }
         WHEN("3 balls : destination not empty"){
             ami.setStateInPosition(HexCell{0,0,0},std::make_optional(true));
             ami.setStateInPosition(HexCell{1,0,-1},std::make_optional(true));
             ami.setStateInPosition(HexCell{2,0,-2},std::make_optional(true));
             ami.setStateInPosition(HexCell{0,1,-1},std::make_optional(false));
             ami.setStateInPosition(HexCell{1,1,-2},std::make_optional(true));

             HexCell firstHexCell{0,0,0};
             HexCell lastHexCell{2,0,-2};
             HexCell arrivalHexCell{0,1,-1};
             THEN("bal has not been moved : destination not free"){

                REQUIRE_THROWS_AS( ami.testsideStepMove(firstHexCell,lastHexCell,arrivalHexCell),std::invalid_argument&);

             }
         }
         WHEN("2 balls : move balls from adversary"){
             ami.setStateInPosition(HexCell{0,0,0},std::make_optional(true));
             ami.setStateInPosition(HexCell{1,0,-1},std::make_optional(false));


             HexCell firstHexCell{0,0,0};
             HexCell lastHexCell{1,0,-1};
             HexCell arrivalHexCell{0,1,-1};
             THEN("bal has not been moved : you can move only your balls"){

                REQUIRE_THROWS_AS( ami.testsideStepMove(firstHexCell,lastHexCell,arrivalHexCell),std::invalid_argument&);

             }
         }
         WHEN("3 balls : move balls from adversary"){
             ami.setStateInPosition(HexCell{0,0,0},std::make_optional(true));
             ami.setStateInPosition(HexCell{1,0,-1},std::make_optional(true));
             ami.setStateInPosition(HexCell{2,0,-2},std::make_optional(false));


             HexCell firstHexCell{0,0,0};
             HexCell lastHexCell{2,0,-2};
             HexCell arrivalHexCell{0,1,-1};
             THEN("bal has not been moved : you can move only your balls"){

                REQUIRE_THROWS_AS( ami.testsideStepMove(firstHexCell,lastHexCell,arrivalHexCell),std::invalid_argument&);

             }
         }
    }
}

TEST_CASE("determineDirection method"){
    FriendHexBoard board {};
    SECTION("too much distance between from to"){
        HexCell from{-4,0,4};
        HexCell to{-2,0,2};
        REQUIRE_THROWS_AS(board.testDetermineDirection(from,to),std::invalid_argument&);

    }
    SECTION("1 direction"){
        HexCell from{0,0,0};
        HexCell to{1,0,-1};
        int result = board.testDetermineDirection(from,to);
        int expected = 0;
        REQUIRE(result==expected);
    }
    SECTION("2 direction"){
        HexCell from{1,0,-1};
        HexCell to{2,-1,-1};
        int result = board.testDetermineDirection(from,to);
        int expected = 1;
        REQUIRE(result==expected);
    }
    SECTION("3 direction"){
        HexCell from{1,0,-1};
        HexCell to{1,-1,0};
        int result = board.testDetermineDirection(from,to);
        int expected = 2;
        REQUIRE(result==expected);
    }
    SECTION("4 direction"){
        HexCell from{1,0,-1};
        HexCell to{0,0,0};
        int result = board.testDetermineDirection(from,to);
        int expected = 3;
        REQUIRE(result==expected);
    }
    SECTION("5 direction"){
        HexCell from{1,0,-1};
        HexCell to{0,1,-1};
        int result = board.testDetermineDirection(from,to);
        int expected = 4;
        REQUIRE(result==expected);
    }
    SECTION("6 direction"){
        HexCell from{1,0,-1};
        HexCell to{1,1,-2};
        int result = board.testDetermineDirection(from,to);
        int expected = 5;
        REQUIRE(result==expected);
    }
}

TEST_CASE("changeposition methode"){
    FriendHexBoard board {};
    SECTION(" move the balls in occupied cells"){
        std::vector<HexCell> cells = {HexCell{0,-3,3},HexCell{1,-3,2}};
        REQUIRE_THROWS_AS(board.testChangePosition(cells,5),std::invalid_argument&);
    }
    SECTION("free move"){
        std::vector<HexCell> cells = {HexCell{0,-2,2},HexCell{1,-2,1}};
        REQUIRE_NOTHROW(board.testChangePosition(cells,5));
    }
}
