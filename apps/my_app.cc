// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/ImageIo.h>
#include <choreograph/Timeline.h>
#include <choreograph/Output.hpp>
#include <chess/Piece.h>
#include <cinder/Log.h>
#include <chess/Knight.h>
#include "chess/Board.h"
#include "chess/Engine.h"

namespace myapp {
using cinder::app::MouseEvent;
using cinder::app::KeyEvent;

MyApp::MyApp() {
  ci::vec2 center = getWindowCenter();
  ci::Area left_board_bounds = ci::Area(center.x - kBoardLen - kBorder, center.y - kBoardLen / 2,
      center.x - kBorder, center.y + kBoardLen/2);
  ci::Area top_left_box_bounds = ci::Area(center.x - kBorder - 7 * kBoardLen / 5, center.y - kBoardLen / 2,
                                          center.x - 2* kBorder - kBoardLen, center.y - kBorder);
  ci::Area low_left_box_bounds = ci::Area(center.x - kBorder - 7 * kBoardLen / 5, center.y + kBorder,
                                          center.x - 2*kBorder - kBoardLen, center.y + kBoardLen/2);

  ci::Area right_board_bounds = ci::Area(center.x + kBorder, center.y - kBoardLen / 2,
      center.x + kBoardLen + kBorder, center.y + kBoardLen/2);

  ci::Area top_right_box_bounds = ci::Area(center.x + kBoardLen + 2 * kBorder, center.y - kBoardLen / 2,
                                center.x + 7*kBoardLen/5 + kBorder, center.y - kBorder);

  ci::Area low_right_box_bounds = ci::Area(center.x + kBoardLen + 2* kBorder, center.y + kBorder,
                                center.x + 7*kBoardLen/5 + kBorder, center.y + kBoardLen/2);
  engine_ = chess::Engine(left_board_bounds, top_left_box_bounds, low_left_box_bounds,
      right_board_bounds, top_right_box_bounds, low_right_box_bounds);
}

void MyApp::setup() {
//  float w = 800;
//  float left = w * 0.08f;
//  float right = w - left;
//  choreograph::Timeline timeline;
//  choreograph::Output<ci::vec3> output;
//  timeline.appl
//  choreograph::PhraseRef<ci::vec2> leftToRight = Ramp(ci::vec2( left, 0.0f ), ci::vec2( right, 0.0f ), 1.0f, choreograph::EaseInOutQuad() );
//
//
//
count_ = 0;
  board_black_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "board_black.png")));
  board_white_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "board_white.png")));
  
  // Load all piece images
  bb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/bb.png")));
  kb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/kb.png")));
  nb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/nb.png")));
  pb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/pb.png")));
  qb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/qb.png")));
  rb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/rb.png")));
  
  rw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/rw.png")));
  bw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/bw.png")));
  kw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/kw.png")));
  nw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/nw.png")));
  pw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/pw.png")));
  qw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/qw.png")));
}

void MyApp::update() {
  engine_.Update();
  count_++;
}

void MyApp::draw() {
  ci::gl::clear(kGreyCol);
  
  DrawBackground();
  DrawBoards();
  DrawPieces();

  
}

void MyApp::DrawBackground() {
  ci::gl::color(kBlackCol);
  ci::Rectf top_left = ci::Rectf(engine_.left_board_.bounds_.top_box);
  ci::gl::drawSolidRect(top_left);
  ci::gl::color(kWhiteCol);
  ci::Rectf top_right = ci::Rectf(engine_.right_board_.bounds_.top_box);
  ci::gl::drawSolidRect(top_right);
  
  ci::gl::color(kWhiteCol);
  ci::Rectf low_left = ci::Rectf(engine_.left_board_.bounds_.bottom_box);
  ci::gl::drawSolidRect(low_left);
  
  ci::gl::color(kBlackCol);
  ci::Rectf low_right = ci::Rectf(engine_.right_board_.bounds_.bottom_box);
  ci::gl::drawSolidRect(low_right);
  
  ci::gl::color(1.0f, 1.0f, 1.0f);
}

void MyApp::DrawBoards() {
  ci::vec2 center = getWindowCenter();
  ci::gl::draw(board_white_img_,ci::Rectf(engine_.left_board_.bounds_.board));
  ci::gl::draw(board_black_img_, ci::Rectf(engine_.right_board_.bounds_.board));
  
}

void MyApp::DrawPieces() {
  
  for (int row = 0; row < chess::kBoardSize; row++) {
    for (int col = 0; col < chess:: kBoardSize; col++) {
      if (engine_.left_board_.board_.GetPieceAtLocWhiteView(row, col) == nullptr) {
        continue;
      } else {
        ci::gl::draw(MyApp::RetrievePieceImage(engine_.left_board_.board_.GetPieceAtLocWhiteView(row, col)),
                     GetSquareAsRectf(engine_.left_board_.bounds_.board, row, col));
//        ci::gl::draw(MyApp::RetrievePieceImage(engine_.left_board_.board_.GetPieceAtLocBlackView(row, col)),
//                     GetSquareAsRectf(engine_.right_board_.bounds_.board, row, col));
      }
    }
  }
}

ci::Rectf MyApp::GetSquareAsRectf(ci::Area& board_bounds, int row, int col) {
  ci::vec2 center = ci::app::getWindowCenter();
  auto square = ci::Rectf(col * kSquareLen + board_bounds.getX1() + kBorder, 
            row * kSquareLen + board_bounds.getY1() + kBorder,
            (col+1) * kSquareLen + board_bounds.getX1() + kBorder, 
            (row+1) * kSquareLen + board_bounds.getY1() + kBorder);
  return square;
}
  
cinder::gl::Texture2dRef& MyApp::RetrievePieceImage(chess::Piece* piece) {
  if (piece->GetIsWhite()) {
    switch (piece->GetPieceType()) {
      case chess::KING :   return kw_img_;
      case chess::PAWN :   return pw_img_;
      case chess::ROOK :   return rw_img_;
      case chess::QUEENED_PAWN :
      case chess::QUEEN :  return qw_img_;
      case chess::BISHOP : return bw_img_;
      case chess::KNIGHT : return nw_img_;
    }
  } else {
    switch (piece->GetPieceType()) {
      case chess::KING :   return kb_img_;
      case chess::PAWN :   return pb_img_;
      case chess::ROOK :   return rb_img_;
      case chess::QUEENED_PAWN :
      case chess::QUEEN :  return qb_img_;
      case chess::BISHOP : return bb_img_;
      case chess::KNIGHT : return nb_img_;
    }
  }
}


void MyApp::mouseDown(MouseEvent event) {
  ci::vec2 center = ci::app::getWindowCenter();
  if (event.isLeft()) {
    engine_.ProcessClick(event.getPos());
  }
}

}  // namespace myapp
