// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include "chess/Piece.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(cinder::app::MouseEvent) override;
  ci::vec2 mLoc1;
  ci::vec2 mLoc2;
  bool first_click;

  cinder::gl::Texture2dRef& MyApp::RetrievePieceImage(chess::PieceType, bool isWhite);

  cinder::gl::Texture2dRef board_black_img_;
  cinder::gl::Texture2dRef board_white_img_;
  cinder::gl::Texture2dRef bb_img_;
  cinder::gl::Texture2dRef bw_img_;
  cinder::gl::Texture2dRef kb_img_;
  cinder::gl::Texture2dRef kw_img_;
  cinder::gl::Texture2dRef nb_img_;
  cinder::gl::Texture2dRef nw_img_;
  cinder::gl::Texture2dRef pb_img_;
  cinder::gl::Texture2dRef pw_img_;
  cinder::gl::Texture2dRef qb_img_;
  cinder::gl::Texture2dRef qw_img_;
  cinder::gl::Texture2dRef rb_img_;
  cinder::gl::Texture2dRef rw_img_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
