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
    return IsValidPlacement(turn.second);
  }
  
  
  bool is_valid = false;
  if (turn.first.Col() == turn.second.Col()) {
    
    if (is_white_) {
      if (turn.first.Row() == turn.second.Row() + 1) {
        // Pawn can move one space forward
        is_valid = true;
      } else if (can_double_move_ && turn.first.Row() == turn.second.Row() + 2) {
        // Pawn can move two spaces forward if it is first move
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
  
  // Pawn can move diagonally one space forward
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
    // The pawn needs to be placed on an empty square
    path.push_back(turn.second);
    
    // If the pawn is placed from the hand, it can no longer double move
    can_double_move_ = false;
    return path;
  }
  
  // The pawn moved diagonally, so it must be a capture (en passant or normal)
  if (abs(turn.first.Col() - turn.second.Col()) == 1) {
    // Empty path for capture
    return path;
  }
  
  // Double move checks
  if (turn.first.Row() == turn.second.Row() + 2) {
    
    // Point in front of pawn must be empty
    auto point = Location(turn.second.Row() + 1, turn.second.Col());
    path.push_back(point);
    is_poss_double_move_ = true;
    
  } else if (turn.first.Row() == turn.second.Row() - 2) {
    
    // Point in front of pawn must be empty
    auto point = Location(turn.second.Row() - 1, turn.second.Col());
    path.push_back(point);
    is_poss_double_move_ = true;
    
  } else {
    // Not a double move
    is_poss_double_move_ = false;
  }
  
  // The pawn must move to an empty square if it moves forward
  path.push_back(turn.second);
  
  return path;
}

void Pawn::DoTurn() {
  // Called after the pawn actually moves.
  // Turn off double moving, since the pawn moved
  can_double_move_ = false;
  is_poss_double_move_ = false;
}

bool Pawn::IsValidPlacement(Location pawn_destination) {
  // The pawn cannot be placed on the last rank
  if (is_white_) {
    if (pawn_destination.Row() == 0) {
      return false;
    }
  } else {
    if (pawn_destination.Row() == kBoardSize - 1) {
      return false;
    }
  }
  return true;
}

}  