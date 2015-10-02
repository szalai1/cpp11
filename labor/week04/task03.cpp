#include <iostream>

#define EPS 0.0001f

struct Float {
  Float(float f = 0) :num_(f) {}
  float num_;
  operator float() const {
    return num_;
  }
  
};

bool operator==(Float &f1, Float &f2) {
  return !(f1 < f2) and !(f1>f2);
}

bool operator !=(Float &f1, Float f2) {
  return not f1 == f2;
}

Float operator-(Float &f1) {
  return Float{-f1.num_};
}

bool operator<(Float &f1, Float &f2) {
  return f2.num_-f1.num_>EPS;
}

bool operator>(Float &f1, Float &f2) {
  return f2 < f1;
}

bool operator<=(Float &f1, Float &f2) {
  return f1 < f2 or f1 == f2;
}

bool operator>=(Float &f1, Float &f2) {
  return f1 > f2 or f1 == f2;
}


Float operator+(Float &f, const Float &f2) {
  return f.num_ + f2.num_;
}

Float operator-(Float &f, const Float &f2) {
  return f.num_ + f2.num_;
}

Float operator+=(Float &f1, const Float &f2) {
  f1 = f1+f2;
  return f1;
}

Float operator-=(Float &f1, const  Float &f2) {
  f1 = f1 + f2;
  return f1;
}

int main() {

  Float f1 = 1.0f,
    f2 = 1.00001f,
    f3 = 100;
  
  std::cout << (f1 < f2) << std::endl;    /* hamis */
  std::cout << (f1 < f3) << std::endl;    /* igaz */
  f1 = f2 + f3;
  for (Float f = 0.999; f < 1.001; f += 0.0001) {
  std::cout << f << '\t' << (f < 1.0) << std::endl;
 }
}
