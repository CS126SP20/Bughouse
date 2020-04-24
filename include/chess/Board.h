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

  Piece* Update(std::pair<std::pair<int,int>,std::pair<int,int>> turn);
private:
  Piece* board_[kBoardSize][kBoardSize];
  void SetUpBoard();

};  
}

#endif //FINALPROJECT_BOARD_H
