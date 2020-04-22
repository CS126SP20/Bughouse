// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include "chess/Piece.h"
#include "chess/Knight.h"
#include "utility"
#include "chess/Board.h"
#include "chess/Engine.h"

namespace myapp {
  const double kBorder = 34.4;
  const int kBoardLen = 640;
  const double kSquareLen = 71.2;
  const ci::Color kGreyCol = ci::Color(1.0f * 89/256, 1.0f * 89/256, 1.0f * 89/256);
  const ci::Color kBlackCol = ci::Color(1.0f * 62/256, 1.0f * 54/256, 1.0f * 52/256);
  const ci::Color kWhiteCol = ci::Color(1.0f * 248 /256, 1.0f * 244/256, 1.0f * 236/256);

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
  chess::Engine engine_;

  cinder::gl::Texture2dRef& RetrievePieceImage(chess::Piece* piece);
  void DrawBackground();
  void DrawBoards();
  void DrawPieces();
  
  std::pair<int, int> GetSquareFromPoint(ci::vec2 point);
  ci::Rectf GetSquareAsRectf(ci::Area& board_bounds, int row, int col);

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
