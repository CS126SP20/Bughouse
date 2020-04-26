//
// Created by tomok on 4/19/2020.
//

#include "chess/PieceClasses/Pawn.h"

namespace chess {
Pawn::Pawn(bool is_white)
  : can_en_pass_{false},
    is_white_(is_white)
  { }

bool Pawn::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
  return false;
}

std::vector<std::pair<int,int>> Pawn::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
  std::vector<std::pair<int,int>> path;
  return path;
}
}  