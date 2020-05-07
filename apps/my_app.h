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
  
// Team settings  
const auto kTeam1Color = ci::Color(1.0f*210/255, 1.0f*180/255, 1.0f*222/255);
const std::string kTeam1Name = "Purple";
const auto kTeam2Color = ci::Color(1.0f*183/255, 1.0f*201/255, 1.0f*226/255);
const std::string kTeam2Name = "Blue";


class MyApp : public cinder::app::App {
 public:
  MyApp() { }
  
  // Game screen gif
  ci::ciAnimatedGifRef chess_gif_;
  // End screen gif
  ci::ciAnimatedGifRef pac_gif_;

  // One engine per board
  chess::BoardEngine left_engine_;
  chess::BoardEngine right_engine_;
  
  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(cinder::app::MouseEvent) override;
  void PrintText(const std::string &text, const ci::Color &color, const cinder::vec2 &loc, const ci::ivec2& size);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
