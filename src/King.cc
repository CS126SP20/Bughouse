//
// Created by tomok on 4/19/2020.
//


#include "chess/PieceClasses/King.h"
#include <chess/Board.h>

namespace chess {
  King::King(bool is_white) : is_white_(is_white) {}

  bool King::IsLegalMove(std::pair<Location, Location> turn) {
    if (abs(turn.first.Row() - turn.second.Row()) <= 1 
          && abs(turn.first.Col() - turn.second.Col()) <= 1) {
      return true;
    }
    
    int valid_row;
    if (is_white_) {
      valid_row = kBoardSize - 1;
    } else {
      valid_row = 0;
    }
    
    if (turn.first.Row() == turn.second.Row() && turn.first.Row() == valid_row) {
      if (turn.first.Col() == 4 && (turn.second.Col() == 2 || turn.second.Col() == 6)) {
        return true;
      }
    }
    
    return false;
  }

  std::vector<Location> King::GetPath(std::pair<Location,Location> turn) {
    std::vector<Location> path;
    if (abs(turn.first.Row() - turn.second.Row()) <= 1
        && abs(turn.first.Col() - turn.second.Col()) <= 1) {
      return path;
    }

    int valid_row;
    if (is_white_) {
      valid_row = kBoardSize - 1;
    } else {
      valid_row = 0;
    }

    if (turn.first.Row() == turn.second.Row() && turn.first.Row() == valid_row && turn.first.Col() == 4) {
      if (turn.second.Col() == 2) {
        auto point_after_rook = Location(valid_row, turn.second.Col() - 1);
        path.push_back(point_after_rook);
        for (int i = turn.second.Col(); i < turn.first.Col(); i++) {
          auto point = Location(valid_row, i);
          path.push_back(point);
        }
      } else if (turn.second.Col() == 6) {
        for (int i = turn.first.Col() + 1; i <= turn.second.Col(); i++) {
          auto point = Location(valid_row, i);
          path.push_back(point);
        }
      }
      
    }
    
    return path;
  }
  
}