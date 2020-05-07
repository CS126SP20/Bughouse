//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_KING_H
#define FINALPROJECT_KING_H

#include "King.h"
#include "chess/Piece.h"

namespace chess {

class King : public Piece {
 public:
  explicit King(bool is_white);

  bool IsLegalMove(std::pair<Location, Location> turn);

  bool GetIsWhite() { return is_white_; }

  PieceType GetPieceType() { return KING; }
    
  bool IsPawn() override { return false; }

  std::vector<Location> CalculatePath(std::pair<Location, Location> turn) override;

  void DoTurn() override { }
  
 private:
  bool is_white_;
};

}

#endif //FINALPROJECT_KING_H
