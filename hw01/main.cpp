#include "string.h"
#include "test.h"

void g(std::string x) {
  std::cout << "\n\ncatalog: " << x << "\n";
  for ( auto i : MyString::catalog_) {
    std::cout << "#>" << i.first << std::endl;
  }
}
int main() {
  test1();
  g(">>>");
  std::cout << "\n #########" << std::endl;
  test2();
  g(">>>");
  std::cout<< "\n #########" << std::endl;
  //test3();
  g(">>>");
  std::cout<< "\n #########" << std::endl;
  test4();
  std::cout << "\n #########"<< std::endl;
  test5();
  g(">>>");
}
