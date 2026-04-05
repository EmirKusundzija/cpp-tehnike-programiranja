#include <iostream>
#include <string>

void Izvrsni(std::string &s) {

  for (int i = 0; i < s.length() / 2; i++) {
    char temp = s.at(i);
    s.at(i) = s.at(s.length() - 1 - i);
    s.at(s.length() - 1 - i) = temp;
  }
}

int main() {
  std::string s = "Ovo je neki tekst...";
  Izvrsni(s);
  std::cout << s;

  return 0;
}