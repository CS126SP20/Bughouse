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
    return (turn.first.Col() == EMPTY)
            || abs(turn.first.Row() - turn.second.Row()) == abs(turn.first.Col() - turn.second.Col());
  }

  std::vector<Location> Bishop::GetPath(std::pair<Location, Location> turn) {
    std::vector<Location> path;
    
    int row1 = turn.first.Row();
    int col1 = turn.first.Col();
    int row2 = turn.second.Row();
    int col2 = turn.second.Col();

    if (col1 == EMPTY) {
      path.push_back(turn.second);
      return path;
    }
    
    int sign_y;
    int sign_x;
    
    if (row2 > row1) {
      sign_y = 1;
    } else {
      sign_y = -1;
    }
    
    if (col2 > col1) {
      sign_x = 1;
    } else {
      sign_x = -1;
    }

    while ((abs(col1 - col2) > 1 ) && (abs(row1 - row2) > 1)) {
      col1 += sign_x;
      row1 += sign_y;
      auto point = Location(row1, col1);
      path.push_back(point);
    }

    return path;
  }
  
}