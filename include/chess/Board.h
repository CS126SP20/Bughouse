//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H


#include "Piece.h"
#include "vector"
#include <cinder/Area.h>
#include "Location.h"

namespace chess {
  const int kBoardSize = 8;
  
class Board {

public:
  
  // Sets up a standard chess board
  Board();

  // Updates the board with the turn
  // Called on a validated turn in cinder's update
  // Returns the captured piece, and if there is none, then will return nullptr
  Piece* Update(std::pair<Location, Location> turn, bool is_white_turn);

  // Checks if the move is valid according to the turn
  bool IsValidMove(std::pair<Location, Location> turn, bool is_white_turn);
  
  // Returns the piece pointer of the piece at a square.
  // Nullptr is returned if there is no piece at that square
  Piece* GetPieceAtSquare(Location& loc);
  
  // Returns the piece pointer of a piece in a player's hand
  // Returns nullptr if the index is invalid
  Piece* GetPieceInHand(bool is_white, int index);
  
  // Removes the piece from the hand to place onto the board
  // Returns nullptr if the index is invalid
  Piece* GetAndRemoveFromHand(bool is_white, int index);
  
  // Puts a piece into the player's hand
  void ReceivePiece(Piece* piece);
  
  // Returns the specified player's number of pieces in the hand
  int GetHandSize(bool is_white);

  // Checks if the move was a pawn promotion
  bool HasPromotedPawn(bool is_white_turn);
  
  // Promotes the pawn with the choice of the player. 
  void PromotePawn(PieceType choice, bool is_white_turn);
  
  
  
private:
  
  // Represents the board. 
  // Each square is filled with either nullptr or the pointer to the piece
  Piece* board_[kBoardSize][kBoardSize];
  
  // Represents the player's hand of pieces they can place on the board
  std::vector<Piece*> black_player_hand_;
  std::vector<Piece*> white_player_hand_;

  // Castling rights
  bool can_white_castle_queen_;
  bool can_white_castle_king_;
  bool can_black_castle_queen_;
  bool can_black_castle_king_;
  
  // The column index of the last double-moved pawn
  // If the last move was not a double-pawn move, then it is -1.
  int en_pass_col_;
  
  // Whether the current move is an en passant or not
  bool is_en_pass_;
  
  // Called by constructor to initialize the board in standard chess format
  void SetUpBoard();
  
  // Checks to make sure that the path of the piece is open
  // Called after IsValidMove
  bool IsPathOpen(std::vector<Location>& path);
  
  // Given that the current piece is a pawn attempting to en pass, makes sure that
  // it is valid
  bool CanEnPass(Location pawn_destination, bool is_white_turn);
  
  // Returns castling rights of the respective player
  bool CanCastleQueen(bool is_white_turn);  
  bool CanCastleKing(bool is_white_turn);
  
  // Performs the en passant
  Piece* EnPass(Location pawn_destination, bool is_white_turn);

  // Performs the castling
  void Castle(std::pair<Location, Location> turn);
  
  // Invalidates castling rights of the respective player
  void TurnOffQueenCastle(bool is_white_turn);
  void TurnOffKingCastle(bool is_white_turn);
  
};  

}

#endif //FINALPROJECT_BOARD_H
