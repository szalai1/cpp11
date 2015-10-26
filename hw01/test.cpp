#include "test.h"

void f(std::string x) {
  std::cout << "\n\ncatalog: " << x << "\n";
  for ( auto i : MyString::catalog_) {
    std::cout << "#>" << i.first << std::endl;
  }
}


void test1() {
  f("1");
  MyString s1;
  s1 = "s1";
  MyString s2 = s1;
  s2 = s1;
  s1 = s2;
  s2 = s2;
  s1 = s2 = s1;
  std::cout << "s1 ?= " << s1 <<std::endl;
  std::cout << "s1 ?= " << s2 <<std::endl;
}

void test2() {
  f("2");
  MyString s1{"alma"};
  MyString s2{"fa"};
  s1 += s2;
  f("3");
  std::cout << "almafa ?= " << s1 << std::endl;
}

void test3() {
  f("4");
  MyString s1{"alma"};
  s1[0] = 'A';
  std::cout << "Alam ?= " << s1 << std::endl; 
}


void test4() {
  f("x");
  std::cout << "xxxx0" << std::endl;
  MyString s1{"alma"};
  f("y");
  std::cout << "xxxx1" << std::endl;
  s1 += 'A';
  std::cout << "xxxx2" << std::endl;
  std::cout << "alamA ?= " << s1 << std::endl;
  std::cout << "xxxx3" << std::endl;
}

void test5() {
  MyString s1{"Ez"};
  MyString s2{"egy"};
  MyString s3{"fa"};
  s1 = s1 + ' ' + s2 + ' ' + s3 + '.';
  std::cout << "Ez egy fa. ?= " << s1  << std::endl;
}
