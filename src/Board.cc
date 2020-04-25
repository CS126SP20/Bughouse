//
// Created by tomok on 4/19/2020.
//

#include "chess/PieceClasses/Pawn.h"
#include "chess/PieceClasses/King.h"
#include "chess/PieceClasses/Queen.h"
#include "chess/PieceClasses/Knight.h"
#include "chess/PieceClasses/Bishop.h"
#include "chess/PieceClasses/Rook.h"
#include "chess/Board.h"


namespace chess {

Board::Board() {
  SetUpBoard();
}  

Piece* Board::Update(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
  Piece* captured = board_[turn.second.first][turn.second.second];
  board_[turn.second.first][turn.second.second] = board_[turn.first.first][turn.first.second];
  board_[turn.first.first][turn.first.second] = nullptr;
  return captured;
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

Piece* Board::GetPieceAtLocWhiteView(int row, int col) {
  return board_[row][col];
}

Piece* Board::GetPieceAtLocBlackView(int row, int col) {
  return board_[kBoardSize - row - 1][kBoardSize - col - 1];
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

int Board::GetHandSize(bool is_white) {
  if (is_white) {
    return white_player_hand_.size();
  } else {
    return black_player_hand_.size();
  }
}

void Board::SetUpBoard() {
  bool is_white = true;
  bool is_pawn = false;

  board_[0][0] = new Rook(!is_white, is_pawn);
  board_[0][7] = new Rook(!is_white, is_pawn);
  board_[7][0] = new Rook(is_white, is_pawn);
  board_[7][7] = new Rook(is_white, is_pawn);

  board_[0][1] = new Knight(!is_white, is_pawn);
  board_[0][6] = new Knight(!is_white, is_pawn);
  board_[6][1] = new Knight(is_white, is_pawn);
  board_[6][6] = new Knight(is_white, is_pawn);

  board_[0][2] = new Bishop(!is_white, is_pawn);
  board_[0][5] = new Bishop(!is_white, is_pawn);
  board_[5][2] = new Bishop(is_white, is_pawn);
  board_[5][5] = new Bishop(is_white, is_pawn);

  board_[0][3] = new Queen(!is_white, is_pawn);
  board_[7][3] = new Queen(is_white, is_pawn);

  board_[0][4] = new King(!is_white);
  board_[7][4] = new King(is_white);


  // Set up the pawns on the 2nd and 7th ranks with their respective colors.
  for (int i = 0; i < kBoardSize; i++) {
    board_[1][i] = new Pawn(false);
    board_[kBoardSize - 2][i] = new Pawn(true);
  }

  // Set everything else to nullptr
  for (int i = 2; i < kBoardSize - 2; i++) {
    for (int j = 0; j < kBoardSize; j++) {
      board_[i][j] = nullptr;
    }
  }
}
}