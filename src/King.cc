//
// Created by tomok on 4/19/2020.
//

#include "chess/PieceClasses/King.h"

namespace chess {
  King::King(bool is_white) : is_white_(is_white) {}

  bool King::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    return false;
  }

  std::vector<std::pair<int,int>> King::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    std::vector<std::pair<int,int>> path;
    return path;
  }
}