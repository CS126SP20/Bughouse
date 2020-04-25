//
// Created by tomok on 4/19/2020.
//

#include "chess/PieceClasses/King.h"

namespace chess {
  King::King(bool is_white) : is_white_(is_white) {}

  bool King::IsLegalMove(int start_x, int start_y, int end_x, int end_y) {
    return false;
  }

}