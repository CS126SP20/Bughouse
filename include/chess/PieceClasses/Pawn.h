//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_PAWN_H
#define FINALPROJECT_PAWN_H

#include "chess/Piece.h"

namespace chess {
  
 class Pawn : public Piece {
   bool is_white_;
   bool is_poss_double_move_;
   bool can_double_move_;
   //TODO: A PAWN CAN BE ANY PIECE!
 public:
   explicit Pawn(bool is_white);

   bool GetIsWhite() override { return is_white_; }
   
   PieceType GetPieceType() override { return PAWN; };

   bool IsPawn() override { return true; }

   void Reset() override { }

   bool Pawn::IsLegalMove(std::pair<Location, Location> turn) override;
   
   std::vector<Location> GetPath(std::pair<Location, Location> turn) override;

   void DoTurn() override;
 };
 
}
#endif //FINALPROJECT_PAWN_H
