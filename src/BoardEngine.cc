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

bool BoardEngine::IsBoardClickValid(std::pair<int, int> click) {
//  Piece* piece;
//  if (is_white_turn_) {
//    piece = board_.GetPieceAtLocWhiteView(click.first, click.second);
//  } else {
//    piece = board_.GetPieceAtLocBlackView(click.first, click.second);
//  }
//
//  if (piece == nullptr || piece->GetIsWhite() != is_white_turn_) {
//    return false;
//  }

  return true;
  
}

void BoardEngine::ProcessClick(ci::vec2 point) {
  std::pair<int,int> click = board_view_.ProcessClick(point);
  if (!IsMoveEmpty(click)) {
    UpdateTurn(click);
  }
}

void BoardEngine::UpdateTurn(std::pair<int, int> click) {
  Piece* piece = board_.GetPieceAtLocWhiteView(click.first, click.second);
  
  if (piece != nullptr && piece->GetIsWhite() == is_white_turn_ && IsMoveEmpty(turn_.first)) {
    turn_.first = click;
  } else if (IsMoveEmpty(turn_.second)) {
    if (turn_.first == click) {
      turn_.first = std::make_pair(EMPTY, EMPTY);
    } else if (piece == nullptr || piece->GetIsWhite() != is_white_turn_) {
      turn_.second = click;
    }
  }
  
}


void BoardEngine::Move() {
  if (!IsMoveEmpty(turn_.first) && !IsMoveEmpty(turn_.second)) {
    Piece* captured = board_.Update(turn_);
    turn_ = std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
    is_white_turn_ = !is_white_turn_;
    board_view_.SwapCurrentPlayerColor();
  }
}

void BoardEngine::Draw() {
  board_view_.Draw(board_);
}



}
