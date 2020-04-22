//
// Created by tomok on 4/21/2020.
//

#ifndef FINALPROJECT_BOARDENGINE_H
#define FINALPROJECT_BOARDENGINE_H

#include <cinder/Area.h>
#include <cinder/Color.h>
#include "chess/Board.h"
#include "cinder/Vector.h"
#include "utility"
#include "chess/ChessImages.h"
#include "chess/BoardView.h"

namespace chess {
  const int EMPTY = -1;


class BoardEngine {
  
public:
  BoardEngine() { };
  BoardEngine(ChessImages* chess_images, bool is_white, 
      ci::Area board_bounds, ci::Area top_box_bounds, ci::Area bottom_box_bounds);
  Board board_;
  BoardView board_view_;
  void ProcessClick(ci::vec2 point);
  bool is_white_turn_;
  void Draw();
  Piece* SendPiece();
  void RecievePiece(Piece* piece);
  void Move();
  std::pair<std::pair<int,int>,std::pair<int,int>> turn_;

private:



  bool IsBoardClickValid(std::pair<int,int> click);
  void UpdateTurn(std::pair<int,int> click);
  bool IsMoveEmpty(std::pair<int,int> move);
  
};

}

#endif //FINALPROJECT_BOARDENGINE_H