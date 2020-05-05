//
// Created by tomok on 4/19/2020.
//

#include "chess/Board.h"
#include <chess/BoardEngine.h>
#include "chess/PieceClasses/Pawn.h"
#include "chess/PieceClasses/King.h"
#include "chess/PieceClasses/Queen.h"
#include "chess/PieceClasses/Knight.h"
#include "chess/PieceClasses/Bishop.h"
#include "chess/PieceClasses/Rook.h"



namespace chess {

Board::Board()
  : can_black_castle_{true},
    can_white_castle_{true},
    en_pass_col_(EMPTY),
    is_en_pass_(false)
    {
  SetUpBoard();
}  

Piece* Board::Update(std::pair<Location, Location> turn, bool is_white_turn) {
  Piece* captured = nullptr;
  if (turn.first.Col() == EMPTY) {
    Piece* to_move = GetAndRemoveFromHand(is_white_turn, turn.first.Row());
    to_move->DoTurn();
    board_[turn.second.Row()][turn.second.Col()] = to_move;
    
  } else {
    Piece* to_move = board_[turn.first.Row()][turn.first.Col()];
    
    if (to_move->GetPieceType() == PAWN && abs(turn.second.Row() - turn.first.Row()) == 2) {
      en_pass_col_ = turn.second.Col();
      is_en_pass_ = false;
    } else if (is_en_pass_) {
      captured = EnPass(turn.second, is_white_turn);
      en_pass_col_ = EMPTY;
      is_en_pass_ = false;
    } else {
      captured = board_[turn.second.Row()][turn.second.Col()];
      is_en_pass_ = false;
      en_pass_col_ = EMPTY;
    }
    
    
    if (CanCastle(is_white_turn) && (to_move->GetPieceType() == ROOK || to_move->GetPieceType() == KING)) {
      TurnOffCastle(is_white_turn);
      if (to_move->GetPieceType() == KING && abs(turn.first.Col() - turn.second.Col()) > 1) {
        Castle(turn);
        return nullptr;
      }
    }
    
    if (captured != nullptr && captured->GetPieceType() != PAWN && captured->IsPawn()) {
      Piece* to_delete = captured;
      captured = new Pawn(captured->GetIsWhite());
      delete to_delete;
    }
    board_[turn.second.Row()][turn.second.Col()] = to_move;
    to_move->DoTurn();
    board_[turn.first.Row()][turn.first.Col()] = nullptr;
    
  }

  return captured;
}

Piece* Board::EnPass(Location pawn_destination, bool is_white_turn) {
  Piece* captured;
  if (is_white_turn) {
    captured = board_[pawn_destination.Row() + 1][en_pass_col_];
    board_[pawn_destination.Row() + 1][en_pass_col_] = nullptr;
  } else {
    captured = board_[pawn_destination.Row() - 1][en_pass_col_];
    board_[pawn_destination.Row() - 1][en_pass_col_] = nullptr;
  }
  return captured;
}

void Board::Castle(std::pair<Location, Location> turn) {
  board_[turn.second.Row()][turn.second.Col()] = board_[turn.first.Row()][turn.first.Col()];
  board_[turn.first.Row()][turn.first.Col()] = nullptr;

  Location start_rook_loc;
  Location new_rook_loc;
  if (turn.second.Col() == 2) {
    start_rook_loc = Location(turn.second.Row(), 0);
    new_rook_loc = Location(turn.second.Row(), turn.second.Col() + 1);
  } else {
    start_rook_loc = Location(turn.second.Row(), kBoardSize - 1);
    new_rook_loc = Location(turn.second.Row(), turn.second.Col() - 1);
  }
  
  board_[new_rook_loc.Row()][new_rook_loc.Col()] = board_[start_rook_loc.Row()][start_rook_loc.Col()];
  board_[start_rook_loc.Row()][start_rook_loc.Col()] = nullptr;
  
}

bool Board::CanCastle(bool is_white_turn) {
  if (is_white_turn) {
    return can_white_castle_;
  } else {
    return can_black_castle_;
  }
}

void Board::TurnOffCastle(bool is_white_turn) {
  if (is_white_turn) {
    can_white_castle_ = false;
  } else {
    can_black_castle_ = false;
  }
}



bool Board::IsValidMove(std::pair<Location, Location> turn, bool is_white_turn) {
  Piece* to_move;
  if (turn.first.Col() == EMPTY) {
    to_move = GetPieceInHand(is_white_turn, turn.first.Row());
  } else {
    to_move = GetPieceAtSquare(turn.first);
  }
  
  bool is_valid = false;
  if (to_move->IsLegalMove(turn)) {
    std::vector<Location> path = to_move->GetPath(turn);
    if (IsPathOpen(path)) {
      if (to_move->GetPieceType() == PAWN && path.size() == 0) {
        if (board_[turn.second.Row()][turn.second.Col()] != nullptr) is_valid = true;
        else is_valid = CanEnPass(turn.second, is_white_turn);
      } else if (to_move->GetPieceType() == KING && abs(turn.first.Col() - turn.second.Col()) > 1) { 
        is_valid = CanCastle(is_white_turn);
      } else {
        is_valid = true;
      }
    }
  }
  
  return is_valid;
}

bool Board::CanEnPass(chess::Location pawn_destination, bool is_white_turn) {
  if (pawn_destination.Col() == en_pass_col_) {
    bool valid;
    if (is_white_turn) {
      valid = pawn_destination.Row() == 2;
    } else {
      valid = pawn_destination.Row() == 5;
    }
    
    is_en_pass_ = valid;
    return valid;
    
  } else {
    is_en_pass_ = false;
    return false;
  }
}

bool Board::IsPathOpen(std::vector<Location> &path) {
  bool is_open = true;
  for (Location loc : path) {
    if (GetPieceAtSquare(loc) != nullptr) {
      is_open = false;
      break;
    }
  }
  return is_open;
}

bool Board::HasPromotedPawn(bool is_white_turn) {
  int row;
  if (is_white_turn) {
    row = 0;
  } else {
    row = kBoardSize - 1;
  }
  
  for (int i = 0; i < kBoardSize; i++) {
    if (board_[row][i] != nullptr && board_[row][i]-> GetPieceType() == PAWN) {
      return true;
    }
  }
  return false;
}

void Board::PromotePawn(PieceType choice, bool is_white_turn) {
  int row;
  if (is_white_turn) {
    row = 0;
  } else {
    row = kBoardSize - 1;
  }

  for (int i = 0; i < kBoardSize; i++) {
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
      
      board_[row][i] = promotion_piece;
      
      delete pawn;
    }
  }
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
}