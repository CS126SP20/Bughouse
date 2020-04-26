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

   bool IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) override;

   bool GetIsWhite() override { return is_white_; }
   
   PieceType GetPieceType() override { return PAWN; };

   bool IsPawn() override { return true; }

   void Reset() override { }

   std::vector<std::pair<int,int>> GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) override;
 };
 
}
#endif //FINALPROJECT_PAWN_H
