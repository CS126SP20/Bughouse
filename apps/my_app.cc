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

namespace myapp {
using cinder::app::MouseEvent;
using cinder::app::KeyEvent;

MyApp::MyApp() {
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

}

void MyApp::draw() {
  ci::gl::clear(ci::Color(89/256, 89/256, 89/256));
  
  DrawBoards();
  
  


  chess::Board board;

  for (int row = 0; row < chess::kBoardSize; row++) {
    for (int col = 0; col < chess:: kBoardSize; col++) {
      if (board.GetPieceAtLocWhiteView(row, col) == nullptr) {
        continue;
      } else {
        ci::gl::draw(MyApp::RetrievePieceImage(board.GetPieceAtLocWhiteView(row, col)),
            ci::Rectf(col * kSquareLen + kBorder, row * kSquareLen + kBorder, 
                     (col + 1) * kSquareLen + kBorder, (row+1) * kSquareLen + kBorder));
        ci::gl::draw(MyApp::RetrievePieceImage(board.GetPieceAtLocBlackView(row, col)),
                     ci::Rectf(col * kSquareLen + kBorder + kBoardLen, 
                                       row * kSquareLen + kBorder,
                                       (col + 1) * kSquareLen + kBorder + kBoardLen,
                                       (row+1) * kSquareLen + kBorder));
      }
    }
  }
  
}

void MyApp::DrawBoards() {
  ci::vec2 center = getWindowCenter();
  ci::gl::draw(board_white_img_,ci::Rectf(center.x - kBoardLen, center.y - kBoardLen/2,
                         center.x, center.y + kBoardLen/2));
  ci::gl::draw(board_black_img_, ci::Rectf(center.x, center.y - kBoardLen/2,
                                           center.x + kBoardLen, center.y + kBoardLen/2));
  
}

void MyApp::DrawPieces() {
  
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
  if (event.isLeft()) {
    if (first_click) {
      mLoc1 = event.getPos();
      first_click = false;
    } else {
      mLoc2 = event.getPos();
      first_click = true;
    }  
  }
}

}  // namespace myapp
