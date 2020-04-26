//
// Created by tomok on 4/19/2020.
//

#include <chess/PieceClasses/Rook.h>
#include <chess/PieceClasses/Bishop.h>
#include "chess/PieceClasses/Queen.h"

namespace chess {
  Queen::Queen(bool is_white, bool is_pawn)
    : is_white_(is_white),
      is_pawn_{is_pawn} {}

  bool Queen::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    Rook rook(is_white_, false);
    Bishop bishop(is_white_, false);
    return rook.IsLegalMove(turn) || bishop.IsLegalMove(turn);
  }

  // TODO: Make a rook or a bishop and return their path.
  std::vector<std::pair<int,int>> Queen::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    Rook rook(is_white_, false);
    Bishop bishop(is_white_, false);
    if (rook.IsLegalMove(turn)) {
      return rook.GetPath(turn);
    } else {
      return bishop.GetPath(turn);
    }
  }

}