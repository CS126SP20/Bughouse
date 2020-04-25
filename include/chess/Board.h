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
  
  Piece* GetPieceAtLocWhiteView(int row, int col);
  Piece* GetPieceAtLocBlackView(int row, int col);
  Piece* GetPieceInHand(bool is_white, int index);
  void ReceivePiece(Piece* piece);
  int GetHandSize(bool is_white);

  Piece* Update(std::pair<std::pair<int,int>,std::pair<int,int>> turn);
private:
  Piece* board_[kBoardSize][kBoardSize];
  std::vector<Piece*> black_player_hand_;
  std::vector<Piece*> white_player_hand_;
  void SetUpBoard();

};  
}

#endif //FINALPROJECT_BOARD_H
