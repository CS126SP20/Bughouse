//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_BISHOP_H
#define FINALPROJECT_BISHOP_H

#include "chess/Piece.h"

namespace chess {

class Bishop : public Piece {
 public:

  explicit Bishop(bool is_white, bool is_pawn);

  bool IsLegalMove(std::pair<Location, Location> turn) override ;

  bool GetIsWhite() override { return is_white_; } 

  PieceType GetPieceType() override { return BISHOP; }

  bool IsPawn() override { return is_pawn_; }

  std::vector<Location> GetPath(std::pair<Location, Location> turn) override;

  void DoTurn() override {}
    
 private:
    bool is_white_;
    bool is_pawn_;
};

}

#endif //FINALPROJECT_BISHOP_H
