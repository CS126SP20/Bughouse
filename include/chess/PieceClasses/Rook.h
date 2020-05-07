//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_ROOK_H
#define FINALPROJECT_ROOK_H


#include "chess/Piece.h"

namespace chess {

class Rook : public Piece {
 public:

  explicit Rook(bool is_white, bool is_pawn);

  bool GetIsWhite() override { return is_white_; }

  PieceType GetPieceType() override { return ROOK; }

  bool IsPawn() override { return is_pawn_; }

  bool IsLegalMove(std::pair<Location, Location> turn) override;
    
  std::vector<Location> CalculatePath(std::pair<Location, Location> turn) override;

  void DoTurn() override {}

 private:
  bool is_white_;
  bool is_pawn_;
};

}


#endif //FINALPROJECT_ROOK_H
