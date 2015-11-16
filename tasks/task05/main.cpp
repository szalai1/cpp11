#include <map>
#include <set>
#include <iostream>


int main() {
  std::map<std::string,int> m;
  std::string s;
  while (std::cin >> s)
    ++m[s];
  std::set<std::pair<int, std::string>> ss;
  for ( auto it : m) {
    ss.insert(std::make_pair(it.second, it.first));
  }
  for (auto p : ss)
    std::cout << p.first << " " << p.second << std::endl;
}
