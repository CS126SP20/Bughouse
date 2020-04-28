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
  pac_gif_ = ci::ciAnimatedGif::create(loadAsset("pacman.gif"));
  
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
  
  Player team1_player1{ ci::Timer(true), true, kTeam1Color};
  Player team1_player2{ ci::Timer(false), false, kTeam1Color };
  Player team2_player1{ ci::Timer(false), false, kTeam2Color};
  Player team2_player2{ ci::Timer(true), true, kTeam2Color };
  
  left_engine_ = chess::BoardEngine(chess_images_, true,
                                    left_board_bounds, top_left_box_bounds, low_left_box_bounds,
                                    team1_player1, team2_player1);
  right_engine_ = chess::BoardEngine(chess_images_, true,
                                     right_board_bounds, top_right_box_bounds, low_right_box_bounds,
                                     team1_player2, team2_player2);
}

void MyApp::update() {
  if (!left_engine_.IsGameEnd() && !right_engine_.IsGameEnd()) {
    Piece* left_capture = left_engine_.Move();
    Piece* right_capture = right_engine_.Move();
    if (left_capture != nullptr) {
      right_engine_.ReceivePiece(left_capture);
    }
    if (right_capture != nullptr) {
      left_engine_.ReceivePiece(right_capture);
    }
  }
}


void MyApp::draw() {
  ci::gl::clear(kGreyCol);

  if (left_engine_.IsGameEnd() || right_engine_.IsGameEnd()) {
    ci::Color winner_color; 
    ci::gl::clear(winner_color);
    if (left_engine_.IsGameEnd()) winner_color = left_engine_.GetWinnerColor();
    else winner_color = right_engine_.GetWinnerColor();
    
    ci::gl::clear(winner_color);
    ci::vec2 place(getWindowCenter().x, getWindowCenter().y - 100);
    std::string text;
    if ( winner_color == kTeam1Color) {
      text = kTeam1;
    } else {
      text = kTeam2;
    }

    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 50};
    const ci::Color txt_color = ci::Color::black();
    
    PrintText("Game Over! The Winner is: " + text, txt_color, {center.x, center.y - 100}, size);
    pac_gif_->draw();
    
  } else {
    left_engine_.Draw();
    right_engine_.Draw();
    chess_gif_->draw();
  }

}

void MyApp::PrintText(const std::string &text, const ci::Color &color, const cinder::vec2 &loc, const ci::ivec2& size) {
  cinder::gl::color(color);

  auto box = ci::TextBox()
                 .alignment(ci::TextBox::CENTER)
                 .color(color)
                 .size(size)
                 .font(cinder::Font("Arial", 30))
                 .backgroundColor(ci::ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
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
