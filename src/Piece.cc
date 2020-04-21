// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <chess/Piece.h>

namespace chess {
  

Queen::Queen(bool is_white) {
  is_white_ = is_white;
  piece_type_ = QUEEN;
}  

King::King(bool is_white) {
  is_white_ = is_white;
  piece_type_ = KING;
}  

Bishop::Bishop(bool is_white) {
  is_white_ = is_white;
  piece_type_ = BISHOP;
}  

}  // namespace chess
