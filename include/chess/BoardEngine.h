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
#include <chess/GameState.h>
#include "chess/ChessImages.h"
#include "chess/BoardView.h"
#include "chess/Player.h"
#include "chess/Location.h"
#include <cinder/audio/Voice.h>

namespace chess {
  const int kMaxSeconds = 300;
  
  // Represents one game. Holds the board and the board view and operates upon them.
class BoardEngine {
  
public:
  
  // Default Constructor
  BoardEngine() { };
  
  /**
   * @param chess_images - A ChessImages object that is shared with the other board.
   *                     Use to retreive images of the peices.
   * @param board_bounds - The pixel bounds for the board on the screen. Includes the border
   * @param top_box_bounds - The pixel bounds for the top box that holds black's extra pieces
   * @param bottom_box_bounds - The pixel bounds for the bottom box that holds white's extra pieces
   */
  BoardEngine(ChessImages *chess_images, ci::Area board_bounds, ci::Area top_box_bounds, ci::Area bottom_box_bounds,
              Player team1_player, Player team2_player);
  
  // Called on click, updates turn_ according to the user action.
  void ProcessClick(const ci::vec2& point);

  // Called by update, moves board if turn is full
  Piece* Move();
  
  // Wrapper for the board object to receive a piece from the other engine
  void ReceivePiece(Piece* piece);
  
  // Check to make sure the game is still going
  bool IsGameEnd() { return current_game_state_ == GameState::kTeam1Win 
                            || current_game_state_ == GameState::kTeam2Win; };
  
  // Called at the end of the round
  ci::Color GetWinnerColor();

  // Called by cinder draw. Draws board view.
  void Draw();
  
private:
  // State of game. Starts as kPlaying
  GameState current_game_state_;

  // Dynamically changed every time the board flips for the other player
  bool is_white_turn_;

  // A board object to represent the board
  Board board_;

  // A boardView object to manage UI
  BoardView board_view_;
  
  // Represents a move of a piece from one point to another.
  // Updated every time the user clicks the screen
  std::pair<Location, Location> turn_;
  
  // The last move that the player made
  std::pair<Location, Location> last_turn_;
  
  // Players know their team, their time, and their color
  Player team_1_player_;
  Player team_2_player_;
  
  // Sfx
  ci::audio::VoiceRef sfx_;
  
  // Called by Move, changes game state depending on the board move
  GameState UpdateGameState(Piece* captured);
  
  // Called by process click
  // Updates the turn with the click location
  void UpdateTurnWithBoardClick(Location& click);
  void UpdateTurnWithBoxClick(Location& click);

  // Called during Move, to make sure the game hasn't ended
  void CheckTimeOut();
  
  // Called by move, swaps current players and changes timers
  void SwapTurns();
  
};

}

#endif //FINALPROJECT_BOARDENGINE_H