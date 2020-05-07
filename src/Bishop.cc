//
// Created by tomok on 4/19/2020.
//

#include "chess/PieceClasses/Bishop.h"
#include <chess/BoardEngine.h>


namespace chess {
  
Bishop::Bishop(bool is_white, bool is_pawn)
  : is_white_(is_white),
    is_pawn_{is_pawn} {}
  
    
bool Bishop::IsLegalMove(std::pair<Location, Location> turn) {
  bool is_valid = false;
  
  if (turn.first.Col() == EMPTY) {
    // The piece is chosen from the hand
    is_valid = true;
  } else if (abs(turn.first.Row() - turn.second.Row()) == abs(turn.first.Col() - turn.second.Col())) {
    // The bishop can only move diagonally with a slope of 1 or -1.
    is_valid = true;
  }
  
  return is_valid;
}

std::vector<Location> Bishop::CalculatePath(std::pair<Location, Location> turn) {
  std::vector<Location> path;
    
  int row1 = turn.first.Row();
  int col1 = turn.first.Col();
  int row2 = turn.second.Row();
  int col2 = turn.second.Col();

  if (col1 == EMPTY) {
    // The bishop is played from the hand.
    // The destination square needs to be open.
    path.push_back(turn.second);
    return path;
  }
    
  int sign_y;
  int sign_x;
    
  if (row2 > row1) sign_y = 1; // Moving down
  else sign_y = -1; // Moving up
    
  if (col2 > col1) sign_x = 1; // Moving to the right
  else sign_x = -1; // Moving to the left
  
  
  while ((abs(col1 - col2) > 1 ) && (abs(row1 - row2) > 1)) {
    // Don't add destination square because it does not have to be empty (could be a capture)
    
    // While the bishop isn't at the destination, add points to path
    col1 += sign_x;
    row1 += sign_y;
    auto point = Location(row1, col1);
    path.push_back(point);
  }

  return path;
}
  
}