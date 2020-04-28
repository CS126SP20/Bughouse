//
// Created by tomok on 4/21/2020.
//
#include "chess/ChessImages.h"
#include <chess/Piece.h>

#include "cinder/gl/gl.h"
#include <cinder/ImageIo.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>

namespace chess {
using namespace ci::app;
  
void ChessImages::SetUp() {
  board_black_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "board_black.png")));
  board_white_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "board_white.png")));

  // Load all piece images
  bb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/bb.png")));
  kb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/kb.png")));
  nb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/nb.png")));
  pb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/pb.png")));
  qb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/qb.png")));
  rb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/rb.png")));

  rw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/rw.png")));
  bw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/bw.png")));
  kw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/kw.png")));
  nw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/nw.png")));
  pw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/pw.png")));
  qw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/qw.png")));
}
  
cinder::gl::Texture2dRef& ChessImages::RetrievePieceImage(chess::Piece* piece) {
  if (piece->GetIsWhite()) {
    switch (piece->GetPieceType()) {
      case chess::KING :   return kw_img_;
      case chess::PAWN :   return pw_img_;
      case chess::ROOK :   return rw_img_;
      case chess::QUEENED_PAWN :
      case chess::QUEEN :  return qw_img_;
      case chess::BISHOP : return bw_img_;
      case chess::KNIGHT : return nw_img_;
    }
  } else {
    switch (piece->GetPieceType()) {
      case chess::KING :   return kb_img_;
      case chess::PAWN :   return pb_img_;
      case chess::ROOK :   return rb_img_;
      case chess::QUEENED_PAWN :
      case chess::QUEEN :  return qb_img_;
      case chess::BISHOP : return bb_img_;
      case chess::KNIGHT : return nb_img_;
    }
  }
}

cinder::gl::Texture2dRef& ChessImages::RetrieveBoardImage(ci::Color player_color) {
  if (player_color == kBlackCol) {
    return board_black_img_;
  } else {
    return board_white_img_;
  }
}


  
}