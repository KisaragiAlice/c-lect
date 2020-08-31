#include <iostream>
using namespace std;
class Shape {
public:
  Shape() {}
  Shape(short r) {}
  Shape(short x,short y) {}
  virtual ~Shape() { cerr<<"~Shape()"<< endl; };  
  virtual float area()=0;
};

class Rectangle: public Shape {
protected:
  short width=0;short height=0;
public:  
  Rectangle(short w,short h): width(w),height(h) {};
  ~Rectangle(){ cerr<<"~Rectangle()"<< endl;};
  float area() { return this->width * this->height; };
};
class Triangle: public Shape {
protected:
  short width=0;short height=0;
public: 
  Triangle(short w,short h): width(w),height(h) {};
  ~Triangle(){ cerr<<"~Triangel()"<< endl;};
  float area() { return width*height/2.0; };
};

class Ellipse: public Shape {
protected:
  const float pi=3.1415926535F;  
  short x_radius=0;short y_radius=0;
public:  
  Ellipse(short rx,short ry): x_radius(rx),y_radius(ry) {};
  ~Ellipse(){ cerr<<"~Ellipse()"<< endl;};
  float area() { return pi*x_radius*y_radius; };
};
class Circle: public Ellipse {
public:  
  Circle(short r): Ellipse(r,r) {};
  ~Circle(){ cerr<<"~Circle()"<< endl;};
  float area() { return pi*x_radius*y_radius; };
};
class Square: public Rectangle {
public:  
  Square(short x): Rectangle(x,x) {};
  ~Square(){ cerr<<"~Square()"<< endl;};
  float area() { return width*width; };
};

class Factory {
public:
  Shape* newInstance(string type,short x,short y) {
    Shape* s=create(type,x,y); return s;
  };
private:
  virtual Shape* create(string type,short x,short y)=0;
};

class ShapeFactory: public Factory {
private:
  Shape* create(string type,short x,short y) {
    if (type=="rectangle") return new Rectangle(x,y);
    if (type=="triangle") return new Triangle(x,y);
    if (type=="ellipse") return new Ellipse(x,y);
    if (type=="circle") return new Circle(x);    
    if (type=="square") return new Square(x);    
    else return NULL;
  }
};

int main(void) {
  Factory *shapef=new ShapeFactory();
  const short N=5;
  Shape *s[N]={
      shapef->newInstance("rectangle",10,20),
      shapef->newInstance("ellipse",10,20),      
      shapef->newInstance("triangle",10,20),
      shapef->newInstance("circle",20,20),
      shapef->newInstance("square",10,10), 
  };
  for (int i=0;i<N;i++) {
    cout << s[i]->area() << ":" << s[i] << endl;
  }
}
  
