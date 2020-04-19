// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_CHESS_PIECE_H
#define FINALPROJECT_CHESS_PIECE_H


namespace chess {

enum PieceType {
  ROOK,
  KNIGHT,
  BISHOP,
  PAWN,
  QUEEN,
  KING
};  

class Piece {
 public: 
  virtual bool is_legal_move(int loc1, int loc2) = 0;
  
 protected: 
  bool is_white_;
  PieceType piece_type_;
};

class Pawn : public Piece {
  bool can_en_pass_;
  Pawn(bool is_white);
  bool is_legal_move(int loc1, int loc2);
};

class King : public Piece {
  bool can_castle_;
  King(bool is_white);
  bool is_legal_move(int loc1, int loc2);
};

class Queen : public Piece {
  Queen(bool is_white);
  bool is_legal_move(int loc1, int loc2);
};

class Rook : public Piece {
  bool can_castle;
  Rook(bool is_white);
  bool is_legal_move(int loc1, int loc2);
};

class Bishop : public Piece {
  Bishop(bool is_white);
  bool is_legal_move(int loc1, int loc2);
};

class Knight : public Piece {
  Knight(bool is_white);
  bool is_legal_move(int loc1, int loc2);
};

}  // namespace chess


#endif // FINALPROJECT_CHESS_PIECE_H_
