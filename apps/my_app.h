// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <chess/BoardEngine.h>
#include "chess/Piece.h"
#include "chess/Knight.h"
#include "utility"
#include "chess/Board.h"
#include "chess/Engine.h"
#include "chess/ChessImages.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(cinder::app::MouseEvent) override;
  chess::BoardEngine left_engine_;
  chess::BoardEngine right_engine_;


  void DrawBackground();
  void DrawBoards();
  void DrawPieces();
  
  std::pair<int, int> GetSquareFromPoint(ci::vec2 point);
  ci::Rectf GetSquareAsRectf(ci::Area& board_bounds, int row, int col);

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
