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

 public:
  BoardView() { };

  BoardView(ChessImages* chess_image, ci::Area board_bounds,
      ci::Area top_box_bounds, ci::Area bottom_box_bounds);
  
  // Called by the board engine to process a player click
  // Returns the Location of the click
  Location ProcessClick(const ci::vec2& point);
  
  // Called if the game state is promotion
  // Returns the choice that the player made
  // Returns a pawn if the choice was invalid
  PieceType GetPieceTypeFromClick(const ci::vec2& click);
  
  // Switch turns
  void SwapCurrentPlayerColor();  
  
  // Called to draw all of the elements
  void Draw(Board& board, Player& team1, Player& team2, 
      std::pair<Location, Location> turn, 
      std::pair<Location, Location> last_turn);

  // Draw pawn promotion only if the state is pawn promotion
  void DrawPawnPromotion();

 private:
  // All of the choices for the player during promotion
  const PieceType kPromotionChoices[4] = {QUEEN, KNIGHT, ROOK, BISHOP};
  // Represents all of the areas to draw on the UI
  Bounds bounds_;

  // A pointer to all of the loaded piece and board images
  ChessImages* images_;
  
  ci::Color current_player_color_;
  ci::Color current_opponent_color_;
  
  // Returns the location of the board click
  Location GetBoardSquareAtPoint(const ci::vec2& point);
  
  // Returns the location of the box click
  // Since it is in the box, the column entry of the locatoin
  // is empty, and the row entry is the index of the chosen piece
  Location GetHandIndexAtPoint(const ci::vec2& point);

  // Returns a square of the board as a rect
  ci::Rectf GetSquareAsRectf(Location& location);

  // Returns an index of the box as a rec
  ci::Rectf GetHandIndexAsRectf(ci::Area& box_bounds, int index);
  
  void DrawBoxes();
  void DrawBoard();
  
  // Highlights the current clicked box and the last move by the opponent
  void DrawTurns(std::pair<Location, Location> turn,
                 std::pair<Location, Location> last_turn,
                 const ci::Color& current_color, const ci::Color& opp_color);
  void DrawTurnSquare(Location location, bool is_white, const ci::Color& color);

  void DrawPieces(Board& board);
  void DrawHandPieces(Board& board);
  
  // Draws the time and the player teams
  void DrawPlayers(Player& player1, Player& player2);

  void PrintText(const std::string &text, const ci::Color &color, const cinder::vec2 &loc, const ci::ivec2& size);
  // Reports the time of the player as minute-second format, counting down
  std::string ReportTime(int seconds);
};  
  
}


#endif //FINALPROJECT_BOARDVIEW_H
