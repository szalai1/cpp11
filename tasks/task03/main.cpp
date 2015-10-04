#include <iostream>
#include <cmath>

double log_b(int base, double num) {
  return log10(num)/log10(base);
}

struct BasePrinter {
  int base_;
  std::ostream &os_;
  BasePrinter(std::ostream &os, int b): base_(b), os_(os) {}
  std::ostream &operator<<(int num) {
    convert(num);
    return os_;
  }
  void convert(int num) {
    int max_digit = log_b(base_, num);
    convert_helper(num, max_digit);
  }
  void convert_helper(int num, int digit) {
    if (digit == -1) {
      return;
    }
    int max_val = pow( base_, digit);
    int c = num/max_val;
    char cc;
    if (c >=10 ) {
      cc = 'A' + c - 10;
    }
    else {
      cc = '0' + c;
    }
    os_ << cc;
    convert_helper(num%max_val, digit-1);
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
}
