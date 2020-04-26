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
  void ReceivePiece(Piece* piece);
  int GetHandSize(bool is_white);
  Piece* Update(std::pair<std::pair<int,int>,std::pair<int,int>> turn, bool is_white_turn);
  bool IsValidMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn, bool is_white_turn);
  
private:
  Piece* board_[kBoardSize][kBoardSize];
  std::vector<Piece*> black_player_hand_;
  std::vector<Piece*> white_player_hand_;
  void SetUpBoard();
  bool IsPathOpen(std::vector<std::pair<int,int>>& path);

};  
}

#endif //FINALPROJECT_BOARD_H
