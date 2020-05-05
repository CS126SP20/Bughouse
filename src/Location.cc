//
// Created by tomok on 5/5/2020.
//

#include "chess/Location.h"

namespace chess {
Location::Location() : row_(EMPTY), col_(EMPTY) {}  

Location::Location(int row, int col) : row_(row), col_(col) {}

bool Location::IsEmpty() {
  return row_ == EMPTY && col_ == EMPTY;
}

void Location::Empty() {
  row_ = EMPTY;
  col_ = EMPTY;
}

bool Location::operator==(const Location& rhs) const {
  return row_ == rhs.row_ && col_ == rhs.col_;
}

bool Location::operator()(const Location& lhs, const Location& rhs) const {
  return lhs <= rhs;
}

bool Location::operator!=(const Location& rhs) const {
  return !(*this == rhs);
}

bool Location::operator<(const Location& rhs) const {
  return row_ < rhs.row_ || (rhs.row_ >= row_ && col_ < rhs.col_);
}

bool Location::operator<=(const Location& rhs) const {
  return !(rhs < *this);
}

bool Location::operator>(const Location& rhs) const {
  return rhs < *this;
}

bool Location::operator>=(const Location& rhs) const {
  return !(*this < rhs);
}

Location Location::operator+(const Location& rhs) const {
  return { row_ + rhs.row_, col_ + rhs.col_ };
}

Location Location::operator-(const Location& rhs) const {
  return *this + (-rhs);
}

Location Location::operator-() const { return {-row_, -col_}; }

Location& Location::operator+=(const Location& rhs) {
  *this = *this + rhs;
  return *this;
}

int mod(int a, int b) {
  int c = a % b;
  return c + (c < 0 ? b : 0);
}

Location Location::operator%(const Location& rhs) const {
  return {mod(row_, rhs.row_), mod(col_, rhs.col_)};
}

int Location::Row() const { return row_; }

int Location::Col() const { return col_; }

}