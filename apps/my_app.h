// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <chess/BoardEngine.h>
#include "chess/Piece.h"
#include "chess/PieceClasses/Knight.h"
#include "utility"
#include "chess/Board.h"
#include "chess/Engine.h"
#include "chess/ChessImages.h"
#include "ciAnimatedGif.h"


namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  ci::ciAnimatedGifRef chess_gif_;
  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(cinder::app::MouseEvent) override;
  chess::BoardEngine left_engine_;
  chess::BoardEngine right_engine_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
