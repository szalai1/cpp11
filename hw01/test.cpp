#include "test.h"

void test1() {
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
  MyString s1{"alma"};
  MyString s2{"fa"};
  s1 += s2;
  std::cout << "almafa ?= " << s1 << std::endl;
}

void test3() {
  MyString s1{"alma"};
  MyString s2 = s1;
  s1[0] = 'A';
  std::cout << "Alam ?= " << s1 << std::endl; 
}


void test4() {
  MyString s1{"alma"};
  s1 += 'A';
  std::cout << "alamA ?= " << s1 << std::endl;
}

void test5() {
  MyString s1{"Ez"};
  MyString s2{"egy"};
  MyString s3{"fa"};
  s1 = s1 + ' ' + s2 + ' ' + s3 + '.';
  std::cout << "Ez egy fa. ?= " << s1  << std::endl;
}


void test6() {
  MyString s1{"Valami"};
  MyString s2 = s1;
  MyString s3 = s2;
  s1[0] = 'x';
  std::cout << "x ?=" << s1[0] << std::endl;
  s3[4] = '#';
}
