#include "catch.hpp"
#include "friend_game.h"
using namespace model;


TEST_CASE("readPlayerMove method"){
    FriendGame game{};
        SECTION("inputs too long"){
            std::string s = "H1H2H3H4";
            REQUIRE_THROWS_AS(game.testReadPlayerMove(s),std::invalid_argument&);
        }
        SECTION("inputs too short"){
            std::string s = "H1";
            REQUIRE_THROWS_AS(game.testReadPlayerMove(s),std::invalid_argument&);
        }
        SECTION("input empty"){
            std::string s = "";
            REQUIRE_THROWS_AS(game.testReadPlayerMove(s),std::invalid_argument&);
        }
        SECTION("2 coordinates OK"){
            std::string s = "A1A2";
            unsigned result = game.testReadPlayerMove(s).size();
            unsigned expected = 2;
            REQUIRE(result==expected);

         }
        SECTION("3 coordinates OK"){
            std::string s = "A1A2A3";
            unsigned result = game.testReadPlayerMove(s).size();
            unsigned expected = 3;
            REQUIRE(result==expected);
         }
}
TEST_CASE("isInputValid"){
    FriendGame game{};

    SECTION("String in vector too long"){
       std::string s1= "A1A";
       std::string s2 = "B1";
       std ::vector<std::string> v{};
       v.push_back(s1);
       v.push_back(s2);
       REQUIRE_THROWS_AS(game.testIsInputValid(v),std::invalid_argument&);
    }

    SECTION("String in vector too short"){

       std::string s1= "A";
       std::string s2 = "B1";

       std ::vector<std::string> v{};

       v.push_back(s1);
       v.push_back(s2);

       REQUIRE_THROWS_AS(game.testIsInputValid(v),std::invalid_argument&);
    }

    SECTION("first is not alphabet second is numeric"){

       std::string s1= "11";
       std::string s2 = "B1";

       std ::vector<std::string> v{};

       v.push_back(s1);
       v.push_back(s2);

       bool result = game.testIsInputValid(v);
       bool expected = false;
       REQUIRE(result==expected);

    }

    SECTION("first is alphabet second is not numeric"){

       std::string s1= "AA";
       std::string s2 = "B1";

       std ::vector<std::string> v{};

       v.push_back(s1);
       v.push_back(s2);

       bool result = game.testIsInputValid(v);
       bool expected = false;
       REQUIRE(result==expected);

    }

    SECTION("first is not alphabet second is not numeric"){

       std::string s1= "1A";
       std::string s2 = "B1";

       std ::vector<std::string> v{};

       v.push_back(s1);
       v.push_back(s2);

       bool result = game.testIsInputValid(v);
       bool expected = false;
       REQUIRE(result==expected);

    }

    SECTION("first is alphabet second is numeric"){

       std::string s1= "A1";
       std::string s2 = "B1";

       std ::vector<std::string> v{};

       v.push_back(s1);
       v.push_back(s2);

       bool result = game.testIsInputValid(v);
       bool expected = true;
       REQUIRE(result==expected);

    }
}

TEST_CASE("Check winner "){
    Game game{};

    SECTION("Player has not won"){
        for (int i =0; i < 5; i++){
            game.getCurrentPlayer().addBallOut();

        }
       bool result = game.checkWinner();
       bool expected = false;
       REQUIRE(result==expected);
    }

    SECTION("Player has won"){

       for (int i =0; i < 6; i++){
           game.getCurrentPlayer().addBallOut();

       }

       bool result = game.checkWinner();
       bool expected = true;
       REQUIRE(result==expected);
    }
}

TEST_CASE("Switch player "){
    FriendGame game{};

    SECTION("current player is player1"){

       game.testSwitchPlayer();
       std::optional<bool> result = game.getCurrentPlayer().getState();
       std::optional<bool> expected = false;
       REQUIRE(result==expected);
    }

    SECTION("current player is player2"){
       game.testSwitchPlayer();
       game.testSwitchPlayer();

       std::optional<bool> result = game.getCurrentPlayer().getState();
       std::optional<bool> expected = true;
       REQUIRE(result==expected);
    }
}



