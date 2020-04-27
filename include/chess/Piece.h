// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_CHESS_PIECE_H
#define FINALPROJECT_CHESS_PIECE_H


#include <utility>
#include <vector>

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
  virtual bool IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) = 0;
  virtual std::vector<std::pair<int,int>> GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) = 0;
  virtual bool GetIsWhite() = 0; 
  virtual PieceType GetPieceType() = 0;
  virtual void DoTurn() = 0;
 
  
};

}  // namespace chess


#endif // FINALPROJECT_CHESS_PIECE_H_
