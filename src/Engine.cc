//
// Created by tomok on 4/19/2020.
//

#include <cinder/app/AppBase.h>
#include "chess/Engine.h"

namespace chess {

Engine::Engine(ci::Area left_board_bounds, ci::Area top_left_box_bounds, ci::Area low_left_box_bounds,
               ci::Area right_board_bounds, ci::Area top_right_box_bounds, ci::Area low_right_box_bounds)
               {
  left_board_ = BoardEngine(true, left_board_bounds, top_left_box_bounds, low_left_box_bounds);
  right_board_ = BoardEngine(false, right_board_bounds, top_right_box_bounds, low_right_box_bounds);
}

void Engine::Update() {
//  left_board_.Move();
}

void Engine::ProcessClick(ci::vec2 click) {
  if (click.x < ci::app::getWindowCenter().x) {
    left_board_.ProcessClick(click);
  } else {
    right_board_.ProcessClick(click);
  }
}

}