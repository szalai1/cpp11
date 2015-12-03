#include <iostream>
#include <thread>


//this is so dum

void f(int num) {
  int jj = 0;
  for (int ii = 0; ii < 10000000000; ++ii) {
    jj += ii;
    if ( jj %100000000 == 0) {
      std::cout << num << std::endl;
    }
  }
}


int main() {
  std::thread th{f, 1};
  std::thread th2{f, 2};
  th2.join();
  th.join();

}
