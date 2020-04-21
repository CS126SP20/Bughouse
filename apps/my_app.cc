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
  
  if (board_black_img_) {
    ci::gl::draw(board_black_img_, ci::Rectf(0, 0, 800, 800));
    ci::gl::draw(board_white_img_, ci::Rectf(800, 0, 1600, 800));
  }
  
  
  int border = 43;
  int board_size = 800;
  int square_size = 89;

  chess::Board board;

  for (int row = 0; row < chess::kBoardSize; row++) {
    for (int col = 0; col < chess:: kBoardSize; col++) {
      if (board.GetPieceAtLoc(row, col) == nullptr) {
        continue;
      } else {
        ci::gl::draw(MyApp::RetrievePieceImage(board.GetPieceAtLoc(row, col)),
            ci::Rectf(col * square_size + border, row * square_size + border, 
                     (col + 1) * square_size + border, (row+1) * square_size + border));
      }
    }
  }
  
  

//  int incr = 89;
//  for (int i = 0; i < 8; i++) {
//    int row = 0;
//    if (mLoc1.x >0) {
//
//      row += incr;
//    }
//
//    ci::gl::draw(nb_img_, ci::Rectf(i*incr + border, border + row, (i+1)*incr + border, border + incr + row));
//    row += incr;
//    ci::gl::draw(rb_img_, ci::Rectf(i *incr +border, border + row, (i+1)*incr + border, border + incr + row));
//    row += incr;
//    ci::gl::draw(kb_img_,ci::Rectf(i * incr +border, border + row, (i+1)*incr + border, border + incr+ row));
//    row += incr;
//    ci::gl::draw(qb_img_, ci::Rectf(i * incr + border, border + row, (i+1)*incr + border, border + incr+ row));
//    row += incr;
//    ci::gl::draw(bb_img_, ci::Rectf(i * incr + border, border + row, (i+1)*incr + border, border + incr+ row));
//  }
//
//
//
//  int eh = 843;
//  for (int i = 0; i < 8; i++) {
//    int row = 0;
//    ci::gl::draw(pw_img_, ci::Rectf(i*incr + eh, border + row, (i+1)*incr + eh, border + incr + row));
//    row += incr;
//    ci::gl::draw(nw_img_, ci::Rectf(i*incr + eh, border + row, (i+1)*incr + eh, border + incr + row));
//    row += incr;
//    ci::gl::draw(rw_img_, ci::Rectf(i *incr +eh, border + row, (i+1)*incr + eh, border + incr + row));
//    row += incr;
//    ci::gl::draw(kw_img_,ci::Rectf(i * incr +eh, border + row, (i+1)*incr + eh, border + incr+ row));
//    row += incr;
//    ci::gl::draw(qw_img_, ci::Rectf(i * incr + eh, border + row, (i+1)*incr + eh, border + incr+ row));
//    row += incr;
//    ci::gl::draw(bw_img_, ci::Rectf(i * incr + eh, border + row, (i+1)*incr + eh, border + incr+ row));
//  }

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
