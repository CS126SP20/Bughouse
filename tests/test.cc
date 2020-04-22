// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <chess/Piece.h>
#include "chess/Knight.h"
#include "chess/Bishop.h"
#include <cinder/Color.h>

TEST_CASE("Random sanity test", "[random]") {
//  chess::Knight* knight = new chess::Knight(false);
//  REQUIRE_FALSE(knight->GetIsWhite());
//  REQUIRE(knight->GetPieceType() == chess::KNIGHT);
//  
//  chess::Piece* h = new chess::Knight(false);
//  REQUIRE_FALSE(h->GetIsWhite());
//  REQUIRE(h->GetPieceType() == chess::KNIGHT);
//  
//  chess::Piece* a = new chess::Bishop(false);
//  REQUIRE_FALSE(a->GetIsWhite());
//  REQUIRE(a->GetPieceType() == chess::BISHOP);
//  
//  REQUIRE_FALSE(a->GetPieceType() == h->GetPieceType());
  ci::Color color(0.1,0.1,0.1);
  ci::Color color2(0.8,.8,0.1);
  REQUIRE_FALSE(color == color2);
}