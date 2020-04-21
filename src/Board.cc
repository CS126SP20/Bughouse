//
// Created by tomok on 4/19/2020.
//

#include "chess/Pawn.h"
#include "chess/King.h"
#include "chess/Queen.h"
#include "chess/Knight.h"
#include "chess/Bishop.h"
#include "chess/Rook.h"
#include "chess/Board.h"


namespace chess {

Board::Board() {
  int row_num = 0;
  bool is_white;
  
  for (int row = 0; row < kBoardSize; row++) {
    is_white = row_num != 0;
    
    for (int i = 0; i < kBoardSize; i++) {
      switch(i) {
        case 0:
        case 7:
          // Fill corners with rooks
          board_[row_num][i] = new Rook(is_white);
          break;
        case 1:
        case 6:
          // Fill 2nd and 7th columns with knights
          board_[row_num][i] = new Knight(is_white);
          break;
        case 2:
        case 5:  
          // Fill 3rd and 6th columns with Bishops
          board_[row_num][i] = new Bishop(is_white);
          break;
        case 3:
          board_[row_num][i] = new Queen(is_white);
          break;
        case 4:
          board_[row_num][i] = new King(is_white);
      }
    }
    
    row_num = kBoardSize - 1;
  }
  
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

Piece* Board::GetPieceAtLoc(int x, int y) {
  return board_[x][y];
}

}