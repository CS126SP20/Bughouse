//
// Created by tomok on 4/21/2020.
//

#ifndef FINALPROJECT_CHESSIMAGES_H
#define FINALPROJECT_CHESSIMAGES_H

#include <chess/Piece.h>
#include "chess/ChessImages.h"
#include "cinder/gl/gl.h"


namespace chess {
  
const double kBorder = 34.4;
const int kBoardLen = 640;
const double kSquareLen = 71.2;
const ci::Color kGreyCol = ci::Color(1.0f * 91/256, 1.0f * 89/256, 1.0f * 89/256);
const ci::Color kBlackCol = ci::Color(1.0f * 62/256, 1.0f * 54/256, 1.0f * 52/256);
const ci::Color kWhiteCol = ci::Color(1.0f * 248 /256, 1.0f * 244/256, 1.0f * 236/256);
//TODO:Write destructor
class ChessImages {
  public:
    void SetUp();
    cinder::gl::Texture2dRef& RetrievePieceImage(chess::Piece* piece);
    cinder::gl::Texture2dRef& RetrieveBoardImage(ci::Color player_color);
  private:
    cinder::gl::Texture2dRef board_black_img_;
    cinder::gl::Texture2dRef board_white_img_;
    cinder::gl::Texture2dRef bb_img_;
    cinder::gl::Texture2dRef bw_img_;
    cinder::gl::Texture2dRef kb_img_;
    cinder::gl::Texture2dRef kw_img_;
    cinder::gl::Texture2dRef nb_img_;
    cinder::gl::Texture2dRef nw_img_;
    cinder::gl::Texture2dRef pb_img_;
    cinder::gl::Texture2dRef pw_img_;
    cinder::gl::Texture2dRef qb_img_;
    cinder::gl::Texture2dRef qw_img_;
    cinder::gl::Texture2dRef rb_img_;
    cinder::gl::Texture2dRef rw_img_;
  };
}
#endif //FINALPROJECT_CHESSIMAGES_H
