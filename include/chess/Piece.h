// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_CHESS_PIECE_H
#define FINALPROJECT_CHESS_PIECE_H


#include <utility>
#include <vector>
#include "Location.h"

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

/**
 * Abstract class for all of the chess pieces.
 */
class Piece {
 public:
  
  // Tells whether a piece is a promoted pawn or not
  virtual bool IsPawn() = 0;
  
  // Returns whether a given move is legal or not (calculation depends upon the piece
  virtual bool IsLegalMove(std::pair<Location, Location> turn) = 0;
  
  // Given that the move is legal, returns the path that the piece requires to be open
  // in order to reach the destination square
  // Called after IsLegalMove is verified
  virtual std::vector<Location> CalculatePath(std::pair<Location,Location> turn) = 0;
  
  // Color of the piece
  virtual bool GetIsWhite() = 0; 
  
  // Returns the piece type
  virtual PieceType GetPieceType() = 0;
  
  // Purely for the pawn, to track the first double square move
  // Called once the piece is moved
  virtual void DoTurn() = 0;
 
  
};

}  // namespace chess


#endif // FINALPROJECT_CHESS_PIECE_H_
