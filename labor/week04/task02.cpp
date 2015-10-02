#include <iostream>

int operator ""_binary(char const *raw ) {
  switch (raw[0]) {
  case '\0':
    return 0;
  case '0':
    return 2* operator""_binary(raw+1);
  case '1':
    return 2*operator""_binary(raw+1)+1;
  }
}


int main() {
    std::cout << 1111_binary << std::endl;      /* 15 */
    std::cout << 10000000_binary << std::endl;  /* 128 */
}
