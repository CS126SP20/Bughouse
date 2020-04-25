// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_CHESS_PIECE_H
#define FINALPROJECT_CHESS_PIECE_H


#include <utility>

namespace chess {

enum PieceType {
  ROOK,
  KNIGHT,
  BISHOP,
  PAWN,
  QUEEN,
  QUEENED_PAWN,
  KING
};  

class Piece {
 public:
  virtual void Reset() = 0;
  virtual bool IsPawn() = 0;
  virtual bool IsLegalMove(int start_x, int start_y, int end_x, int end_y) = 0;
  virtual bool GetIsWhite() = 0; 
  virtual PieceType GetPieceType() = 0; 
};

}  // namespace chess


#endif // FINALPROJECT_CHESS_PIECE_H_
