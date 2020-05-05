//
// Created by tomok on 4/19/2020.
//
#include "chess/PieceClasses/Pawn.h"
#include <chess/BoardEngine.h>


namespace chess {
Pawn::Pawn(bool is_white)
  : is_poss_double_move_{false},
    is_white_{is_white},
    can_double_move_{true}
  { }

bool Pawn::IsLegalMove(std::pair<Location, Location> turn) {
  if (turn.first.Col() == EMPTY) {
    if (is_white_) {
      if (turn.second.Row() == 0) {
        return false;
      }
    } else {
      if (turn.second.Row() == kBoardSize - 1) {
        return false;
      }
    }
    return true;
  }
  
  bool is_valid = false;
  if (turn.first.Col() == turn.second.Col()) {
    if (is_white_) {
      if (turn.first.Row() == turn.second.Row() + 1) {
        is_valid = true;
      } else if (can_double_move_ && turn.first.Row() == turn.second.Row() + 2) {
        is_valid = true;
      }
    } else {
      if (turn.first.Row() == turn.second.Row() - 1) {
        is_valid = true;
      } else if (can_double_move_ && turn.first.Row() == turn.second.Row() - 2) {
        is_valid = true;
      }
    }
  }
  
  
  if (abs(turn.first.Col() - turn.second.Col()) == 1) {
    if (is_white_) {
      if (turn.first.Row() == turn.second.Row() + 1) {
        is_valid = true;
      }
    } else {
      if (turn.first.Row() == turn.second.Row() - 1) {
        is_valid = true;
      }
    }
  }
  
  
  return is_valid;
}

std::vector<Location> Pawn::GetPath(std::pair<Location, Location> turn) {
  std::vector<Location> path;
  
  if (turn.first.Col() == EMPTY) {
    path.push_back(turn.second);
    can_double_move_ = false;
    return path;
  }
  
  if (abs(turn.first.Col() - turn.second.Col()) == 1) {
    return path;
  }
  
  if (turn.first.Row() == turn.second.Row() + 2) {
    auto point = Location(turn.second.Row() + 1, turn.second.Col());
    path.push_back(point);
    is_poss_double_move_ = true;
  } else if (turn.first.Row() == turn.second.Row() - 2) {
    auto point = Location(turn.second.Row() - 1, turn.second.Col());
    path.push_back(point);
    is_poss_double_move_ = true;
  } else {
    is_poss_double_move_ = false;
  }
  path.push_back(turn.second);
  
  return path;
}

void Pawn::DoTurn() {
  can_double_move_ = false;
  is_poss_double_move_ = false;
}
}  