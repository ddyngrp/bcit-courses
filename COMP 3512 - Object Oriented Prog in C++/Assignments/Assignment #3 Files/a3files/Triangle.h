#ifndef TRIANGLE_H
#define TRIANGLE_H
// headers, ... 

class Triangle: public Shape {
public:
  // read data for Triangle from 'is'; used by factory
  // should read in data members saved by 'save' (except for the type name)
  // should perform some error-checking (see README)
  explicit Triangle(std::istream& is); 

  // a Triangle consists of 3 vertices
  // 'i' should be 0, 1, or 2; if not, throw an exception
  Point getVertex(int i) const;

  // 'i' should be 0, 1, or 2; if not, throw an exception
  void  setVertex(int i, const Point& p); 

  // write to standard output
  // example output:  [T: (5,-6), (7,-8), (2,1)]
  virtual void draw() const; 

  /* example output:
       triangle
       (5,-6)
       (7,-8)
       (2,1)
  */
  virtual void save(std::ostream& os = std::cout) const; 

  // accept a visitor
  virtual void accept(ShapeVisitor& v);

private:
  // provide suitable data structure
};

// provide inline implementation of getVertex & setVertex here
// implement the other functions in the CPP file
#endif
