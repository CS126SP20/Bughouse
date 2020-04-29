//
// Created by tomok on 4/21/2020.
//


#include "chess/BoardView.h"
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/app/App.h>
#include <chess/BoardEngine.h>


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
  is_pawn_promotion_ = false;
}  

void BoardView::UpdateGameState(GameState game_state) {
  is_pawn_promotion_ = game_state == GameState::kPawnPromotion;
}

std::pair<int, int> BoardView::ProcessClick(ci::vec2 point) {
  std::pair<int,int> click_loc = std::make_pair(EMPTY, EMPTY);

  if (point.x > bounds_.board.getX1() + kBorder && point.x < bounds_.board.getX2() - kBorder
      && point.y > bounds_.board.getY1() + kBorder && point.y < bounds_.board.getY2() - kBorder) {
    click_loc = GetBoardSquareAtPoint(point);

  } else if (point.x > bounds_.bottom_box.getX1() && point.x < bounds_.bottom_box.getX2()
             && point.y > bounds_.bottom_box.getY1(), point.y < bounds_.bottom_box.getY2()) {
    click_loc = GetHandIndexAtPoint(point);
  }
  
  return click_loc;
}

std::pair<int,int> BoardView::GetBoardSquareAtPoint(ci::vec2 point) {
  int col = std::floor((point.x - bounds_.board.getX1() - kBorder) / kSquareLen);
  int row = std::floor((point.y - bounds_.board.getY1() - kBorder) / kSquareLen);
  if (col < 0 || row < 0 || col >= kBoardLen || row >= kBoardLen) {
    return std::make_pair(EMPTY,EMPTY);
  } else if (current_player_color_ == kWhiteCol) {
    return std::make_pair(row , col);
  } else {
    return std::make_pair(kBoardSize - 1 - row, kBoardSize - 1 - col);
  }
}

