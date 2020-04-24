//
// Created by tomok on 4/21/2020.
//

#ifndef FINALPROJECT_BOARDVIEW_H
#define FINALPROJECT_BOARDVIEW_H

#include <cinder/Area.h>

namespace chess {
 
struct Bounds {
    ci::Area board;
    ci::Area top_box;
    ci::Area bottom_box;
};

class BoardView {
  Bounds bounds_;
public:
  BoardView() { };

  BoardView(ChessImages* chess_image, bool is_white, ci::Area board_bounds,
      ci::Area top_box_bounds, ci::Area bottom_box_bounds);
  std::pair<int, int> ProcessClick(ci::vec2 point);
  void SwapCurrentPlayerColor();  
  void Draw(Board& board);

private:
  std::pair<int,int> GetBoardSquareAtPoint(ci::vec2 point);
  std::pair<int,int> GetHandIndexAtPoint(ci::vec2 point);
  ChessImages* images_;
  void DrawBoxes();
  void DrawBoard();
  void DrawPieces(Board& board);
  ci::Rectf GetSquareAsRectf(ci::Area& board_bounds, int row, int col);
  ci::Color current_player_color_;
  ci::Color current_opponent_color_;
};  
  
}


#endif //FINALPROJECT_BOARDVIEW_H
