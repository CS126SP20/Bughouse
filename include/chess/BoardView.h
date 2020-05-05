//
// Created by tomok on 4/21/2020.
//

#ifndef FINALPROJECT_BOARDVIEW_H
#define FINALPROJECT_BOARDVIEW_H

#include <cinder/Area.h>
#include "Player.h"
#include "chess/Board.h"
#include <chess/GameState.h>
#include <chess/ChessImages.h>

namespace chess {
 
struct Bounds {
    ci::Area board;
    ci::Area top_box;
    ci::Area bottom_box;
    ci::Area promotion_box;
};

class BoardView {
  Bounds bounds_;
public:
  BoardView() { };

  BoardView(ChessImages* chess_image, bool is_white, ci::Area board_bounds,
      ci::Area top_box_bounds, ci::Area bottom_box_bounds);
  std::pair<int, int> ProcessClick(ci::vec2 point);
  void SwapCurrentPlayerColor();  
  void Draw(Board& board, Player team1, Player team2);
  PieceType GetPieceTypeFromClick(ci::vec2 click);
  void DrawPawnPromotion();

private:
  PieceType kPromotionChoices[4] = {QUEEN, KNIGHT, ROOK, BISHOP};
  std::pair<int,int> GetBoardSquareAtPoint(ci::vec2 point);
  std::pair<int,int> GetHandIndexAtPoint(ci::vec2 point);
  ChessImages* images_;
  void DrawBoxes();
  void DrawBoard();
  void DrawPieces(Board& board);
  void DrawHandPieces(Board& board);

  void DrawPlayers(Player& player1, Player& player2);
  ci::Rectf GetSquareAsRectf(int row, int col);
  ci::Rectf GetHandIndexAsRectf(ci::Area& box_bounds, int index);
  ci::Color current_player_color_;
  ci::Color current_opponent_color_;
  void PrintText(const std::string &text, const ci::Color &color, const cinder::vec2 &loc, const ci::ivec2& size);
  std::string ReportTime(int seconds);
};  
  
}


#endif //FINALPROJECT_BOARDVIEW_H
