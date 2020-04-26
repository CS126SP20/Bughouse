//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_KING_H
#define FINALPROJECT_KING_H

#include "King.h"
#include "chess/Piece.h"

namespace chess {

class King : public Piece {
    bool is_white_;

  public:
    explicit King(bool is_white);

    bool IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn);

    bool GetIsWhite() { return is_white_; }

    PieceType GetPieceType() { return KING; }
    
    bool IsPawn() override { return false; }
    
    void Reset() override { }

    std::vector<std::pair<int,int>> GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) override;
  };

}

#endif //FINALPROJECT_KING_H
