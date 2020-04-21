//
// Created by tomok on 4/19/2020.
//
#include <chess/Knight.h>
#include "chess/Board.h"
namespace chess {

Board::Board() {
  board_[0][0] = new Knight(true);
  
}  
}