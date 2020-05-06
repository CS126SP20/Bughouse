//
// Created by tomok on 4/21/2020.
//


#include "chess/BoardView.h"
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include "chess/BoardEngine.h"



namespace chess {

BoardView::BoardView(ChessImages* chess_image,
    ci::Area board_bounds, ci::Area top_box_bounds, ci::Area bottom_box_bounds)
{
  bounds_.board = board_bounds;
  bounds_.bottom_box = bottom_box_bounds;
  bounds_.top_box = top_box_bounds;
  
  // Place the promotion choice box in the center of the board
  ci::vec2 board_center = (bounds_.board.getUL() + kBoardLen/2);
  auto promotion_UL = ci::vec2(board_center.x - 5*kPromotionBoxBorderLen/2 - 2*kHandSquareLen,
                               board_center.y - kPromotionBoxBorderLen - kHandSquareLen/2);
  auto promotion_LR = ci::vec2(board_center.x + 5*kPromotionBoxBorderLen/2 + 2*kHandSquareLen,
                               board_center.y + kPromotionBoxBorderLen + kHandSquareLen/2);
  bounds_.promotion_box = ci::Area(promotion_UL, promotion_LR);
  
  // The white player always starts
  current_player_color_ = kWhiteCol;
  current_opponent_color_ = kBlackCol;

  images_ = chess_image;
}

//================================================================
// Public member functions
//================================================================

Location BoardView::ProcessClick(const ci::vec2& point) {
  Location click_loc = Location();
  
  if (point.x > bounds_.board.getX1() + kBorder && point.x < bounds_.board.getX2() - kBorder
      && point.y > bounds_.board.getY1() + kBorder && point.y < bounds_.board.getY2() - kBorder) {
    click_loc = GetBoardSquareAtPoint(point);

  } else if (point.x > bounds_.bottom_box.getX1() && point.x < bounds_.bottom_box.getX2()
             && point.y > bounds_.bottom_box.getY1() && point.y < bounds_.bottom_box.getY2()) {
    click_loc = GetHandIndexAtPoint(point);
  }
  
  return click_loc;
}

PieceType BoardView::GetPieceTypeFromClick(const ci::vec2& click) {
  int index = -1;
  
  if (click.x > bounds_.promotion_box.getX1() && click.x < bounds_.promotion_box.getX2()
      && click.y > bounds_.promotion_box.getY1() && click.y < bounds_.promotion_box.getY2()) {
    // Get the chosen promotion box
    index = floor((click.x - bounds_.promotion_box.getX1()) / kHandSquareLen);
  }
  
  if (index != -1) {
    // Player clicked within one of the boxes, so return that type
    return kPromotionChoices[index];
  }
  
  // Player did not click a promotion box
  return PAWN;
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

void BoardView::Draw(Board& board, Player& team1, Player& team2,
                     std::pair<Location, Location> turn,
                     std::pair<Location, Location> last_turn) {
  ci::gl::color(1.0f,1.0f,1.0f);
  DrawBoxes();
  ci::gl::color(1.0f, 1.0f, 1.0f);
  DrawBoard();
  
  ci::gl::color(1.0f, 1.0f, 1.0f);
  
  // Highlight the boxes with the team color
  // The last move should be highlighted with opponent team color
  // The current move should be highlighted with current team color
  bool is_white = current_player_color_ == kWhiteCol;
  ci::Color curr_color;
  ci::Color opp_color;
  if (is_white == team1.is_white_) {
    curr_color = team1.team_color_;
    opp_color = team2.team_color_;
  } else {
    curr_color = team2.team_color_;
    opp_color = team1.team_color_;
  }
  DrawTurns(turn, last_turn, curr_color, opp_color);
  
  // Now finish drawing everything else
  ci::gl::color(1.0f, 1.0f, 1.0f);
  DrawPieces(board);
  ci::gl::color(1.0f, 1.0f, 1.0f);
  DrawHandPieces(board);
  ci::gl::color(1.0f, 1.0f, 1.0f);
  DrawPlayers(team1, team2);
}

void BoardView::DrawPawnPromotion() {
  bool is_white = false;
  if (current_player_color_ == kWhiteCol) {
    is_white = true;
  }
  
  // Draw the border of the promotion box
  ci::gl::color(kBlackCol);
  ci::gl::drawSolidRect(bounds_.promotion_box);
  
  // Now draw each of the boxes, within the border
  ci::gl::color(kWhiteCol);
  auto first_box_UL = ci::vec2(bounds_.promotion_box.getX1() + kPromotionBoxBorderLen,
                              bounds_.promotion_box.getY1() + kPromotionBoxBorderLen);
  for (int i = 0; i < std::size(kPromotionChoices); i++) {
    // Draw the box
    auto box = ci::Rectf(first_box_UL,
                         ci::vec2(first_box_UL.x + kHandSquareLen, first_box_UL.y + kHandSquareLen));
    ci::gl::drawSolidRect(box);
    // Draw the piece promotion option
    ci::gl::draw(images_->RetrievePieceImage(kPromotionChoices[i], is_white), box);
    
    // Go on to the next box
    first_box_UL.x += kHandSquareLen + kPromotionBoxBorderLen;
  }
  
}

//================================================================
// Private member functions
//================================================================

Location BoardView::GetBoardSquareAtPoint(const ci::vec2& point) {
  int col = std::floor((point.x - bounds_.board.getX1() - kBorder) / kSquareLen);
  int row = std::floor((point.y - bounds_.board.getY1() - kBorder) / kSquareLen);
  
  if (col < 0 || row < 0 || col >= kBoardLen || row >= kBoardLen) {
    // The click was not within the board, return empty
    return Location();
    
  } else if (current_player_color_ == kWhiteCol) {
    return Location(row , col);
  } else {
    // If the player is black, return the inverse of the point since the board is flipped
    return Location(kBoardSize - 1 - row, kBoardSize - 1 - col);
  }
}

Location BoardView::GetHandIndexAtPoint(const ci::vec2& point) {
  int col = std::floor((point.x - bounds_.bottom_box.getX1()) / kHandSquareLen);
  int row = std::floor((point.y - bounds_.bottom_box.getY1()) / kHandSquareLen);
  
  if (col < 0 || row < 0 || col >= kBoxLenIndex || row >= kBoxHeightIndex) {
    // The click was not within the box, return empty
    return Location();
  } else {
    // Return the index of the chosen piece
    return Location(col + row*kBoxLenIndex, EMPTY);
  }
}

ci::Rectf BoardView::GetHandIndexAsRectf(ci::Area& box_bounds, int index) {
  // Lay out the pieces left to right
  
  // Row is number of times the index number overlaps with the number of boxes per row
  int row = floor(index / kBoxLenIndex);
  // Col number is the remainder
  int col = (index % kBoxLenIndex);
  
  // Get That Square!
  auto square = ci::Rectf(col * kHandSquareLen + box_bounds.getX1(),
            row * kHandSquareLen + box_bounds.getY1(),
            (col+1) * kHandSquareLen + box_bounds.getX1(), 
            (row+1) * kHandSquareLen + box_bounds.getY1());
  return square;
}

ci::Rectf BoardView::GetSquareAsRectf(Location& location) {
  // Get That Square!
  auto square = ci::Rectf(location.Col() * kSquareLen + bounds_.board.getX1() + kBorder, 
            location.Row() * kSquareLen + bounds_.board.getY1() + kBorder,
            (location.Col()+1) * kSquareLen + bounds_.board.getX1() + kBorder, 
            (location.Row()+1) * kSquareLen + bounds_.board.getY1() + kBorder);
  return square;
}

void BoardView::DrawBoxes() {
  ci::gl::color(1.0f, 1.0f, 1.0f);
  
  // Top box is the opponent's color
  ci::gl::color(current_opponent_color_); 
  ci::Rectf top = ci::Rectf(bounds_.top_box);
  ci::gl::drawSolidRect(top);

  // Bottom box is the current player's color
  ci::gl::color(current_player_color_);
  ci::Rectf low = ci::Rectf(bounds_.bottom_box);
  ci::gl::drawSolidRect(low);
}

void BoardView::DrawBoard() {
  ci::gl::draw(images_->RetrieveBoardImage(),
      ci::Rectf(bounds_.board));
}

void BoardView::DrawTurns(std::pair<Location, Location> turn,
                          std::pair<Location, Location> last_turn,
                          const ci::Color& current_color, const ci::Color& opponent_color) {
  
  bool is_white = kWhiteCol == current_player_color_;
  
  // Draw the box that current player has clicked
  DrawTurnSquare(turn.first, is_white, current_color);
  
  // Draw the last turn of the opponent
  // Don't draw the first click of the turn if it was a hand move
  if (last_turn.first.Col() != EMPTY) DrawTurnSquare(last_turn.first, is_white, opponent_color);
  DrawTurnSquare(last_turn.second, is_white, opponent_color);
  
}

void BoardView::DrawTurnSquare(chess::Location location, bool is_white, const ci::Color& color) {
  if (!location.IsEmpty()) {
    ci::gl::color(color);
    Location loc = location;
    
    if (!is_white && location.Col() != EMPTY) {
      // Black, so must invert the location for black player view
      loc = Location(kBoardSize - 1 - location.Row(), kBoardSize - 1 - location.Col());
    }
    
    ci::Rectf to_draw;
    if (location.Col() == EMPTY) {
      // Highlight a square on the box
      to_draw = GetHandIndexAsRectf(bounds_.bottom_box, location.Row());
    } else {
      // Highlight a square on the board
      to_draw = GetSquareAsRectf(loc);
    }
    
    // DRAW IT! :)
    ci::gl::drawSolidRect(to_draw);
  }
}

void BoardView::DrawPieces(Board& board) {
  
  for (int row = 0; row < chess::kBoardSize; row++) {
    for (int col = 0; col < chess:: kBoardSize; col++) {
      // Draw every piece on the board
      if (current_player_color_ == kWhiteCol) {
        
        Location square = Location(row, col);
        if (board.GetPieceAtSquare(square) == nullptr) {
          // Empty square
          continue;
        } else {
          // Draw the piece
          Piece* to_draw = board.GetPieceAtSquare(square);
          ci::gl::draw(images_->RetrievePieceImage(to_draw->GetPieceType(), to_draw->GetIsWhite()),
                       GetSquareAsRectf(square));
        }
      } else {
        // If the player is black, must invert all of the box indices for flipped board view
        Location square = Location(kBoardSize - 1 - row, kBoardSize - 1 - col);
        if (board.GetPieceAtSquare(square) == nullptr) {
          // Empty square
          continue;
          
        } else {
          // Draw the piece
          Piece* to_draw = board.GetPieceAtSquare(square);
          Location loc = Location(row, col);
          ci::gl::draw(images_->RetrievePieceImage(to_draw->GetPieceType(), to_draw->GetIsWhite()),
                       GetSquareAsRectf(loc));
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

  // Draw the current player's hand
  for (int i = 0; i < board.GetHandSize(is_white); i++) {
    Piece* to_draw = board.GetPieceInHand(is_white, i);
    ci::gl::draw(images_->RetrievePieceImage(to_draw->GetPieceType(), to_draw->GetIsWhite()),
        GetHandIndexAsRectf(bounds_.bottom_box, i));
  }
  
  // Draw the opponent player's hand
  for (int i = 0; i < board.GetHandSize(!is_white); i++) {
    Piece* to_draw = board.GetPieceInHand(!is_white, i);
    ci::gl::draw(images_->RetrievePieceImage(to_draw->GetPieceType(), to_draw->GetIsWhite()),
                 GetHandIndexAsRectf(bounds_.top_box, i));
  }
} 

void BoardView::DrawPlayers(chess::Player &player1, chess::Player &player2) {
  bool is_white = current_player_color_ == kWhiteCol;
  
  Player bottom; // Current player
  Player top; // Opponent player
  if ( is_white == player1.is_white_) {
    bottom = player1;
    top = player2;
  } else {
    bottom = player2;
    top = player1;
  }
  
  // Draw current player time remaining
  ci::gl::color(1.0f, 1.0f, 1.0f);
  ci::vec2 bottom_loc = {bounds_.board.getX2() - 160, bounds_.board.getY2() - kBorder/2};
  const cinder::ivec2 size = {300, kBorder};
  PrintText("Player Time Remaining: " + ReportTime(bottom.timer_.getSeconds()),
      kBlackCol, bottom_loc, size);

  // Draw current player team
  ci::gl::color(1.0f, 1.0f, 1.0f);
  ci::vec2 bottom_team_rect = {bounds_.board.getX2() - 420, bounds_.board.getY2() - kBorder/2};
  PrintText("Team: " + bottom.team_name_, bottom.team_color_, bottom_team_rect, size);

  // Draw opponent player time remaining
  ci::gl::color(1.0f, 1.0f, 1.0f);
  ci::vec2 top_loc = {bounds_.board.getX2() - 160, bounds_.board.getY1() + kBorder/2};
  PrintText("Player Time Remaining: " + ReportTime(top.timer_.getSeconds()),
      kBlackCol, top_loc, size);

  // Draw opponent player team
  ci::gl::color(1.0f, 1.0f, 1.0f);
  ci::vec2 top_team_rect = {bounds_.board.getX2() - 420, bounds_.board.getY1() + kBorder/2};
  PrintText("Team: " + top.team_name_, top.team_color_, top_team_rect, size);
  
}

std::string BoardView::ReportTime(int seconds) {
  int sec_remain = kMaxSeconds - seconds;
  
  std::string min = std::to_string(int(floor(sec_remain / 60)));
  std::string sec = std::to_string(sec_remain % 60);
  
  // Add a zero in front for single digit numbers
  if (sec.length() == 1) {
    sec = "0" + sec;
  }
  
  auto to_write =  min + ":" + sec;

  return to_write;
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