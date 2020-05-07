//
// Created by tomok on 4/19/2020.
//


#include "chess/PieceClasses/King.h"
#include <chess/Board.h>

namespace chess {
  King::King(bool is_white) : is_white_(is_white) {}

bool King::IsLegalMove(std::pair<Location, Location> turn) {
  
  // Can legally move in a one square radius  
  if (abs(turn.first.Row() - turn.second.Row()) <= 1 
        && abs(turn.first.Col() - turn.second.Col()) <= 1) {
    return true;
  }
    
  // Check for castling
  // Must be on beginning rank
  int valid_row;
  if (is_white_) {
    
    valid_row = kBoardSize - 1;
  } else {
    valid_row = 0;
  }
  
  
  if (turn.first.Row() == turn.second.Row() && turn.first.Row() == valid_row) {
    if (turn.first.Col() == 4 && (turn.second.Col() == 2 || turn.second.Col() == 6)) {
      // Can either move left or right two squares
      return true;
    }
  }
    
  return false;
}

std::vector<Location> King::CalculatePath(std::pair<Location,Location> turn) {
    
  std::vector<Location> path;
  
  // Move in one square radius
  if (abs(turn.first.Row() - turn.second.Row()) <= 1
      && abs(turn.first.Col() - turn.second.Col()) <= 1) {
    // Doesn't need any squares to be open
    return path;
  }

  // Check for castling
  int valid_row;
  if (is_white_) valid_row = kBoardSize - 1;
  else valid_row = 0;
  
  if (turn.first.Row() == turn.second.Row() && turn.first.Row() == valid_row && turn.first.Col() == 4) {
    
    if (turn.second.Col() == 2) {
      // Castled queen-side
      
      // Square next to rook must also be open
      auto point_after_rook = Location(valid_row, turn.second.Col() - 1);
      path.push_back(point_after_rook);
      
      // Add all points that the king must cross in order to castle
      for (int i = turn.second.Col(); i < turn.first.Col(); i++) {
        auto point = Location(valid_row, i);
        path.push_back(point);
      }
      
    } else if (turn.second.Col() == 6) {
      // Castle king-side
      
      // Add all points that the king must cross in order to castle
      for (int i = turn.first.Col() + 1; i <= turn.second.Col(); i++) {
        auto point = Location(valid_row, i);
        path.push_back(point);
      }
      
    }

  } 
    
  return path;
}
  
}