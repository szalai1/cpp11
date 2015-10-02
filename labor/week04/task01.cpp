#include <iostream>

struct TimeInterval {
  unsigned long long  min_; 
};

std::ostream & operator<<(std::ostream &os, TimeInterval& ti) {
  os << ti.min_/(24*60) << " min " << (ti.min_%(24*60))/(60) << " h "  << ti.min_%60 << " min";
  return os;
}

constexpr TimeInterval operator""_m (unsigned long long num) {
  return TimeInterval{num};
}

constexpr TimeInterval operator""_h (unsigned long long num) {
  return TimeInterval{num*60};
}

TimeInterval operator+(const TimeInterval &t,const  TimeInterval &t2) {
  return TimeInterval{t.min_+ t2.min_};
}

int main() {
  TimeInterval i1{65};            /* percben */
  std::cout << i1 << std::endl;   /* 1h 5m */
  
  TimeInterval i2 = 5_h + 79_m;
  std::cout << i2 << std::endl;   /* 6h 19m */
  
}
