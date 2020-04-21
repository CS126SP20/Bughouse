//
// Created by tomok on 4/19/2020.
//

#include "chess/Bishop.h"

namespace chess {
  Bishop::Bishop(bool is_white) : is_white_(is_white) {}
  
  bool Bishop::IsLegalMove(int start_x, int start_y, int end_x, int end_y) {
    return false;
  }
  
}