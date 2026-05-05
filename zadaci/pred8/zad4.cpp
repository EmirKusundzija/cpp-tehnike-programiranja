#include <iostream>
#include <map>
#include <string>
std::string
ZamijeniPremaRjecniku(const std::string &s,
                      const std::map<std::string, std::string> &mapa) {

  int i = 0, d = s.length();

  std::string izlazni;
  while (i < d) {
    while (i < d && s[i] == ' ')
      izlazni += s[i++];

    std::string rijec;
    while (i < d && s[i] != ' ')
      rijec += s[i++];
    auto it = mapa.find(rijec);
    if (it == mapa.end())
      izlazni += rijec;
    else
      izlazni += it->second;
  }
  return izlazni;
}
int main() {
  // test
  std::map<std::string, std::string> moj_rjecnik{{"jabuka", "apple"},
                                                 {"da", "yes"},
                                                 {"kako", "how"},
                                                 {"ne", "no"},
                                                 {"majmun", "monkey"}};
  std::cout << ZamijeniPremaRjecniku("kako da ne", moj_rjecnik);
  return 0;
}
