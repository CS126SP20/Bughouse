//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_ROOK_H
#define FINALPROJECT_ROOK_H


#include "chess/Piece.h"

namespace chess {

  class Rook : public Piece {
    bool is_white_;
    bool is_pawn_;
  public:

    explicit Rook(bool is_white, bool is_pawn);

    bool IsLegalMove(int start_x, int start_y, int end_x, int end_y) override;

    bool GetIsWhite() override { return is_white_; }

    PieceType GetPieceType() override { return ROOK; }

    bool IsPawn() override { return is_pawn_; }

    void Reset() override { }
  };


}


#endif //FINALPROJECT_ROOK_H
