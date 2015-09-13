// a kod orarol: 
#include "ratio.h"

Ratio::Ratio(int num, int den) {
  /* Euclidean: gcd -> a */
  int a = num, b = den, t;
  while (b != 0)
    t = a%b, a = b, b = t;
  num_ = num/a;
  den_ = den/a;
}

Ratio operator+(Ratio r1, Ratio r2) {
  return Ratio(
               r1.num() * r2.den() + r2.num() * r1.den(),
               r1.den() * r2.den());
}

Ratio operator+=(Ratio &lv, const Ratio &rv) {
  lv = lv+rv;
  return lv;
}

Ratio operator-(Ratio &r1, Ratio &r2) {
  return r1+(-r2);
}

Ratio operator-(const Ratio &val) {
  return Ratio(-val.num(), val.den());
}

Ratio operator-=(Ratio &lv, const Ratio &rv) {
  lv+= (-rv);
  return lv;
}

Ratio operator*( const Ratio &lv, const Ratio &rv) {
  return Ratio(lv.num() * rv.num(),
               lv.den() * rv.den());
}

Ratio operator*=(Ratio &lv, const Ratio &rv) {
  lv = lv * rv;
  return lv;
}

Ratio operator/(const Ratio &lv, const Ratio &rv) {
  return lv * Ratio(rv.den(), rv.num());
}

Ratio operator/=(Ratio &lv, const Ratio &rv) {
  lv *= Ratio(rv.den(), rv.num());
  return lv;
}

std::ostream &operator<<(std::ostream &os, Ratio r) {
  os << r.num() << '/' << r.den();
  return os;
}

std::istream &operator>>(std::istream &is, Ratio &r ) {
  int num, den;
  is >> num >> den;
  r = Ratio(num, den);
  return is;
}


