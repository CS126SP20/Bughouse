//
// Created by tomok on 4/19/2020.
//

#include <chess/BoardEngine.h>
#include "chess/PieceClasses/Pawn.h"

namespace chess {
Pawn::Pawn(bool is_white)
  : is_poss_double_move_{false},
    is_white_{is_white},
    can_double_move_{true}
  { }

bool Pawn::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
  if (turn.first.second == EMPTY) {
    if (is_white_) {
      if (turn.second.first == 0) {
        return false;
      }
    } else {
      if (turn.second.first == kBoardSize - 1) {
        return false;
      }
    }
    can_double_move_ = false;
    return true;
  }
  
  bool is_valid = false;
  if (turn.first.second == turn.second.second) {
    if (is_white_) {
      if (turn.first.first == turn.second.first + 1) {
        is_valid = true;
      } else if (can_double_move_ && turn.first.first == turn.second.first + 2) {
        is_valid = true;
      }
    } else {
      if (turn.first.first == turn.second.first - 1) {
        is_valid = true;
      } else if (can_double_move_ && turn.first.first == turn.second.first - 2) {
        is_valid = true;
      }
    }
  }
  return is_valid;
}

std::vector<std::pair<int,int>> Pawn::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
  std::vector<std::pair<int,int>> path;
  
  if (turn.first.second == EMPTY) {
    path.push_back(turn.second);
    return path;
  }
  
  if (turn.first.first == turn.second.first + 2) {
    auto point = std::make_pair(turn.second.first + 1, turn.second.second);
    path.push_back(point);
    is_poss_double_move_ = true;
  } else if (turn.first.first == turn.second.first - 2) {
    auto point = std::make_pair(turn.second.first - 1, turn.second.second);
    path.push_back(point);
    is_poss_double_move_ = true;
  } else {
    is_poss_double_move_ = false;
  }
  path.push_back(turn.second);
  
  return path;
}

void Pawn::DoTurn() {
  if (is_poss_double_move_) {
    can_double_move_ = false;
    is_poss_double_move_ = false;
  }
}
}  