//
// Created by tomok on 4/19/2020.
//

#include <chess/PieceClasses/Knight.h>
#include <chess/BoardEngine.h>
#include "chess/PieceClasses/Rook.h"

namespace chess {
  
  Rook::Rook(bool is_white, bool is_pawn)
    : is_white_(is_white),
      is_pawn_{is_pawn} {}

  bool Rook::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    return (turn.first.second == EMPTY) // Moved from the hand to the board
          || (turn.first.first == turn.second.first)  // Moving horizontally
          || (turn.first.second == turn.second.second); // Moving vertically
  }    

  std::vector<std::pair<int,int>> Rook::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    std::vector<std::pair<int,int>> path;
    int row1 = turn.first.first;
    int col1 = turn.first.second;
    int row2 = turn.second.first;
    int col2 = turn.second.second;
    
    if (col1 == EMPTY) {
      path.push_back(turn.second);
      return path;
    }
    
    if (row1 == row2) {
      int min_col = std::min(col1, col2);
      int max_col = std::max(col1, col2);
      for (int col = min_col + 1; col < max_col; col++) {
        auto path_point = std::make_pair(row1, col);
        path.push_back(path_point);
      }
    } else if (col1 == col2) {
      int min_row = std::min(row1, row2);
      int max_row = std::max(row1, row2);
      for (int row = min_row + 1; row < max_row; row++) {
        auto path_point = std::make_pair(row, col1);
        path.push_back(path_point);
      }
    }
    
    return path;
  }

}