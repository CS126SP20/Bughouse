// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>


namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  
  cinder::gl::Texture2dRef texture_;
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

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
