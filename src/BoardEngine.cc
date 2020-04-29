//
// Created by tomok on 4/21/2020.
//

#include "chess/BoardEngine.h"
#include <cinder/Area.h>

#include "chess/ChessImages.h"

namespace chess {
  
BoardEngine::BoardEngine(ChessImages* chess_image, bool is_white, 
    ci::Area board_bounds, ci::Area top_box_bounds,
    ci::Area bottom_box_bounds, Player team1_player, Player team2_player)
    : turn_{{EMPTY,EMPTY},{EMPTY,EMPTY}},
      is_white_turn_{is_white},
      board_view_{chess_image, is_white, board_bounds, top_box_bounds, bottom_box_bounds},
      team_2_player_{std::move(team2_player)},
      team_1_player_{std::move(team1_player)},
      current_game_state_{GameState::kPlaying}
    {
}

void BoardEngine::CheckTimeOut() {
  if (team_2_player_.timer_.getSeconds() >= kMaxSeconds) {
    current_game_state_ = GameState::kTeam1Win;
  } else if (team_1_player_.timer_.getSeconds() >= kMaxSeconds) {
    current_game_state_ = GameState::kTeam2Win;
  }
}


bool BoardEngine::IsMoveEmpty(std::pair<int,int> move) {
  return move.first == EMPTY && move.second == EMPTY;
}


void BoardEngine::ProcessClick(ci::vec2 point) {
  std::pair<int,int> click = board_view_.ProcessClick(point);
  if (!IsMoveEmpty(click)) {
    if (click.second == EMPTY) {
      UpdateTurnWithBoxClick(click);
    } else {
      UpdateTurnWithBoardClick(click);
    }
  }
}

void BoardEngine::UpdateTurnWithBoardClick(std::pair<int, int> click) {
  Piece* piece = board_.GetPieceAtSquare(click.first, click.second);
  
  if (piece != nullptr && (piece->GetIsWhite() == is_white_turn_)) {
    if (turn_.first == click) {
      turn_.first = std::make_pair(EMPTY, EMPTY);
    } else {
      turn_.first = click;
    }
  } else if (!IsMoveEmpty(turn_.first) && IsMoveEmpty(turn_.second) 
            && (piece == nullptr || piece->GetIsWhite() != is_white_turn_)) {
    if (board_.IsValidMove(std::make_pair(turn_.first, click), is_white_turn_)) {
      turn_.second = click;
    } else {
      turn_.first = std::make_pair(EMPTY, EMPTY);
    }
    
  }
  
  
}

void BoardEngine::UpdateTurnWithBoxClick(std::pair<int, int> click) {
  if (click.first < 0 || click.first >= board_.GetHandSize(is_white_turn_)) return;
  turn_.first = click;
}

void BoardEngine::ReceivePiece(Piece* piece) {
  if (piece == nullptr) return;
  board_.ReceivePiece(piece);
}

Piece* BoardEngine::Move() {

  Piece* captured = nullptr;
  if (!IsMoveEmpty(turn_.first) && !IsMoveEmpty(turn_.second)) {
    captured = board_.Update(turn_, is_white_turn_);
    
    current_game_state_ = UpdateGameState(captured);
    SwapTurns();
  }
  
  CheckTimeOut();
  return captured;
}

void BoardEngine::SwapTurns() {
  turn_ = std::make_pair(std::make_pair(EMPTY, EMPTY), std::make_pair(EMPTY, EMPTY));
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
  board_view_.Draw(board_, team_1_player_, team_2_player_);
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
