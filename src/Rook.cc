//
// Created by tomok on 4/19/2020.
//

#include <chess/Knight.h>
#include "chess/Rook.h"

namespace chess {
  
  Rook::Rook(bool is_white) : is_white_(is_white) {}

  bool Rook::IsLegalMove(int start_x, int start_y, int end_x, int end_y) {
    return false;
  }

}