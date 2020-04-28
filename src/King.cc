//
// Created by tomok on 4/19/2020.
//

#include "chess/PieceClasses/King.h"

namespace chess {
  King::King(bool is_white) : is_white_(is_white) {}

  bool King::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    if (abs(turn.first.first - turn.second.first) <= 1 
          && abs(turn.first.second - turn.second.second) <= 1) {
      return true;
    }
    
    if (turn.first.first == turn.second.first) {
      if (can_castle_ && turn.first.second == 4 && (turn.second.second == 2 || turn.second.second == 6)) {
        return true;
      }
    }
  }

  std::vector<std::pair<int,int>> King::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    std::vector<std::pair<int,int>> path;
    return path;
  }
  
  void King::DoTurn() {
    
  }
}