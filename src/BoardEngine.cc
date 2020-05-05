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

void BoardEngine::CheckTimeOut() {
  if (team_2_player_.timer_.getSeconds() >= kMaxSeconds) {
    current_game_state_ = GameState::kTeam1Win;
  } else if (team_1_player_.timer_.getSeconds() >= kMaxSeconds) {
    current_game_state_ = GameState::kTeam2Win;
  }
}


void BoardEngine::ProcessClick(ci::vec2 point) {
  if (current_game_state_ == GameState::kPawnPromotion) {
    PieceType choice = board_view_.GetPieceTypeFromClick(point);
    if (choice != PAWN) {
      board_.PromotePawn(choice, is_white_turn_);
      current_game_state_ = GameState::kPlaying;
      SwapTurns();
    }
    return;
  }
  
  Location click = board_view_.ProcessClick(point);
  if (!click.IsEmpty()) {
    if (click.Col() == EMPTY) {
      UpdateTurnWithBoxClick(click);
    } else {
      UpdateTurnWithBoardClick(click);
    }
  }
}

void BoardEngine::UpdateTurnWithBoardClick(Location& click) {
  Piece* piece = board_.GetPieceAtSquare(click);
  
  if (piece != nullptr && (piece->GetIsWhite() == is_white_turn_)) {
    if (turn_.first == click) {
      turn_.first.Empty();
    } else {
      turn_.first = click;
    }
  } else if (!turn_.first.IsEmpty() && turn_.second.IsEmpty()
            && (piece == nullptr || piece->GetIsWhite() != is_white_turn_)) {
    if (board_.IsValidMove(std::make_pair(turn_.first, click), is_white_turn_)) {
      turn_.second = click;
    } else {
      turn_.first.Empty();
    }
    
  }
  
}

void BoardEngine::UpdateTurnWithBoxClick(Location& click) {
  if (click.Row() < 0 || click.Col() >= board_.GetHandSize(is_white_turn_)) return;
  turn_.first = click;
}

void BoardEngine::ReceivePiece(Piece* piece) {
  if (piece == nullptr) return;
  board_.ReceivePiece(piece);
}

Piece* BoardEngine::Move() {
  if (current_game_state_ == GameState::kPawnPromotion) {
    return nullptr;
  }
  Piece* captured = nullptr;
  
  if (!turn_.first.IsEmpty() && !turn_.second.IsEmpty()) {
    
    captured = board_.Update(turn_, is_white_turn_);
    
    current_game_state_ = UpdateGameState(captured);
    if (current_game_state_ == GameState::kPlaying) {
      SwapTurns();
    }
  }
  
  CheckTimeOut();
  return captured;
}

void BoardEngine::SwapTurns() {
  last_turn_ = turn_;
  turn_.first.Empty();
  turn_.second.Empty();
  is_white_turn_ = !is_white_turn_;
  board_view_.SwapCurrentPlayerColor();
  if (team_1_player_.is_white_ == is_white_turn_) {
    team_1_player_.timer_.resume();
    team_2_player_.timer_.stop();
  } else {
    team_1_player_.timer_.stop();
    team_2_player_.timer_.resume();
  }
}

GameState BoardEngine::UpdateGameState(Piece* captured) {
  GameState current_state;
  if (captured != nullptr && captured->GetPieceType() == KING) {
    if (team_1_player_.is_white_ != captured->GetIsWhite()) {
      current_state = GameState::kTeam1Win;
    } else {
      current_state = GameState::kTeam2Win;
    }
  } else if (board_.HasPromotedPawn(is_white_turn_)) {
    current_state = GameState::kPawnPromotion;
  } else {
    current_state = GameState::kPlaying;
  }
  
  return current_state;
}

void BoardEngine::Draw() {
  board_view_.Draw(board_, team_1_player_, team_2_player_, turn_, last_turn_);
  if (current_game_state_ == GameState::kPawnPromotion) {
    board_view_.DrawPawnPromotion();
  }
}


ci::Color BoardEngine::GetWinnerColor() {
  if (current_game_state_ == GameState::kTeam1Win) {
    return team_1_player_.team_color_;
  } else if (current_game_state_ == GameState::kTeam2Win) {
    return team_2_player_.team_color_;
  }
  return ci::Color(0,0,0);
}


}
