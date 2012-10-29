#ifndef SHAPEMAKER_H
#define SHAPEMAKER_H
// headers, ...

class ShapeFactory {
public:
  explicit ShapeFactory(std::istream& in): in_(in) {}

  // refer to lecture; see writeup for brief description
  Shape* create();

private:
  std::istream&  in_;
};
#endif
