//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H


#include "Piece.h"
#include "vector"
#include <cinder/Area.h>

namespace chess {
  const int kBoardSize = 8;
  
class Board {

public:
  Board();
  
  Piece* GetPieceAtSquare(int row, int col);
  Piece* GetPieceInHand(bool is_white, int index);
  Piece* GetAndRemoveFromHand(bool is_white, int index);
  void ReceivePiece(Piece* piece);
  int GetHandSize(bool is_white);
  Piece* Update(std::pair<std::pair<int,int>,std::pair<int,int>> turn, bool is_white_turn);
  bool IsValidMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn, bool is_white_turn);
  bool HasPromotedPawn(bool is_white_turn);
  void PromotePawn(PieceType choice, bool is_white_turn);
  
  
  
private:
  Piece* board_[kBoardSize][kBoardSize];
  std::vector<Piece*> black_player_hand_;
  std::vector<Piece*> white_player_hand_;
  void SetUpBoard();
  bool IsPathOpen(std::vector<std::pair<int,int>>& path);
  bool can_white_castle_;
  bool can_black_castle_;
  bool CanCastle(bool is_white_turn);  
  
  void TurnOffCastle(bool is_white_turn);
  void Castle(std::pair<std::pair<int, int>, std::pair<int, int>> turn);


};  
}

#endif //FINALPROJECT_BOARD_H
