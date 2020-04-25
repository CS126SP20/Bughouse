//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_PAWN_H
#define FINALPROJECT_PAWN_H

#include "chess/Piece.h"

namespace chess {
  
 class Pawn : public Piece {
   bool is_white_;
   bool can_en_pass_;
   //TODO: A PAWN CAN BE ANY PIECE!
 public:
   explicit Pawn(bool is_white);

   bool IsLegalMove(int start_x, int start_y, int end_x, int end_y) override;

   bool GetIsWhite() override { return is_white_; }
   
   PieceType GetPieceType() override { return PAWN; };

   bool IsPawn() override { return true; }

   void Reset() override { }
 };
 
}
#endif //FINALPROJECT_PAWN_H
