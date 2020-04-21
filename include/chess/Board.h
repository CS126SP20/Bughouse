//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H


#include "Piece.h"

namespace chess {
  const int kBoardSize = 8;
  
class Board {

public:
  Board();
  Piece* GetPieceAtLocWhiteView(int row, int col);
  Piece* GetPieceAtLocBlackView(int row, int col);
  void MovePiece(int start, int end);
  
private:
  Piece* board_[kBoardSize][kBoardSize];
};  
}

#endif //FINALPROJECT_BOARD_H
