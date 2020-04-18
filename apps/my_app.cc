// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/ImageIo.h>


namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() {
}

void MyApp::setup() {
  texture_ = ci::gl::Texture2d::create(loadImage(loadAsset( "boardimg.jpg")));
  
  // Load all piece images
  bb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/bb.png")));
  bw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/bw.png")));
  kb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/kb.png")));
  kw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/kw.png")));
  nb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/nb.png")));
  nw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/nw.png")));
  pb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/pb.png")));
  pw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/pw.png")));
  qb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/qb.png")));
  qw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/qw.png")));
  rb_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/rb.png")));
  rw_img_ = ci::gl::Texture2d::create(loadImage(loadAsset( "pieces/rw.png")));
}

void MyApp::update() { }

void MyApp::draw() {
  
  if (texture_) {
    ci::gl::draw(texture_, ci::Rectf(0, 0, 800, 800));
    ci::gl::draw(texture_, ci::Rectf(800, 0, 1600, 800));
    ci::gl::draw(bb_img_, ci::Rectf(70,68,155,150));
  }

}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
