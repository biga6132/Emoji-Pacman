#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Game.h"
#include "Player.h"
#include <cmath>

//ToRelativePosition test case
TEST_CASE ( "ToRelativePosition ", "[toRelativePosition]") {
    Player player1 = Player("Biswas", true);
    Position p1 = {1,1};
    player1.SetPosition(p1);
    Position p2 = {1,2};  //right
    Position p3 = {1,0};  //left
    Position p4 = {2,1};  //down
    Position p5 = {0,1};  //up
    std::string test1 = player1.ToRelativePosition(p2);
    std::string test2 = player1.ToRelativePosition(p3);
    std::string test3 = player1.ToRelativePosition(p4);
    std::string test4 = player1.ToRelativePosition(p5);
  SECTION( "Relative position should be R" ) {
    REQUIRE( test1 == "R" );
  }
  SECTION( "Relative position should be L" ) {
    REQUIRE( test2 == "L" );
  }
  SECTION( "Relative position should be D" ) {
    REQUIRE( test3 == "D" );
  }
  SECTION( "Relative position should be U" ) {
    REQUIRE( test4 == "U" );
  }
}

TEST_CASE ( "Player Constructor makes Player properly", "[Playerconstructor]") {
  Player p = Player("Biswas", true);
  SECTION( "Player should be contructed properly" ) {
    REQUIRE(p.get_name() == "Biswas");
    REQUIRE(p.is_human() == true);
    REQUIRE(p.get_points() == 0);
    REQUIRE(p.hasTreasure() == false);
    REQUIRE(p.isDead() == false);
    REQUIRE(p.getMoves() == 0);
    REQUIRE(p.getLives() == 3);
  }
}
TEST_CASE ( "Stringify makes string representation of string", "[stringify]") {
  Player p = Player("Biswas", true);
  Player p2 = Player("Jon", true);
  p2.setLives();
  Player p3 = Player("Tyrion", true);
  p3.setLives();
  p3.setLives();
  SECTION( "Stringify should be make string representation of string" ) {
    REQUIRE(p.Stringify() == "Biswas has 3 lives remaining");
    REQUIRE(p2.Stringify() == "Jon has 2 lives remaining");
    REQUIRE(p3.Stringify() == "Tyrion has 1 lives remaining");
  }
}