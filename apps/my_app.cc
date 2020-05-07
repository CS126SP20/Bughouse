// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <chess/Piece.h>
#include "chess/Board.h"
#include <ciAnimatedGif.h>

namespace myapp {
using cinder::app::MouseEvent;
using cinder::app::KeyEvent;
using namespace chess;


void MyApp::setup() {
  // Load gifs
  chess_gif_ = ci::ciAnimatedGif::create( loadAsset("apple.gif"));
  pac_gif_ = ci::ciAnimatedGif::create(loadAsset("pacman.gif"));
  
  // Set up boundaries for board boxes
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
  
  // Load chess images -- board, pieces
  auto* chess_images_ = new ChessImages();
  chess_images_->SetUp();
  
  // Initialize players
  // The two white players start timers immediately
  Player team1_player1{ci::Timer(true), true, kTeam1Color, kTeam1Name};
  Player team1_player2{ci::Timer(false), false, kTeam1Color, kTeam1Name};
  Player team2_player1{ci::Timer(false), false, kTeam2Color, kTeam2Name};
  Player team2_player2{ci::Timer(true), true, kTeam2Color, kTeam2Name};
  
  // Initialize board engi5nes
  left_engine_ = chess::BoardEngine(chess_images_, left_board_bounds, top_left_box_bounds, low_left_box_bounds,
                                    team1_player1, team2_player1);
  right_engine_ = chess::BoardEngine(chess_images_, right_board_bounds, top_right_box_bounds, low_right_box_bounds,
                                     team2_player2, team1_player2);
}

void MyApp::update() {
  // Keep updating while the game continues
  if (!left_engine_.IsGameEnd() && !right_engine_.IsGameEnd()) {
    
    // Move both engines
    Piece* left_capture = left_engine_.Move();
    Piece* right_capture = right_engine_.Move();
    
    // Trade captured pieces if there are any
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
    // Draw game over

    // Get color of winner team
    ci::Color winner_color;
    if (left_engine_.IsGameEnd()) winner_color = left_engine_.GetWinnerColor();
    else winner_color = right_engine_.GetWinnerColor();
    ci::gl::clear(winner_color);
    
    // Get winner team name
    ci::vec2 place(getWindowCenter().x, getWindowCenter().y - 100);
    std::string text;
    if ( winner_color == kTeam1Color) {
      text = kTeam1Name;
    } else {
      text = kTeam2Name;
    }
    
    // Print game over text
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 50};
    const ci::Color txt_color = ci::Color::black();
    PrintText("Game Over! The Winner is: " + text, txt_color, {center.x, center.y - 100}, size);
    
    // Draw the game over gif
    ci::gl::color(1.0f, 1.0f, 1.0f);
    pac_gif_->draw();
    
  } else {
    
    // Draw each enginer
    left_engine_.Draw();
    right_engine_.Draw();
    ci::gl::color(1.0f, 1.0f, 1.0f);
    
    // Draw center game gif
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
      // A click on the left side of the screen
      left_engine_.ProcessClick(event.getPos());
      
    } else {
      // A click on the right side of the screen
      right_engine_.ProcessClick(event.getPos());
      
    }
    
  }
}

}  // namespace myapp
