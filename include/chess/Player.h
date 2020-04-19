//
// Created by tomok on 4/19/2020.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <vector>

namespace chess {

class Player {
  bool can_castle;
  bool is_player_turn;
  std::vector<Piece> pieces_in_hand;
//  PlayerMove (????);

};  

}


#endif //FINALPROJECT_PLAYER_H
