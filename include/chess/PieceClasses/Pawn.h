//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_PAWN_H
#define FINALPROJECT_PAWN_H

#include "chess/Piece.h"

namespace chess {
  
class Pawn : public Piece {

 public:
  explicit Pawn(bool is_white);

  bool GetIsWhite() override { return is_white_; }
   
  PieceType GetPieceType() override { return PAWN; };

  bool IsPawn() override { return true; }

  bool Pawn::IsLegalMove(std::pair<Location, Location> turn) override;
   
  std::vector<Location> CalculatePath(std::pair<Location, Location> turn) override;

  void DoTurn() override;
  
 private:
  bool is_white_;
  // The pawn may double move -- depending on whether the board validates that it can go there
  bool is_poss_double_move_;
  bool can_double_move_;
  
  // The pawn is placed from the hand
  bool IsValidPlacement(Location pawn_destination);
};
 
}
#endif //FINALPROJECT_PAWN_H
