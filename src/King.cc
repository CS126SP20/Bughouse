//
// Created by tomok on 4/19/2020.
//


#include "chess/PieceClasses/King.h"
#include <chess/Board.h>

namespace chess {
  King::King(bool is_white) : is_white_(is_white) {}

  bool King::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    if (abs(turn.first.first - turn.second.first) <= 1 
          && abs(turn.first.second - turn.second.second) <= 1) {
      return true;
    }
    
    int valid_row;
    if (is_white_) {
      valid_row = kBoardSize - 1;
    } else {
      valid_row = 0;
    }
    
    if (turn.first.first == turn.second.first && turn.first.first == valid_row) {
      if (turn.first.second == 4 && (turn.second.second == 2 || turn.second.second == 6)) {
        return true;
      }
    }
    
    return false;
  }

  std::vector<std::pair<int,int>> King::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    std::vector<std::pair<int,int>> path;
    if (abs(turn.first.first - turn.second.first) <= 1
        && abs(turn.first.second - turn.second.second) <= 1) {
      return path;
    }

    int valid_row;
    if (is_white_) {
      valid_row = kBoardSize - 1;
    } else {
      valid_row = 0;
    }

    if (turn.first.first == turn.second.first && turn.first.first == valid_row && turn.first.second == 4) {
      if (turn.second.second == 2) {
        auto point_after_rook = std::make_pair(valid_row, turn.second.second - 1);
        path.push_back(point_after_rook);
        for (int i = turn.second.second; i < turn.first.second; i++) {
          auto point = std::make_pair(valid_row, i);
          path.push_back(point);
        }
      } else if (turn.second.second == 6) {
        for (int i = turn.first.second + 1; i <= turn.second.second; i++) {
          auto point = std::make_pair(valid_row, i);
          path.push_back(point);
        }
      }
      
    }
    
    return path;
  }
  
}