//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_PAWN_H
#define FINALPROJECT_PAWN_H

#include "Piece.h"

namespace chess {
  
 class Pawn : public Piece {
   bool is_white_;
   bool can_en_pass_;
   bool is_queen_;
   
 public:
   explicit Pawn(bool is_white);

   bool IsLegalMove(int start_x, int start_y, int end_x, int end_y) override;

   bool GetIsWhite() override { return is_white_; }
   
   PieceType GetPieceType() override;
 };
 
}
#endif //FINALPROJECT_PAWN_H
