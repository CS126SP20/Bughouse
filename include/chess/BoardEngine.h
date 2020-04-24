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

// Represents one game. Holds the board and the board view and operates upon them.
class BoardEngine {
  
public:
  // Default Constructor
  BoardEngine() { };
  
  /**
   * @param chess_images - A ChessImages object that is shared with the other board.
   *                     Use to retreive images of the peices.
   * @param is_white TODO: Maybe delete this since each board starts as white
   * @param board_bounds - The pixel bounds for the board on the screen. Includes the border
   * @param top_box_bounds - The pixel bounds for the top box that holds black's extra pieces
   * @param bottom_box_bounds - The pixel bounds for the bottom box that holds white's extra pieces
   */
  BoardEngine(ChessImages* chess_images, bool is_white, 
      ci::Area board_bounds, ci::Area top_box_bounds, ci::Area bottom_box_bounds);

  // Called on click, updates turn_ according to the user action.
  void ProcessClick(ci::vec2 point);

  void Draw();
  Piece* SendPiece();
  void RecievePiece(Piece* piece);
  void Move();
  
  // A board object to represent the board
  Board board_;
  
  // A boardView object to manage UI
  BoardView board_view_;
  
  // Dynamically changed every time the board flips for the other player
  bool is_white_turn_;
  
private:
  // Represents a move of a piece from one point to another.
  // Updated every time the user clicks the screen
  std::pair<std::pair<int,int>,std::pair<int,int>> turn_;

  
  bool IsBoardClickValid(std::pair<int,int> click);
  void UpdateTurn(std::pair<int,int> click);
  bool IsMoveEmpty(std::pair<int,int> move);
  
};

}

#endif //FINALPROJECT_BOARDENGINE_H