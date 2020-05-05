//
// Created by tomok on 4/21/2020.
//

#ifndef FINALPROJECT_CHESSIMAGES_H
#define FINALPROJECT_CHESSIMAGES_H

#include "chess/ChessImages.h"
#include <chess/Piece.h>
#include "cinder/gl/gl.h"


namespace chess {

const int kPromotionBoxBorderLen = 2;  
const double kBorder = 34.4;
const int kBoardLen = 640;
const double kSquareLen = 71.2;
const double kHandSquareLen = 55;
const int kBoxLenIndex = 4;
const int kBoxHeightIndex = 5; 
const auto kGreyCol = ci::Color(1.0f * 91/256, 1.0f * 89/256, 1.0f * 89/256);
const auto kBlackCol = ci::Color(1.0f * 62/256, 1.0f * 54/256, 1.0f * 52/256);
const auto kWhiteCol = ci::Color(1.0f * 248 /256, 1.0f * 244/256, 1.0f * 236/256);
//TODO:Write destructor
class ChessImages {
  public:
    void SetUp();
    cinder::gl::Texture2dRef &RetrievePieceImage(PieceType piece_type, bool is_white);
    cinder::gl::Texture2dRef &RetrieveBoardImage() { return board_img_;};
  private:
    cinder::gl::Texture2dRef board_img_;
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
