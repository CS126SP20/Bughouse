//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <vector>

namespace chess {

struct Player {
  bool can_castle;
  std::vector<Piece*> pieces_in_hand;
  ci::Timer timer;
  
//  PlayerMove (????);

};  

}


#endif //FINALPROJECT_PLAYER_H
