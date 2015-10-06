#include <iostream>
#include <cmath>

struct BasePrinter {
  int base_;
  std::ostream &os_;
  BasePrinter(std::ostream &os, int b): base_(b), os_(os) {}
  std::ostream &operator<<(int num) {
    convert(num);
    return os_;
  }

  void convert(int num) {
    if ( num < base_) {
      os_ << num;
      return;
    }
    char c = num%base_;
    char cc;
    if (c >=10 ) {
      cc = 'A' + c - 10;
    }
    else {
      cc = '0' + c;
    }
    convert(num/base_);
    os_ << cc;
  }
};

struct base {
  int base_;
  base(int bs):base_(bs) {}
};

BasePrinter operator<<(std::ostream &os, base b) {
    return BasePrinter{os, b.base_};
}

int main(int argc, char **argv) {
  std::cout << base(2) << 32321 << std::endl;
  std::cout << base(16) << 32321 << std::endl;
}
