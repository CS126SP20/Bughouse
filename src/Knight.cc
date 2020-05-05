//
// Created by tomok on 4/19/2020.
//
#include "chess/PieceClasses/Knight.h"
#include <chess/BoardEngine.h>


namespace chess {

Knight::Knight(bool is_white, bool is_pawn)
  : is_white_(is_white),
    is_pawn_{is_pawn} {}

bool Knight::IsLegalMove(std::pair<Location, Location> turn) {
  
  int row_diff = abs(turn.first.Row() - turn.second.Row());
  int col_diff = abs(turn.first.Col() - turn.second.Col());
  
  // Knight moves in an L shape, 2 by 1
  return ((turn.first.Col() == EMPTY)) ||
        (row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2);
}

std::vector<Location> Knight::GetPath(std::pair<Location, Location> turn) {
  std::vector<Location> path;
  // The knight can jump, so no squares need to be empty
  return path;
}
}