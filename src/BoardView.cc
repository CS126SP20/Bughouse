//
// Created by tomok on 4/21/2020.
//

#include <chess/BoardEngine.h>
#include <chess/ChessImages.h>
#include "chess/BoardView.h"
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/app/App.h>

namespace chess {

BoardView::BoardView(ChessImages* chess_image,
    bool is_white, ci::Area board_bounds, ci::Area top_box_bounds, ci::Area bottom_box_bounds)
{
  bounds_.board = board_bounds;
  bounds_.bottom_box = bottom_box_bounds;
  bounds_.top_box = top_box_bounds;
  if (is_white) {
    current_player_color_ = kWhiteCol;
    current_opponent_color_ = kBlackCol;
  } else {
    current_player_color_ = kBlackCol;
    current_opponent_color_ = kWhiteCol;
  }
  images_ = chess_image;
}  



std::pair<int, int> BoardView::ProcessClick(ci::vec2 point) {
  std::pair<int,int> click_loc = std::make_pair(EMPTY, EMPTY);

  if (point.x > bounds_.board.getX1() + kBorder && point.x < bounds_.board.getX2() - kBorder
      && point.y > bounds_.board.getY1() + kBorder && point.y < bounds_.board.getY2() - kBorder) {
    click_loc = GetBoardSquareAtPoint(point);

  } else if (point.x > bounds_.bottom_box.getX1() && point.x < bounds_.bottom_box.getX2()
             && point.y > bounds_.bottom_box.getY1(), point.y < bounds_.bottom_box.getY2()) {
    
  }
  
  return click_loc;
}

std::pair<int,int> BoardView::GetBoardSquareAtPoint(ci::vec2 point) {
  int col = std::floor((point.x - bounds_.board.getX1() - kBorder) / kSquareLen);
  int row = std::floor((point.y - bounds_.board.getY1() - kBorder) / kSquareLen);
  if (col < 0 || row < 0) {
    return std::make_pair(EMPTY,EMPTY);
  } else if (current_player_color_ == kWhiteCol) {
    return std::make_pair(row , col);
  } else {
    return std::make_pair(kBoardSize - 1 - row, kBoardSize - 1 - col);
  }
}

void BoardView::SwapCurrentPlayerColor() {
  if (current_player_color_ == kWhiteCol) {
    current_player_color_ = kBlackCol;
    current_opponent_color_ = kWhiteCol;
  } else {
    current_player_color_ = kWhiteCol;
    current_opponent_color_ = kBlackCol;
  }
}

void BoardView::Draw(Board& board) {
  DrawBoxes();
  DrawBoard();
  DrawPieces(board);
}

void BoardView::DrawBoxes() {
  ci::gl::color(1.0f, 1.0f, 1.0f);
  
  ci::gl::color(current_opponent_color_); 
  ci::Rectf top = ci::Rectf(bounds_.top_box);
  ci::gl::drawSolidRect(top);


  ci::gl::color(current_player_color_);
  ci::Rectf low = ci::Rectf(bounds_.bottom_box);
  ci::gl::drawSolidRect(low);

  ci::gl::color(1.0f, 1.0f, 1.0f);
  
}
void BoardView::DrawBoard() {
  ci::vec2 center = ci::app::getWindowCenter();
  
  ci::gl::draw(images_->RetrieveBoardImage(current_player_color_),
      ci::Rectf(bounds_.board));

}

void BoardView::DrawPieces(Board& board) {
  for (int row = 0; row < chess::kBoardSize; row++) {
    for (int col = 0; col < chess:: kBoardSize; col++) {
      if (current_player_color_ == kWhiteCol) {
        if (board.GetPieceAtLocWhiteView(row, col) == nullptr) {
          continue;
        } else {
          ci::gl::draw(images_->RetrievePieceImage(board.GetPieceAtLocWhiteView(row, col)),
                       GetSquareAsRectf(bounds_.board, row, col));
        }
      } else {
        if (board.GetPieceAtLocBlackView(row, col) == nullptr) {
          continue;
        } else {

          ci::gl::draw(images_->RetrievePieceImage(board.GetPieceAtLocBlackView(row, col)),
                       GetSquareAsRectf(bounds_.board, row, col));
        }
      }
    }
  }
}

ci::Rectf BoardView::GetSquareAsRectf(ci::Area& board_bounds, int row, int col) {
  ci::vec2 center = ci::app::getWindowCenter();
  auto square = ci::Rectf(col * kSquareLen + board_bounds.getX1() + kBorder, 
            row * kSquareLen + board_bounds.getY1() + kBorder,
            (col+1) * kSquareLen + board_bounds.getX1() + kBorder, 
            (row+1) * kSquareLen + board_bounds.getY1() + kBorder);
  return square;
}

}