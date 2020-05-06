//
// Created by tomok on 4/19/2020.
//

#include "chess/Board.h"
#include "chess/PieceClasses/Pawn.h"
#include "chess/PieceClasses/King.h"
#include "chess/PieceClasses/Queen.h"
#include "chess/PieceClasses/Knight.h"
#include "chess/PieceClasses/Bishop.h"
#include "chess/PieceClasses/Rook.h"



namespace chess {

Board::Board()
  : can_black_castle_queen_{true},
    can_white_castle_king_{true},
    can_black_castle_king_{true},
    can_white_castle_queen_{true},
    en_pass_col_(EMPTY),
    is_en_pass_(false)
    {
  SetUpBoard();
}

//================================================================
// Public member functions
//================================================================

Piece* Board::Update(std::pair<Location, Location> turn, bool is_white_turn) {
  
  if (turn.first.Col() == EMPTY) {
    PlacePieceOnBoard(turn, is_white_turn);
    // No captures
    return nullptr;
  }

  // Default captured piece is nullptr
  Piece* captured = nullptr;
  // The piece to move is the first part of turn
  Piece* to_move = board_[turn.first.Row()][turn.first.Col()];

  // Check for castling
  if (to_move->GetPieceType() == KING) {
    if (abs(turn.first.Col() - turn.second.Col()) > 1) {
      Castle(turn);
      TurnOffKingCastle(is_white_turn);
      TurnOffQueenCastle(is_white_turn);
      en_pass_col_ = EMPTY;
      is_en_pass_ = false;
      return nullptr;
    }
  }
  
  // Check en passant special and pawn special cases
  if (to_move->GetPieceType() == PAWN && abs(turn.second.Row() - turn.first.Row()) == 2) {
    
    // The pawn double moved, so en passant could happen on the next move
    en_pass_col_ = turn.second.Col();
    is_en_pass_ = false;
    
  } else { 
    
    if (is_en_pass_) {
      // Current move is an en passant, so do that.
      captured = EnPass(turn.second, is_white_turn);
    } else {
      // Nothing special happened
      captured = board_[turn.second.Row()][turn.second.Col()];      
    }
    en_pass_col_ = EMPTY;
    is_en_pass_ = false;
  }
  
  UpdateCastlingRights(turn.second, to_move, is_white_turn);
  
  // If the captured piece was a promoted pawn, revert back to a pawn
  if (captured != nullptr && captured->GetPieceType() != PAWN && captured->IsPawn()) {
    Piece* to_delete = captured;
    captured = new Pawn(captured->GetIsWhite());
    delete to_delete;
  }
  
  // Update the board
  board_[turn.second.Row()][turn.second.Col()] = to_move;
  to_move->DoTurn();
  board_[turn.first.Row()][turn.first.Col()] = nullptr;
  
  return captured;
}


bool Board::IsValidMove(std::pair<Location, Location> turn, bool is_white_turn) {
  Piece* to_move;
  
  if (turn.first.Col() == EMPTY) {
    to_move = GetPieceInHand(is_white_turn, turn.first.Row());
  } else {
    to_move = GetPieceAtSquare(turn.first);
  }
  
  bool is_valid = false;
  // Check if the move is legal according to the piece
  if (to_move->IsLegalMove(turn)) {
    
    // Get the path of the move
    std::vector<Location> path = to_move->GetPath(turn);
    
    if (IsPathOpen(path)) {
      // Path is clear
      
      if (to_move->GetPieceType() == PAWN && path.empty()) {
        
        // Pawn moved diagonally, so either a capture or an en passant
        if (board_[turn.second.Row()][turn.second.Col()] != nullptr) is_valid = true; // Pawn capture
        else is_valid = CanEnPass(turn.second, is_white_turn); // En passant
        
      } else if (to_move->GetPieceType() == KING && abs(turn.first.Col() - turn.second.Col()) > 1) {
        
        // King castling 
        if ((turn.second.Col() < kBoardSize / 2 && CanCastleQueen(is_white_turn))
        || (turn.second.Col() > kBoardSize / 2 && CanCastleKing(is_white_turn))) {
          is_valid = true;
        }
        
      } else {
        // If it is not a special case, as long as the path is clear, it is valid
        is_valid = true;
        
      }
    }
  }
  
  return is_valid;
}

void Board::PromotePawn(PieceType choice, bool is_white_turn) {
  int row;
  if (is_white_turn) {
    row = 0;
  } else {
    row = kBoardSize - 1;
  }

  for (int i = 0; i < kBoardSize; i++) {
    // Find the promoted pawn
    if (board_[row][i] != nullptr && board_[row][i]-> GetPieceType() == PAWN) {
      Piece* pawn = board_[row][i];
      Piece* promotion_piece;
      
      switch (choice) {
        case QUEEN :
          promotion_piece = new Queen(is_white_turn, true);
          break;
        case ROOK :
          promotion_piece = new Rook(is_white_turn, true);
          break;
        case KNIGHT :
          promotion_piece = new Knight(is_white_turn, true);
          break;
        case BISHOP :
          promotion_piece = new Bishop(is_white_turn, true);
          break;
        default :
          promotion_piece = nullptr;
      }
      
      // Replace the pawn with the promotion choice
      board_[row][i] = promotion_piece;
      
      delete pawn;
    }
  }
}

bool Board::HasPromotedPawn(bool is_white_turn) {
  // Pawn has to be on last rank
  int row;
  if (is_white_turn) {
    row = 0;
  } else {
    row = kBoardSize - 1;
  }
  
  for (int i = 0; i < kBoardSize; i++) {
    // Search for a promoted pawn
    if (board_[row][i] != nullptr && board_[row][i]-> GetPieceType() == PAWN) {
      return true;
    }
  }
  return false;
}

void Board::ReceivePiece(Piece* piece) {
  bool is_white = piece->GetIsWhite();
  
  if (is_white) {
    white_player_hand_.push_back(piece);
  } else {
    black_player_hand_.push_back(piece);
  }
}

Piece* Board::GetPieceAtSquare(Location& loc) {
  return board_[loc.Row()][loc.Col()];
}

Piece* Board::GetPieceInHand(bool is_white, int index) {
  if (index < 0) {
    return nullptr;
  }
  if (is_white && index < white_player_hand_.size()) {
    return white_player_hand_[index];
  } else if (!is_white && index < black_player_hand_.size()) {
    return black_player_hand_[index];
  }
}

Piece* Board::GetAndRemoveFromHand(bool is_white, int index) {
  Piece* to_remove = GetPieceInHand(is_white, index);
  if (to_remove == nullptr) {
    return nullptr;
  }
  
  if (is_white) {
    white_player_hand_.erase(white_player_hand_.begin() + index);
  } else {
    black_player_hand_.erase(black_player_hand_.begin() + index);
  }
  return to_remove;
  
}

int Board::GetHandSize(bool is_white) {
  if (is_white) {
    return white_player_hand_.size();
  } else {
    return black_player_hand_.size();
  }
}

//===================================================================================
// Private member functions
//===================================================================================

void Board::SetUpBoard() {
  // Set everything else to nullptr
  for (int i = 0; i < kBoardSize; i++) {
    for (int j = 0; j < kBoardSize; j++) {
      board_[i][j] = nullptr;
    }
  }
  
  bool is_white = true;
  bool is_pawn = false;

  board_[0][0] = new Rook(!is_white, is_pawn);
  board_[0][7] = new Rook(!is_white, is_pawn);
  board_[7][0] = new Rook(is_white, is_pawn);
  board_[7][7] = new Rook(is_white, is_pawn);

  board_[0][1] = new Knight(!is_white, is_pawn);
  board_[0][6] = new Knight(!is_white, is_pawn);
  board_[7][1] = new Knight(is_white, is_pawn);
  board_[7][6] = new Knight(is_white, is_pawn);

  board_[0][2] = new Bishop(!is_white, is_pawn);
  board_[0][5] = new Bishop(!is_white, is_pawn);
  board_[7][2] = new Bishop(is_white, is_pawn);
  board_[7][5] = new Bishop(is_white, is_pawn);

  board_[0][3] = new Queen(!is_white, is_pawn);
  board_[7][3] = new Queen(is_white, is_pawn);

  board_[0][4] = new King(!is_white);
  board_[7][4] = new King(is_white);


  // Set up the pawns on the 2nd and 7th ranks with their respective colors.
  for (int i = 0; i < kBoardSize; i++) {
    board_[1][i] = new Pawn(!is_white);
    board_[kBoardSize - 2][i] = new Pawn(is_white);
  }
}

Piece* Board::EnPass(Location pawn_destination, bool is_white_turn) {
  Piece* captured;
  
  // Capture the pawn directly behind the destination
  if (is_white_turn) {
    captured = board_[pawn_destination.Row() + 1][en_pass_col_];
    board_[pawn_destination.Row() + 1][en_pass_col_] = nullptr;
  } else {
    captured = board_[pawn_destination.Row() - 1][en_pass_col_];
    board_[pawn_destination.Row() - 1][en_pass_col_] = nullptr;
  }
  
  return captured;
}

bool Board::CanEnPass(chess::Location pawn_destination, bool is_white_turn) {
  // Make sure that the pawn is going in the direction of the last double pawn move
  if (pawn_destination.Col() == en_pass_col_) {
    
    bool valid;
    // Make sure pawn ends on the right rank
    if (is_white_turn) {
      valid = pawn_destination.Row() == 2;
    } else {
      valid = pawn_destination.Row() == 5;
    }
    // Notify board that the move is an en passant
    is_en_pass_ = valid;
    return valid;
    
  } else {
    is_en_pass_ = false;
    return false;
  }
}

void Board::Castle(std::pair<Location, Location> turn) {
  // Move the king
  board_[turn.second.Row()][turn.second.Col()] = board_[turn.first.Row()][turn.first.Col()];
  board_[turn.first.Row()][turn.first.Col()] = nullptr;

  Location start_rook_loc;
  Location new_rook_loc;
  
  if (turn.second.Col() == 2) {
    // Queen-side castling, left rook goes to right of king
    start_rook_loc = Location(turn.second.Row(), 0);
    new_rook_loc = Location(turn.second.Row(), turn.second.Col() + 1);
  } else {
    // King-side castling, right rook goes to left of king
    start_rook_loc = Location(turn.second.Row(), kBoardSize - 1);
    new_rook_loc = Location(turn.second.Row(), turn.second.Col() - 1);
  }
  
  // Move rook
  board_[new_rook_loc.Row()][new_rook_loc.Col()] = board_[start_rook_loc.Row()][start_rook_loc.Col()];
  board_[start_rook_loc.Row()][start_rook_loc.Col()] = nullptr;
  
}

void Board::UpdateCastlingRights(Location destination, chess::Piece *to_move, bool is_white_turn) {
  // Check for castling or movement of rook or king
  if (CanCastleKing(is_white_turn) || CanCastleQueen(is_white_turn)) {
    
    if (to_move -> GetPieceType() == ROOK) {
      
      if (destination.Col() < kBoardSize / 2) {
        // They moved the left rook, so can no longer queen-side castle
        TurnOffQueenCastle(is_white_turn);
      } else {
        // They moved the right rook, so can no longer king-side castle
        TurnOffKingCastle(is_white_turn);
      }
      
    } else if (to_move->GetPieceType() == KING) {
      // They moved the king, so can not longer castle in either direction
      TurnOffKingCastle(is_white_turn);
      TurnOffQueenCastle(is_white_turn);
    }
  }
}

bool Board::CanCastleQueen(bool is_white_turn) {
  if (is_white_turn) {
    return can_white_castle_queen_;
  } else {
    return can_black_castle_queen_;
  }
}

bool Board::CanCastleKing(bool is_white_turn) {
  if (is_white_turn) {
    return can_white_castle_king_;
  } else {
    return can_black_castle_king_;
  }
}

void Board::TurnOffQueenCastle(bool is_white_turn) {
  if (is_white_turn) {
    can_white_castle_queen_ = false;
  } else {
    can_black_castle_queen_ = false;
  }
}

void Board::TurnOffKingCastle(bool is_white_turn) {
  if (is_white_turn) {
    can_white_castle_king_ = false;
  } else {
    can_black_castle_king_ = false;
  }
}

bool Board::IsPathOpen(std::vector<Location> &path) {
  bool is_open = true;
  for (Location loc : path) {
    // Make sure every location on the path is nullptr
    if (GetPieceAtSquare(loc) != nullptr) {
      is_open = false;
      break;
    }
  }
  return is_open;
}

void Board::PlacePieceOnBoard(std::pair<Location, Location> turn, bool is_white_turn) {
  // The piece was selected from the hand
  Piece* to_move = GetAndRemoveFromHand(is_white_turn, turn.first.Row());
  to_move->DoTurn();

  // Place the piece on the board
  board_[turn.second.Row()][turn.second.Col()] = to_move;
  
}

}