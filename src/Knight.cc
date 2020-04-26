//
// Created by tomok on 4/19/2020.
//

#include "chess/PieceClasses/Knight.h"

namespace chess {

  Knight::Knight(bool is_white, bool is_pawn)
    : is_white_(is_white),
      is_pawn_{is_pawn} {}

  bool Knight::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    return false;
  }
  std::vector<std::pair<int,int>> Knight::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    std::vector<std::pair<int,int>> path;
    return path;
  }
}