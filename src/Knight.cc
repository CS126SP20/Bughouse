//
// Created by tomok on 4/19/2020.
//

#include <chess/BoardEngine.h>
#include "chess/PieceClasses/Knight.h"

namespace chess {

  Knight::Knight(bool is_white, bool is_pawn)
    : is_white_(is_white),
      is_pawn_{is_pawn} {}

  bool Knight::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    int row_diff = abs(turn.first.first - turn.second.first);
    int col_diff = abs(turn.first.second - turn.second.second);
    return ((turn.first.second == EMPTY)) ||
          (row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2);
  }
  std::vector<std::pair<int,int>> Knight::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    std::vector<std::pair<int,int>> path;
    return path;
  }
}