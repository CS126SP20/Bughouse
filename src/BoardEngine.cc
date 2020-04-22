//
// Created by tomok on 4/21/2020.
//

#include "chess/BoardEngine.h"
#include "../apps/my_app.h"
#include <cinder/Area.h>

namespace chess {
  
BoardEngine::BoardEngine(bool is_white, ci::Area board_bounds, ci::Area top_box_bounds, ci::Area bottom_box_bounds)
    : turn_{{EMPTY,EMPTY},{EMPTY,EMPTY}},
      is_white_turn_(is_white)
    {
  bounds_.board = board_bounds;
  bounds_.bottom_box = bottom_box_bounds;
  bounds_.top_box = top_box_bounds;
  
}

void BoardEngine::ProcessClick(ci::vec2 point) {
  std::pair<int,int> click_loc;
  int hand_click_loc;
  if (point.x > bounds_.board.getX1() + myapp::kBorder && point.x < bounds_.board.getX2() - myapp::kBorder
      && point.y > bounds_.board.getY1() + myapp::kBorder && point.y < bounds_.board.getY2() - myapp::kBorder) {
    click_loc = GetBoardSquareAtPoint(point);
    if (IsBoardClickValid(click_loc)) {
      UpdateTurn(click_loc);
    }
  } else if (point.x > bounds_.bottom_box.getX1() && point.x < bounds_.bottom_box.getX2()
      && point.y > bounds_.bottom_box.getY1(), point.y < bounds_.bottom_box.getY2()) {
    
  }
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

void BoardEngine::UpdateTurn(std::pair<int, int> click) {
  if (IsMoveEmpty(turn_.first)) {
    turn_.first = click;
  } else if (IsMoveEmpty(turn_.second)) {
//    if (board_.GetPieceAtLocWhiteView(click_loc.first, click_loc.second)->GetIsWhite() == is_white_turn_) {
//      turn_.second = click_loc;
//    }
    turn_.second = click;
    Move();
  }
}


void BoardEngine::Move() {
  if (!IsMoveEmpty(turn_.first) && !IsMoveEmpty(turn_.second)) {
    board_.Update(turn_);
    turn_ = std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
  }
}

std::pair<int,int> BoardEngine::GetBoardSquareAtPoint(ci::vec2 point) {
  if (is_white_turn_) {
    for (int row = 0; row < kBoardSize; row++) {
      for (int col = 0; col < kBoardSize; col++) {
        if (point.x > bounds_.board.getX1() + myapp::kBorder + col*myapp::kSquareLen
            && point.x <= bounds_.board.getX1() + myapp::kBorder + (col+1)*myapp::kSquareLen
            && point.y > bounds_.board.getY1() + myapp::kBorder + row*myapp::kSquareLen
            && point.y <= bounds_.board.getY1() + myapp::kBorder + (row+1)*myapp::kSquareLen) {

          return std::make_pair(row, col);
        }
      }

    }
  }
}



}
