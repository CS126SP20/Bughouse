//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_KING_H
#define FINALPROJECT_KING_H

#include "King.h"
#include "chess/Piece.h"

namespace chess {

class King : public Piece {
    bool is_white_;

  public:
    explicit King(bool is_white);

    bool IsLegalMove(int start_x, int start_y, int end_x, int end_y);

    bool GetIsWhite() { return is_white_; }

    PieceType GetPieceType() { return KING; }
  };

}

#endif //FINALPROJECT_KING_H
