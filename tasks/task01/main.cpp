#include "ratio.h"

int main(int argc, char **argv) {
  Ratio a(1,2);
  Ratio b(2,4);
  std::cout << "1/2 + 2/4 = " << a+b << std::endl;
  std::cout << "-1/2 = " << -a << std::endl;
  std::cout << "1/2 - 2/4 = " << a-b << std::endl;
  a+=b;
  std::cout << "1/2 += 2/4 = " << a << std::endl;
  Ratio c(1,3);
  Ratio d(1,4);
  c-=d;
  std::cout << "1/3 -= 1/4; c = " << c << std::endl;
  std::cout << "(double) 1/3 = " << (double) Ratio(1,3) << std::endl;
  Ratio x(4,5);
  Ratio y(1,2);
  std::cout << "4/5 * 1/2 = " << y*x << std::endl;
  std::cout << "4/5 / 1/2 = " << x/y << std::endl;
  x*=y;
  std::cout << "4/5 *= 1/2 = " << x << std::endl;
  x = Ratio(4,5);
  x/=y;
  std::cout << "4/5 /= 1/2 = " << x << std::endl;
  Ratio z(1,1);
  std::cin >> z;
  std::cout << "cin >> z = " << z << std::endl;
}
