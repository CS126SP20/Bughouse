//
// Created by tomok on 4/19/2020.
//

#include <chess/BoardEngine.h>
#include "chess/PieceClasses/Bishop.h"

namespace chess {
  Bishop::Bishop(bool is_white, bool is_pawn)
    : is_white_(is_white),
      is_pawn_{is_pawn} {}
  
  bool Bishop::IsLegalMove(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    return (turn.first.second == EMPTY)
            || abs(turn.first.first - turn.second.first) == abs(turn.first.second - turn.second.second);
  }

  std::vector<std::pair<int,int>> Bishop::GetPath(std::pair<std::pair<int,int>,std::pair<int,int>> turn) {
    std::vector<std::pair<int,int>> path;
    
    int row1 = turn.first.first;
    int col1 = turn.first.second;
    int row2 = turn.second.first;
    int col2 = turn.second.second;

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
      auto point = std::make_pair(row1, col1);
      path.push_back(point);
    }

    return path;
  }
  
}