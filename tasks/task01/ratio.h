#include <iostream>

class Ratio {       /* rational number */
public:
  Ratio(int num, int den);
  int num() const { return num_; }
  int den() const { return den_; }

  operator double() {
    return this->num()/(double) this->den();
  }

private:
  int num_;       /* numerator */
  int den_;       /* denominator */
};

Ratio operator*=(Ratio &lv, const Ratio &rv);
Ratio operator+=(Ratio &lv, const Ratio &rv);
Ratio operator+(Ratio r1, Ratio r2);
Ratio operator-(Ratio &r1, Ratio &r2);
Ratio operator-(const Ratio &r1);
Ratio operator-=(Ratio &lv, const Ratio &rv );
Ratio operator*( const Ratio &lv, const Ratio &rv);
Ratio operator/( const Ratio &lv, const Ratio &rv);
Ratio operator/=(Ratio &lv, const Ratio &rv); 
std::ostream &operator<<(std::ostream &os, Ratio r);
std::istream &operator>>(std::istream &is, Ratio &r);
