//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <vector>
#include <cinder/Timer.h>
#include "cinder/Color.h"

namespace chess {

struct Player {
  ci::Timer timer_;
  bool is_white_;
  ci::Color team_color_;
  std::string team_name_;
//  PlayerMove (????);
};  

}


#endif //FINALPROJECT_PLAYER_H
