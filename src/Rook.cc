//
// Created by tomok on 4/19/2020.
//

#include <chess/PieceClasses/Knight.h>
#include "chess/PieceClasses/Rook.h"

namespace chess {
  
  Rook::Rook(bool is_white, bool is_pawn)
    : is_white_(is_white),
      is_pawn_{is_pawn} {}

  bool Rook::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    return false;
  }

  std::vector<std::pair<int,int>> Rook::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    std::vector<std::pair<int,int>> path;
    return path;
  }

}