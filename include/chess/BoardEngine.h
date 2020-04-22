//
// Created by tomok on 4/21/2020.
//

#ifndef FINALPROJECT_BOARDENGINE_H
#define FINALPROJECT_BOARDENGINE_H

#include <cinder/Area.h>
#include "chess/Board.h"
#include "cinder/Vector.h"
#include "utility"

namespace chess {
  const int EMPTY = -1;
  struct Bounds {
    ci::Area board;
    ci::Area top_box;
    ci::Area bottom_box;
  };

class BoardEngine {
  
public:
  BoardEngine() { };
  BoardEngine(bool is_white, ci::Area board_bounds, ci::Area top_box_bounds, ci::Area bottom_box_bounds);
  Board board_;
  void ProcessClick(ci::vec2 point);
  bool is_white_turn_;
  Piece* SendPiece();
  void RecievePiece(Piece* piece);
  void Move();
  std::pair<std::pair<int,int>,std::pair<int,int>> turn_;
  Bounds bounds_;
private:
  std::pair<int,int> GetBoardSquareAtPoint(ci::vec2 point);
  bool IsBoardClickValid(std::pair<int,int> click);
  void UpdateTurn(std::pair<int,int> click);
  bool IsMoveEmpty(std::pair<int,int> move);
  
};

}

#endif //FINALPROJECT_BOARDENGINE_H