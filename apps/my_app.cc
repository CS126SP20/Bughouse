// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <chess/Piece.h>
#include "chess/Board.h"
#include "chess/Engine.h"
#include <ciAnimatedGif.h>

namespace myapp {
using cinder::app::MouseEvent;
using cinder::app::KeyEvent;
using namespace chess;

MyApp::MyApp() {

}

void MyApp::setup() {
  chess_gif_ = ci::ciAnimatedGif::create( loadAsset("apple.gif") );
  
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
  ChessImages* chess_images_ = new ChessImages();
  chess_images_->SetUp();

  left_engine_ = chess::BoardEngine(chess_images_, true,
                                    left_board_bounds, top_left_box_bounds, low_left_box_bounds);
  right_engine_ = chess::BoardEngine(chess_images_, true,
                                     right_board_bounds, top_right_box_bounds, low_right_box_bounds);
}

void MyApp::update() {
  left_engine_.Move();
  right_engine_.Move();
}

void MyApp::draw() {
  ci::gl::clear(kGreyCol);
  
  left_engine_.Draw();
  right_engine_.Draw();
  
  ci::vec2 center = getWindowCenter();
  chess_gif_->draw();

}



void MyApp::mouseDown(MouseEvent event) {
  ci::vec2 center = ci::app::getWindowCenter();
  if (event.isLeft()) {
    if (event.getPos().x < ci::app::getWindowCenter().x) {
      left_engine_.ProcessClick(event.getPos());
    } else {
      right_engine_.ProcessClick(event.getPos());
    }
  }
}

}  // namespace myapp
