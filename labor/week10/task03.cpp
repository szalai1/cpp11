#include <cmath>
#include <functional>
#include <iostream>

std::function<double(double)> logged_func(std::function<double(double)> fg,
                                          std::string str) {
  return  [=](double x) -> double {
    std::cout << " Log: str(" << x << ")" << std::endl;
    return fg(x);
  };
}

int main() {
    auto logged_sin = logged_func(sin, "sin");
    std::cout << logged_sin(1.2) << std::endl;
}
