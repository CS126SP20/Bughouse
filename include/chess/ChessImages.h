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
const auto kGreyCol = ci::Color(1.0f * 91/255, 1.0f * 89/255, 1.0f * 89/255);
const auto kBlackCol = ci::Color(1.0f * 62/255, 1.0f * 54/255, 1.0f * 52/255);
const auto kWhiteCol = ci::Color(1.0f * 248 /255, 1.0f * 244/255, 1.0f * 236/255);

class ChessImages {
 public:
  // Loads all of the images
  void SetUp();
  
  // Returns the image of a piece
  cinder::gl::Texture2dRef &RetrievePieceImage(PieceType piece_type, bool is_white);
  
  // Returns the board image
  cinder::gl::Texture2dRef &RetrieveBoardImage() { return board_img_;};
 private:
  cinder::gl::Texture2dRef board_img_; // Board
  cinder::gl::Texture2dRef bb_img_;    // Bishop, black
  cinder::gl::Texture2dRef bw_img_;    // Bishop, white
  cinder::gl::Texture2dRef kb_img_;    // King,   black
  cinder::gl::Texture2dRef kw_img_;    // King,   white
  cinder::gl::Texture2dRef nb_img_;    // Knight, black
  cinder::gl::Texture2dRef nw_img_;    // Knight, white
  cinder::gl::Texture2dRef pb_img_;    // Pawn,   black
  cinder::gl::Texture2dRef pw_img_;    // Pawn,   white
  cinder::gl::Texture2dRef qb_img_;    // Queen,  black
  cinder::gl::Texture2dRef qw_img_;    // Queen,  white
  cinder::gl::Texture2dRef rb_img_;    // Rook,   black
  cinder::gl::Texture2dRef rw_img_;    // Rook,   white
};
}
#endif //FINALPROJECT_CHESSIMAGES_H
