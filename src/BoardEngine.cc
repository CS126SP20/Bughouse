//
// Created by tomok on 4/21/2020.
//

#include "chess/BoardEngine.h"
#include <cinder/Area.h>
#include "chess/ChessImages.h"

namespace chess {
  
BoardEngine::BoardEngine(ChessImages *chess_images, ci::Area board_bounds, ci::Area top_box_bounds,
                         ci::Area bottom_box_bounds,
                         Player team1_player, Player team2_player)
    : turn_{Location(),Location()},
      last_turn_{Location(),Location()},
      board_view_{chess_images, board_bounds, top_box_bounds, bottom_box_bounds},
      team_2_player_{std::move(team2_player)},
      team_1_player_{std::move(team1_player)},
      current_game_state_{GameState::kPlaying},
      is_white_turn_{true}
    {
}

//================================================================
// Public member functions
//================================================================

void BoardEngine::ProcessClick(const ci::vec2& point) {
  
  if (current_game_state_ == GameState::kPawnPromotion) {
    // The click has to be a promotion choice    
    PieceType choice = board_view_.GetPieceTypeFromClick(point);

    // Pawn is default if none is chosen
    if (choice != PAWN) {
      // Only promote and swap turns once the valid choice is made
      board_.PromotePawn(choice, is_white_turn_);
      current_game_state_ = GameState::kPlaying;
      SwapTurns();
    }
    return;
  }
  
  // Normal click, get the location from board view
  Location click = board_view_.ProcessClick(point);
  if (!click.IsEmpty()) {
    if (click.Col() == EMPTY) {
      // They clicked the box
      UpdateTurnWithBoxClick(click);
    } else {
      // They clicked the board
      UpdateTurnWithBoardClick(click);
    }
  }
}

Piece* BoardEngine::Move() {
  if (current_game_state_ == GameState::kPawnPromotion) {
    // Don't do anything
    // Waiting on the player to choose a promotion
    return nullptr;
  }
  
  Piece* captured = nullptr;
  
  if (!turn_.first.IsEmpty() && !turn_.second.IsEmpty()) {
    // A full, valid turn has been made.
    // Update the board
    captured = board_.Update(turn_, is_white_turn_);
    
    // Update the state of the game
    current_game_state_ = UpdateGameState(captured);
    
    // Only swap turns if the game is still playing (don't swap yet if pawn promotion)
    if (current_game_state_ == GameState::kPlaying) {
      SwapTurns();
    }
  }
  
  // Make sure nobody ran out of time yet
  CheckTimeOut();
  
  // Give the captured piece to the other engine
  return captured;
}

void BoardEngine::ReceivePiece(Piece* piece) {
  if (piece == nullptr) return;
  board_.ReceivePiece(piece);
}

ci::Color BoardEngine::GetWinnerColor() {
  if (current_game_state_ == GameState::kTeam1Win) {
    return team_1_player_.team_color_;
  } else if (current_game_state_ == GameState::kTeam2Win) {
    return team_2_player_.team_color_;
  }
  return ci::Color(0,0,0);
}

void BoardEngine::Draw() {
  board_view_.Draw(board_, team_1_player_, team_2_player_, turn_, last_turn_);
  
  if (current_game_state_ == GameState::kPawnPromotion) {
    board_view_.DrawPawnPromotion();
  }
}

//================================================================
// Private member functions
//================================================================

GameState BoardEngine::UpdateGameState(Piece* captured) {
  GameState current_state;
  
  if (captured != nullptr && captured->GetPieceType() == KING) {
    // The opponent king was captured! Game over
    if (team_1_player_.is_white_ != captured->GetIsWhite()) {
      current_state = GameState::kTeam1Win;
    } else {
      current_state = GameState::kTeam2Win;
    }
    
  } else if (board_.HasPromotedPawn(is_white_turn_)) {
    // The player promoted a pawn
    current_state = GameState::kPawnPromotion;
    
  } else {
    // Nothing special happened 
    current_state = GameState::kPlaying;
  }
  
  return current_state;
}

void BoardEngine::UpdateTurnWithBoardClick(Location& click) {
  Piece* piece = board_.GetPieceAtSquare(click);
  
  if (piece != nullptr && (piece->GetIsWhite() == is_white_turn_)) {
    // Player chose a piece of their own color
    
    if (turn_.first == click) {
      // They un-clicked the previously piece
      turn_.first.Empty();
    } else {
      // They clicked a new piece
      turn_.first = click;
    }
  } else if (!turn_.first.IsEmpty() && turn_.second.IsEmpty()
            && (piece == nullptr || piece->GetIsWhite() != is_white_turn_)) {
    // They already chose a piece for the first move
    // The second piece they chose is either an empty square or a piece of opponent color
    
    if (board_.IsValidMove(std::make_pair(turn_.first, click), is_white_turn_)) {
      // If the move is valid, make it the second click
      turn_.second = click;
    } else {
      // If the move is invalid, un-click the first box
      turn_.first.Empty();
    }
  }
}

void BoardEngine::UpdateTurnWithBoxClick(Location& click) {
  // Make sure it is a valid index choice
  if (click.Row() < 0 || click.Col() >= board_.GetHandSize(is_white_turn_)) return;
  
  // If valid, make it the first click
  turn_.first = click;
}

void BoardEngine::CheckTimeOut() {
  if (team_2_player_.timer_.getSeconds() >= kMaxSeconds) {
    current_game_state_ = GameState::kTeam1Win;
  } else if (team_1_player_.timer_.getSeconds() >= kMaxSeconds) {
    current_game_state_ = GameState::kTeam2Win;
  }
}

void BoardEngine::SwapTurns() {
  // Update the last turn
  last_turn_ = turn_;
  // Empty the current turn
  turn_.first.Empty();
  turn_.second.Empty();
  
  // Swap colors
  is_white_turn_ = !is_white_turn_;
  board_view_.SwapCurrentPlayerColor();
  
  // Stop the current timer, start the opponent timer
  if (team_1_player_.is_white_ == is_white_turn_) {
    team_1_player_.timer_.resume();
    team_2_player_.timer_.stop();
  } else {
    team_1_player_.timer_.stop();
    team_2_player_.timer_.resume();
  }
}

}
