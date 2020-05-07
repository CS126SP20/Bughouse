//
// Created by tomok on 5/6/2020.
//

#include <catch2/catch.hpp>
#include <chess/Board.h>
#include <chess/PieceClasses/Rook.h>

using namespace chess;

TEST_CASE("Update test", "[update][getpiece]") {
  Board board;
  auto move = std::make_pair(Location(7, 1), Location(5, 2));
  board.Update(move, true);
  Location location = Location(5, 2);
  REQUIRE(board.GetPieceAtSquare(location)->GetPieceType() == KNIGHT);
}

TEST_CASE("Play from hand", "[update][getpiece]") {
  Board board;
  Rook* rook = new Rook(true, false);
  board.ReceivePiece(rook);
  
  auto move = std::make_pair(Location(0, EMPTY), Location(5, 4));
  board.Update(move, true);
  Location location = Location(5, 4);
  REQUIRE(board.GetPieceAtSquare(location)->GetPieceType() == ROOK);
  
  delete rook;
}

TEST_CASE("Promote pawn", "[promote][getpiece]") {
  Board board;
  auto move = std::make_pair(Location(6, 0), Location(0, 0));
  board.Update(move, true);
  REQUIRE(board.HasPromotedPawn(true));
  
  Location location = Location(0, 0);
  board.PromotePawn(QUEEN, true);
  REQUIRE(board.GetPieceAtSquare(location)->GetPieceType() == QUEEN);
}

TEST_CASE("Receive piece", "[receive][handsize][remove]") {
  Board board;
  Rook* rook = new Rook(true, false);
  board.ReceivePiece(rook);
  REQUIRE(board.GetHandSize(true) == 1);
  REQUIRE(board.GetAndRemoveFromHand(true, 0) == rook);
  REQUIRE(board.GetHandSize(true) == 0);
  delete rook;
}
