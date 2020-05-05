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
    can_white_castle_{true} 
    {
  SetUpBoard();
}  

Piece* Board::Update(std::pair<std::pair<int,int>,std::pair<int,int>> turn, bool is_white_turn) {
  Piece* captured = nullptr;
  if (turn.first.second == EMPTY) {
    Piece* to_move = GetAndRemoveFromHand(is_white_turn, turn.first.first);
    to_move->DoTurn();
    board_[turn.second.first][turn.second.second] = to_move;
    
  } else {
    Piece* to_move = board_[turn.first.first][turn.first.second];
    captured = board_[turn.second.first][turn.second.second];
    
    if (CanCastle(is_white_turn) && (to_move->GetPieceType() == ROOK || to_move->GetPieceType() == KING)) {
      TurnOffCastle(is_white_turn);
      if (to_move->GetPieceType() == KING && abs(turn.first.second - turn.second.second) > 1) {
        Castle(turn);
        return nullptr;
      }
    }
    
    if (captured != nullptr && captured->GetPieceType() != PAWN && captured->IsPawn()) {
      Piece* to_delete = captured;
      captured = new Pawn(captured->GetIsWhite());
      delete to_delete;
    }
    board_[turn.second.first][turn.second.second] = to_move;
    to_move->DoTurn();
    board_[turn.first.first][turn.first.second] = nullptr;
    
  }

  return captured;
}

void Board::Castle(std::pair<std::pair<int, int>, std::pair<int, int>> turn) {
  board_[turn.second.first][turn.second.second] = board_[turn.first.first][turn.first.second];
  board_[turn.first.first][turn.first.second] = nullptr;

  std::pair<int,int> start_rook_loc;
  std::pair<int,int> new_rook_loc;
  if (turn.second.second == 2) {
    start_rook_loc = std::make_pair(turn.second.first, 0);
    new_rook_loc = std::make_pair(turn.second.first, turn.second.second + 1);
  } else {
    start_rook_loc = std::make_pair(turn.second.first, kBoardSize - 1);
    new_rook_loc = std::make_pair(turn.second.first, turn.second.second - 1);
  }
  
  board_[new_rook_loc.first][new_rook_loc.second] = board_[start_rook_loc.first][start_rook_loc.second];
  board_[start_rook_loc.first][start_rook_loc.second] = nullptr;
  
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



bool Board::IsValidMove(std::pair<std::pair<int, int>, std::pair<int, int> > turn, bool is_white_turn) {
  Piece* to_move;
  if (turn.first.second == EMPTY) {
    to_move = GetPieceInHand(is_white_turn, turn.first.first);
  } else {
    to_move = GetPieceAtSquare(turn.first.first, turn.first.second);
  }
  
  bool is_valid = false;
  if (to_move->IsLegalMove(turn)) {
    std::vector<std::pair<int,int>> path = to_move->GetPath(turn);
    if (IsPathOpen(path)) {
      if (to_move->GetPieceType() == PAWN && path.size() == 0) {
        if (board_[turn.second.first][turn.second.second] != nullptr) is_valid = true;
      } else if (to_move->GetPieceType() == KING && abs(turn.first.second - turn.second.second) > 1) { 
        is_valid = CanCastle(is_white_turn);
      } else {
        is_valid = true;
      }
    }
  }
  
  return is_valid;
}

bool Board::IsPathOpen(std::vector<std::pair<int, int>> &path) {
  bool is_open = true;
  for (std::pair<int,int> point : path) {
    if (GetPieceAtSquare(point.first, point.second) != nullptr) {
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
  piece->Reset();
  if (is_white) {
    white_player_hand_.push_back(piece);
  } else {
    black_player_hand_.push_back(piece);
  }
}

Piece* Board::GetPieceAtSquare(int row, int col) {
  return board_[row][col];
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