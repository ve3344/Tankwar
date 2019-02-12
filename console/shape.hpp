class Point {
public:
  int x = 0, y = 0;

    Point() {
  } Point(int x, int y):x(x), y(y) {
  };
  bool operator ==(const Point & o) {
    return x == o.x && y == o.y;
  }
  bool operator !=(const Point & o) {
    return x != o.x || y != o.y;
  }

};

class Rect {
public:
  int x = 0, y = 0, w = 0, h = 0;
public:  Rect() {
  } Rect(int x, int y, int w, int h):x(x), y(y), w(w), h(h) {
  }
  bool operator ==(const Rect & o) {
    return x == o.x && y == o.y && w == o.w && h == o.h;
  }
  bool operator !=(const Rect & o) {
    return x != o.x || y != o.y || w != o.w || h != o.h;
  }
  Point getCenter(){
  	return {x+w/2,y+h/2};
  }
  bool contains(Point & a) {
    return a.x >= x && a.x <= a.x + w && a.y >= y && a.y <= y + h;
  }

};
class Circle {
public:int x = 0, y = 0, r = 0;
public:  Circle() {
  } Circle(int x, int y, int r):x(x), y(y), r(r) {
  }
  bool operator ==(const Circle & o) {
    return x == o.x && y == o.y && r == o.r;
  }
  bool operator !=(const Circle & o) {
    return x != o.x || y != o.y || r != o.r;
  }
};
class Line {
public:int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
public:  Line(int x1, int y1, int x2, int y2):x1(x1), y1(y1), x2(x2), y2(y2) {
  } bool operator ==(const Line & o) {
    return x1 == o.x1 && y1 == o.y1 && x2 == o.x2 && y2 == o.y2;
  }
  bool operator !=(const Line & o) {
    return x1 != o.x1 || y1 != o.y1 || x2 != o.x2 || y2 != o.y2;
  }
};