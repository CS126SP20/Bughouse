//
// Created by tomok on 4/19/2020.
//
#include "chess/PieceClasses/Rook.h"
#include <chess/BoardEngine.h>


namespace chess {
  
Rook::Rook(bool is_white, bool is_pawn)
  : is_white_(is_white),
    is_pawn_{is_pawn} {}

bool Rook::IsLegalMove(std::pair<Location, Location> turn) {
  return (turn.first.Col() == EMPTY) // Moved from the hand to the board
        || (turn.first.Row() == turn.second.Row())  // Moving horizontally
        || (turn.first.Col() == turn.second.Col()); // Moving vertically
}    

std::vector<Location> Rook::CalculatePath(std::pair<Location,Location> turn) {
  
  std::vector<Location> path;
  int row1 = turn.first.Row();
  int col1 = turn.first.Col();
  int row2 = turn.second.Row();
  int col2 = turn.second.Col();
  
  if (col1 == EMPTY) {
    // Placed from hand. Must be on an empty square
    path.push_back(turn.second);
    return path;
  }
  
  if (row1 == row2) {
    // Moved horizontally 
    int min_col = std::min(col1, col2);
    int max_col = std::max(col1, col2);
    
    for (int col = min_col + 1; col < max_col; col++) {
      // Add squares it will cross up until the destination square, because those need to be empty
      auto path_point = Location(row1, col);
      path.push_back(path_point);
    }
  } else if (col1 == col2) {
    // Moved vertically
    int min_row = std::min(row1, row2);
    int max_row = std::max(row1, row2);
    
    for (int row = min_row + 1; row < max_row; row++) {
      // Add squares it will cross up until the destination square, because those need to be emtpy
      auto path_point = Location(row, col1);
      path.push_back(path_point);
    }
  }
    
  return path;
}

}