std::pair<int,int> BoardView::GetHandIndexAtPoint(ci::vec2 point) {
  int col = std::floor((point.x - bounds_.bottom_box.getX1()) / kHandSquareLen);
  int row = std::floor((point.y - bounds_.bottom_box.getY1()) / kHandSquareLen);
  if (col < 0 || row < 0 || col >= kBoxLenIndex || row >= kBoxHeightIndex) {
    return std::make_pair(EMPTY,EMPTY);
  } else {
    return std::make_pair(col + row*kBoxLenIndex, EMPTY);
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

void BoardView::Draw(Board& board, Player team1, Player team2) {
  ci::gl::color(1.0f,1.0f,1.0f);
  DrawBoxes();
  ci::gl::color(1.0f, 1.0f, 1.0f);
  DrawBoard();
  ci::gl::color(1.0f, 1.0f, 1.0f);
  DrawPieces(board);
  ci::gl::color(1.0f, 1.0f, 1.0f);
  DrawHandPieces(board);
  ci::gl::color(1.0f, 1.0f, 1.0f);
  DrawPlayers(team1, team2);
  
//  if (is_pawn_promotion_) {
//    DrawPawnPromotion();
//  }
}

void BoardView::DrawBoxes() {
  ci::gl::color(1.0f, 1.0f, 1.0f);
  
  ci::gl::color(current_opponent_color_); 
  ci::Rectf top = ci::Rectf(bounds_.top_box);
  ci::gl::drawSolidRect(top);


  ci::gl::color(current_player_color_);
  ci::Rectf low = ci::Rectf(bounds_.bottom_box);
  ci::gl::drawSolidRect(low);
  
}
void BoardView::DrawBoard() {
  ci::vec2 center = ci::app::getWindowCenter();
  
  ci::gl::draw(images_->RetrieveBoardImage(kWhiteCol),
      ci::Rectf(bounds_.board));

}

void BoardView::DrawPieces(Board& board) {
  for (int row = 0; row < chess::kBoardSize; row++) {
    for (int col = 0; col < chess:: kBoardSize; col++) {
      if (current_player_color_ == kWhiteCol) {
        if (board.GetPieceAtSquare(row, col) == nullptr) {
          continue;
        } else {
          ci::gl::draw(images_->RetrievePieceImage(board.GetPieceAtSquare(row, col)),
                       GetSquareAsRectf(row, col));
        }
      } else {
        if (board.GetPieceAtSquare(kBoardSize - 1 - row, kBoardSize - 1 - col) == nullptr) {
          continue;
        } else {

          ci::gl::draw(images_->RetrievePieceImage(
              board.GetPieceAtSquare(kBoardSize - 1 - row, kBoardSize - 1 - col)),
                       GetSquareAsRectf(row, col));
        }
      }
    }
  }
}

void BoardView::DrawHandPieces(Board& board) {
  bool is_white = false;
  if (current_player_color_ == kWhiteCol) {
    is_white = true;
  }

  for (int i = 0; i < board.GetHandSize(is_white); i++) {
    ci::gl::draw(images_->RetrievePieceImage(board.GetPieceInHand(is_white, i)),
        GetHandIndexAsRectf(bounds_.bottom_box, i));
  }
  for (int i = 0; i < board.GetHandSize(!is_white); i++) {
    ci::gl::draw(images_->RetrievePieceImage(board.GetPieceInHand(!is_white, i)),
                 GetHandIndexAsRectf(bounds_.top_box, i));
  }
   
} 

void BoardView::DrawPlayers(chess::Player &player1, chess::Player &player2) {
  bool is_white = current_player_color_ == kWhiteCol;
  Player bottom;
  Player top;
  if ( is_white && player1.is_white_) {
    bottom = player1;
    top = player2;
  } else {
    bottom = player2;
    top = player1;
  }
  ci::gl::color(1.0f, 1.0f, 1.0f);
  ci::vec2 bottom_loc = {bounds_.board.getX2() - 160, bounds_.board.getY2() - kBorder/2};
  const cinder::ivec2 size = {300, kBorder};
  PrintText("Player Time Remaining: " + ReportTime(bottom.timer_.getSeconds() + kBorder/2),
      kBlackCol, bottom_loc, size);

  ci::gl::color(1.0f, 1.0f, 1.0f);
  ci::vec2 bottom_team_rect = {bounds_.board.getX2() - 420, bounds_.board.getY2() - kBorder/2};
  PrintText("Team: " + bottom.team_name_, bottom.team_color_, bottom_team_rect, size);

  ci::gl::color(1.0f, 1.0f, 1.0f);
  ci::vec2 top_loc = {bounds_.board.getX2() - 160, bounds_.board.getY1() + kBorder/2};
  PrintText("Player Time Remaining: " + ReportTime(top.timer_.getSeconds()),
      kBlackCol, top_loc, size);

  ci::gl::color(1.0f, 1.0f, 1.0f);
  ci::vec2 top_team_rect = {bounds_.board.getX2() - 420, bounds_.board.getY1() + kBorder/2};
  PrintText("Team: " + top.team_name_, top.team_color_, top_team_rect, size);
  
}

std::string BoardView::ReportTime(int seconds) {
  int sec_remain = kMaxSeconds - seconds;
  int min = floor(sec_remain / 60);
  int sec = sec_remain % 60;
  auto to_write =  std::to_string(min) + ":" + std::to_string(sec);
  if (to_write.length() < 4) {
    to_write += "0";
  }
  return to_write;
}

void BoardView::DrawPawnPromotion() {
  
}


ci::Rectf BoardView::GetHandIndexAsRectf(ci::Area& box_bounds, int index) {
  int row = floor(index / kBoxLenIndex);
  int col = (index % kBoxLenIndex);
  auto square = ci::Rectf(col * kHandSquareLen + box_bounds.getX1(),
            row * kHandSquareLen + box_bounds.getY1(),
            (col+1) * kHandSquareLen + box_bounds.getX1(), 
            (row+1) * kHandSquareLen + box_bounds.getY1());
  return square;
}

ci::Rectf BoardView::GetSquareAsRectf(int row, int col) {
  auto square = ci::Rectf(col * kSquareLen + bounds_.board.getX1() + kBorder, 
            row * kSquareLen + bounds_.board.getY1() + kBorder,
            (col+1) * kSquareLen + bounds_.board.getX1() + kBorder, 
            (row+1) * kSquareLen + bounds_.board.getY1() + kBorder);
  return square;
}


void BoardView::PrintText(const std::string &text, const ci::Color &color, const cinder::vec2 &loc, const ci::ivec2& size) {
  cinder::gl::color(color);

  auto box = ci::TextBox()
                 .alignment(ci::TextBox::RIGHT)
                 .color(color)
                 .size(size)
                 .font(cinder::Font("Arial", 25))
                 .backgroundColor(ci::ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

}