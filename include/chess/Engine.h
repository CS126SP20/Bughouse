//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H
#include <cinder/Area.h>
#include <chess/BoardEngine.h>
#include <cinder/Vector.h>

namespace chess {

class Engine {
public:
  Engine() {};
  Engine(ci::Area left_board_bounds, ci::Area top_left_box_bounds, ci::Area low_left_box_bounds,
  ci::Area right_board_bounds, ci::Area top_right_box_bounds, ci::Area low_right_box_bounds);
  
  BoardEngine left_board_;
  BoardEngine right_board_;
  void ProcessClick(ci::vec2 click);
  void Update();
};  

}
#endif //FINALPROJECT_ENGINE_H
