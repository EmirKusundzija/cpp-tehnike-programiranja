#include <iostream>
#include <map>
#include <string>
std::string MonoalphSistem(const std::string &s, std::map<char, char> mapa) {
  std::string rez;
  for (auto &c : s) {
    auto it = mapa.find(c);
    if (it != mapa.end())
      rez.push_back(it->second);
    else
      rez.push_back(c);
  }

  return rez;
}
int main() {
  // testiranje funkcije
  std::map<char, char> kljuc = {{'a', 'x'}, {'b', 'c'}, {'c', 'a'}};
  auto test = MonoalphSistem("abcbcaccbac", kljuc);
  std::cout << test << "\n";
  return 0;
}
