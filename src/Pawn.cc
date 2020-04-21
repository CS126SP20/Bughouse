//
// Created by tomok on 4/19/2020.
//

#include "chess/Pawn.h"

namespace chess {
Pawn::Pawn(bool is_white)
  : can_en_pass_{false},
    is_white_(is_white)
  { }

bool Pawn::IsLegalMove(int start_x, int start_y, int end_x, int end_y) {
  return false;
}

}  