//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_QUEEN_H
#define FINALPROJECT_QUEEN_H

#include "chess/Piece.h"

namespace chess {

class Queen : public Piece {
    bool is_white_;
    
    bool is_pawn_;
  public:

    explicit Queen(bool is_white, bool is_pawn);

    bool IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) override;

    bool GetIsWhite() override { return is_white_; }

    PieceType GetPieceType() override { return QUEEN; }

  bool IsPawn() override { return is_pawn_; }

  void Reset() override { }

  std::vector<std::pair<int,int>> GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) override;
  };

}

#endif //FINALPROJECT_QUEEN_H
