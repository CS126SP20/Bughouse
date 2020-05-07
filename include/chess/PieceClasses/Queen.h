//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_QUEEN_H
#define FINALPROJECT_QUEEN_H

#include "chess/Piece.h"

namespace chess {

class Queen : public Piece {

 public:

  explicit Queen(bool is_white, bool is_pawn);

  bool IsLegalMove(std::pair<Location, Location> turn) override;

  bool GetIsWhite() override { return is_white_; }

  PieceType GetPieceType() override { return QUEEN; }

  bool IsPawn() override { return is_pawn_; }

  std::vector<Location> CalculatePath(std::pair<Location, Location> turn) override;

  void DoTurn() override {}
  
 private:
  bool is_white_;
  bool is_pawn_;
  
};

}

#endif //FINALPROJECT_QUEEN_H
