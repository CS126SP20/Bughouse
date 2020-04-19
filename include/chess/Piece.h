// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_CHESS_PIECE_H
#define FINALPROJECT_CHESS_PIECE_H


namespace chess {

enum PieceType {
  Rook,
  Knight,
  Bishop,
  Pawn,
  Queen,
  King
};  

class Piece {
  bool is_white_;
  PieceType piece_type_;
};


}  // namespace chess


#endif // FINALPROJECT_CHESS_PIECE_H_
