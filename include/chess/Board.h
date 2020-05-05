//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H


#include "Piece.h"
#include "vector"
#include <cinder/Area.h>
#include "Location.h"

namespace chess {
  const int kBoardSize = 8;
  
class Board {

public:
  Board();
  
  Piece* GetPieceAtSquare(Location& loc);
  Piece* GetPieceInHand(bool is_white, int index);
  Piece* GetAndRemoveFromHand(bool is_white, int index);
  void ReceivePiece(Piece* piece);
  int GetHandSize(bool is_white);
  Piece* Update(std::pair<Location, Location> turn, bool is_white_turn);
  bool IsValidMove(std::pair<Location, Location> turn, bool is_white_turn);
  bool HasPromotedPawn(bool is_white_turn);
  void PromotePawn(PieceType choice, bool is_white_turn);
  
  
  
private:
  Piece* board_[kBoardSize][kBoardSize];
  std::vector<Piece*> black_player_hand_;
  std::vector<Piece*> white_player_hand_;
  void SetUpBoard();
  bool IsPathOpen(std::vector<Location>& path);
  bool can_white_castle_;
  bool can_black_castle_;
  int en_pass_col_;
  bool is_en_pass_;
  void UpdateEnPassCol(std::pair<Location, Location> turn, bool is_white_turn);
  bool CanEnPass(Location pawn_destination, bool is_white_turn);
  bool CanCastle(bool is_white_turn);  
  Piece* EnPass(Location pawn_destination, bool is_white_turn);
  void TurnOffCastle(bool is_white_turn);
  void Castle(std::pair<Location, Location> turn);


};  
}

#endif //FINALPROJECT_BOARD_H
