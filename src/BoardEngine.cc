//
// Created by tomok on 4/21/2020.
//

#include "chess/BoardEngine.h"
#include <cinder/Area.h>
#include "chess/ChessImages.h"

namespace chess {
  
BoardEngine::BoardEngine(ChessImages* chess_image, bool is_white, 
    ci::Area board_bounds, ci::Area top_box_bounds, ci::Area bottom_box_bounds)
    : turn_{{EMPTY,EMPTY},{EMPTY,EMPTY}},
      is_white_turn_{is_white},
      board_view_{chess_image, is_white, board_bounds, top_box_bounds, bottom_box_bounds}
    {
}


bool BoardEngine::IsMoveEmpty(std::pair<int,int> move) {
  return move.first == EMPTY && move.second == EMPTY;
}

//bool BoardEngine::IsBoardClickValid(std::pair<int, int> click) {
////  Piece* piece;
////  if (is_white_turn_) {
////    piece = board_.GetPieceAtSquare(click.first, click.second);
////  } else {
////    piece = board_.GetPieceAtLocBlackView(click.first, click.second);
////  }
////
////  if (piece == nullptr || piece->GetIsWhite() != is_white_turn_) {
////    return false;
////  }
//
//  return true;
//  
//}

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
    if (turn_.first.second == EMPTY) {
      if (piece == nullptr) turn_.second = click;
    } else {
      if (board_.IsValidMove(std::make_pair(turn_.first, click), is_white_turn_)) {
        turn_.second = click;
      }
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
    turn_ = std::make_pair(std::make_pair(EMPTY, EMPTY), std::make_pair(EMPTY, EMPTY));
    is_white_turn_ = !is_white_turn_;
    board_view_.SwapCurrentPlayerColor();
  }
  return captured;
}

void BoardEngine::Draw() {
  board_view_.Draw(board_);
}



}
