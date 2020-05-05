//
// Created by tomok on 5/5/2020.
//

#ifndef FINALPROJECT_LOCATION_H
#define FINALPROJECT_LOCATION_H

namespace chess {
const int EMPTY = -1;  
// Represents a location on the board.
class Location {
 public:
  Location();
  Location(int row, int col);

  bool IsEmpty();
  void Empty();
  // Comparison operators.
  bool operator()(const Location& lhs, const Location& rhs) const;
  bool operator==(const Location& rhs) const;
  bool operator!=(const Location& rhs) const;
  bool operator<(const Location& rhs) const;
  bool operator<=(const Location& rhs) const;
  bool operator>(const Location& rhs) const;
  bool operator>=(const Location& rhs) const;

  // Vector operators.
  Location operator+(const Location& rhs) const;
  // Note: Always returns positive coordinates.
  Location operator%(const Location& rhs) const;
  Location operator-(const Location& rhs) const;
  Location& operator+=(const Location& rhs);
  Location operator-() const;

  // Accessors.
  int Row() const;
  int Col() const;

 private:
  int row_;
  int col_;
};
 
}

#endif //FINALPROJECT_LOCATION_H
