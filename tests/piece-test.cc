//
// Created by tomok on 5/6/2020.
//
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <chess/PieceClasses/Rook.h>
#include <chess/PieceClasses/Queen.h>
#include <chess/PieceClasses/King.h>
#include <chess/PieceClasses/Knight.h>
#include <chess/PieceClasses/Bishop.h>
#include <chess/PieceClasses/Pawn.h>

using namespace chess;

TEST_CASE("Rook test", "[is_legal][rook][path]") {
  Rook rook = Rook(true, false);
  
  SECTION("Legal move") {
    auto move = std::make_pair(Location(0, 3), Location(4, 3));
    REQUIRE(rook.IsLegalMove(move));
  }
  
  SECTION("Illegal move") {
    auto move = std::make_pair(Location(0, 3), Location(4, 4));
    REQUIRE_FALSE(rook.IsLegalMove(move));
  }
  
  SECTION("Path") {
    auto move = std::make_pair(Location(0, 3), Location(4, 3));
    std::vector<Location> path;
    path.emplace_back(Location(1, 3));
    path.emplace_back(Location(2, 3));
    path.emplace_back(Location(3,3));
    
    REQUIRE(path == rook.CalculatePath(move));
  }
  
}

TEST_CASE("King test", "[is_legal][king][path]") {
  King king = King(true);

  SECTION("Legal move") {
    auto move = std::make_pair(Location(5, 3), Location(4, 3));
    REQUIRE(king.IsLegalMove(move));
  }

  SECTION("Illegal move") {
    auto move = std::make_pair(Location(6, 4), Location(4, 4));
    REQUIRE_FALSE(king.IsLegalMove(move));
  }

  SECTION("Path") {
    auto move = std::make_pair(Location(2, 3), Location(3, 4));

    REQUIRE(king.CalculatePath(move).empty());
  }
  
}

TEST_CASE("Knight test", "[is_legal][knight][path]") {
  Knight knight = Knight(true, false);

  SECTION("Legal move") {
    auto move = std::make_pair(Location(5, 3), Location(7, 4));
    REQUIRE(knight.IsLegalMove(move));
  }

  SECTION("Illegal move") {
    auto move = std::make_pair(Location(6, 4), Location(4, 4));
    REQUIRE_FALSE(knight.IsLegalMove(move));
  }

  SECTION("Path") {
    auto move = std::make_pair(Location(2, 3), Location(4, 4));
    REQUIRE(knight.CalculatePath(move).empty());
  }
}

TEST_CASE("Pawn test", "[is_legal][pawn][path]") {
  Pawn pawn = Pawn(true);

  SECTION("Legal move") {
    auto move = std::make_pair(Location(5, 3), Location(3, 3));
    REQUIRE(pawn.IsLegalMove(move));
  }

  SECTION("Illegal move") {
    auto move = std::make_pair(Location(5, 4), Location(6, 4));
    REQUIRE_FALSE(pawn.IsLegalMove(move));
  }

  SECTION("Path") {
    auto move = std::make_pair(Location(5, 3), Location(3, 3));
    std::vector<Location> path;
    path.emplace_back(Location(4, 3));
    path.emplace_back(Location(3, 3));
    REQUIRE(path == pawn.CalculatePath(move));
  }
}

TEST_CASE("Black Bishop test", "[is_legal][bishop][path]") {
  Bishop bishop = Bishop(false, false);

  SECTION("Legal move") {
    auto move = std::make_pair(Location(0, 1), Location(6, 7));
    REQUIRE(bishop.IsLegalMove(move));
  }

  SECTION("Illegal move") {
    auto move = std::make_pair(Location(0, 1), Location(2, 2));
    REQUIRE_FALSE(bishop.IsLegalMove(move));
  }

  SECTION("Path") {
    auto move = std::make_pair(Location(0, 1), Location(6, 7));
    std::vector<Location> path;
    path.emplace_back(Location(1, 2));
    path.emplace_back(Location(2, 3));
    path.emplace_back(Location(3,4));
    path.emplace_back(Location(4, 5));
    path.emplace_back(Location(5,6));

    REQUIRE(path == bishop.CalculatePath(move));
  }
}

TEST_CASE("Queen test", "[is_legal][queen][path]") {
  Queen queen = Queen(true, false);

  SECTION("Bishop-like Legal move") {
    auto move = std::make_pair(Location(0, 1), Location(6, 7));
    REQUIRE(queen.IsLegalMove(move));
  }

  SECTION("Bishop-like Illegal move") {
    auto move = std::make_pair(Location(0, 1), Location(2, 2));
    REQUIRE_FALSE(queen.IsLegalMove(move));
  }

  SECTION("Bishop-like Path") {
    auto move = std::make_pair(Location(0, 1), Location(6, 7));
    std::vector<Location> path;
    path.emplace_back(Location(1, 2));
    path.emplace_back(Location(2, 3));
    path.emplace_back(Location(3,4));
    path.emplace_back(Location(4, 5));
    path.emplace_back(Location(5,6));

    REQUIRE(path == queen.CalculatePath(move));
  }

  SECTION("Rook-like Legal move") {
    auto move = std::make_pair(Location(0, 3), Location(4, 3));
    REQUIRE(queen.IsLegalMove(move));
  }

  SECTION("Rook-like Illegal move") {
    auto move = std::make_pair(Location(0, 3), Location(4, 4));
    REQUIRE_FALSE(queen.IsLegalMove(move));
  }

  SECTION("Rook-like Path") {
    auto move = std::make_pair(Location(0, 3), Location(4, 3));
    std::vector<Location> path;
    path.emplace_back(Location(1, 3));
    path.emplace_back(Location(2, 3));
    path.emplace_back(Location(3,3));

    REQUIRE(path == queen.CalculatePath(move));
  }
}

