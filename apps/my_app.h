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
#include "chess/ChessImages.h"
#include "ciAnimatedGif.h"


namespace myapp {
  const auto kTeam1Color = ci::Color(1.0f*210/256, 1.0f*180/256, 1.0f*222/256);
  const std::string kTeam1 = "Purple";
  const std::string kTeam2 = "Blue";
  const auto kTeam2Color = ci::Color(1.0f*89/256, 1.0f*163/256, 1.0f*229/256);

class MyApp : public cinder::app::App {
 public:
  MyApp();
  ci::ciAnimatedGifRef chess_gif_;
  ci::ciAnimatedGifRef pac_gif_;
  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(cinder::app::MouseEvent) override;
  chess::BoardEngine left_engine_;
  chess::BoardEngine right_engine_;
  void PrintText(const std::string &text, const ci::Color &color, const cinder::vec2 &loc, const ci::ivec2& size);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
