// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/ImageIo.h>
#include <choreograph/Timeline.h>
#include "chess/Piece.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() {
}

void MyApp::setup() {
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

void MyApp::update() { }

void MyApp::draw() {
  
  if (board_black_img_) {
    ci::gl::draw(board_black_img_, ci::Rectf(0, 0, 800, 800));
    ci::gl::draw(board_white_img_, ci::Rectf(800, 0, 1600, 800));
  }
  
  int border = 43;

  int incr = 89;
  for (int i = 0; i < 8; i++) {
    int row = 0;
    ci::gl::draw(pb_img_, ci::Rectf(i*incr + border, border + row, (i+1)*incr + border, border + incr + row));
    row += incr;
    ci::gl::draw(nb_img_, ci::Rectf(i*incr + border, border + row, (i+1)*incr + border, border + incr + row));
    row += incr;
    ci::gl::draw(rb_img_, ci::Rectf(i *incr +border, border + row, (i+1)*incr + border, border + incr + row));
    row += incr;
    ci::gl::draw(kb_img_,ci::Rectf(i * incr +border, border + row, (i+1)*incr + border, border + incr+ row));
    row += incr;
    ci::gl::draw(qb_img_, ci::Rectf(i * incr + border, border + row, (i+1)*incr + border, border + incr+ row));
    row += incr;
    ci::gl::draw(bb_img_, ci::Rectf(i * incr + border, border + row, (i+1)*incr + border, border + incr+ row));
  }



  int eh = 843;
  for (int i = 0; i < 8; i++) {
    int row = 0;
    ci::gl::draw(pw_img_, ci::Rectf(i*incr + eh, border + row, (i+1)*incr + eh, border + incr + row));
    row += incr;
    ci::gl::draw(nw_img_, ci::Rectf(i*incr + eh, border + row, (i+1)*incr + eh, border + incr + row));
    row += incr;
    ci::gl::draw(rw_img_, ci::Rectf(i *incr +eh, border + row, (i+1)*incr + eh, border + incr + row));
    row += incr;
    ci::gl::draw(kw_img_,ci::Rectf(i * incr +eh, border + row, (i+1)*incr + eh, border + incr+ row));
    row += incr;
    ci::gl::draw(qw_img_, ci::Rectf(i * incr + eh, border + row, (i+1)*incr + eh, border + incr+ row));
    row += incr;
    ci::gl::draw(bw_img_, ci::Rectf(i * incr + eh, border + row, (i+1)*incr + eh, border + incr+ row));
  }

}

cinder::gl::Texture2dRef MyApp::RetrievePieceImage(chess::PieceType piece, int color) {
  if (color == chess::kColWhite) {
    switch (piece) {
      case chess::King :   return kw_img_;
      case chess::Pawn :   return pw_img_;
      case chess::Rook :   return rw_img_;
      case chess::Queen :  return qw_img_;
      case chess::Bishop : return bw_img_;
      case chess::Knight : return nw_img_;
    }
  } else {
    switch (piece) {
      case chess::King :   return kb_img_;
      case chess::Pawn :   return pb_img_;
      case chess::Rook :   return rb_img_;
      case chess::Queen :  return qb_img_;
      case chess::Bishop : return bb_img_;
      case chess::Knight : return nb_img_;
    }
  }
}

  void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
