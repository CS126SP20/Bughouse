//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_QUEEN_H
#define FINALPROJECT_QUEEN_H

#include "Piece.h"

namespace chess {

class Queen : public Piece {
    bool is_white_;

  public:

    explicit Queen(bool is_white);

    bool IsLegalMove(int start_x, int start_y, int end_x, int end_y) override;

    bool GetIsWhite() override { return is_white_; }

    PieceType GetPieceType() override { return QUEEN; }
  };

}

#endif //FINALPROJECT_QUEEN_H
