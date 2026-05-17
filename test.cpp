#include <iostream>
#include <vector>
int main() {
  // C++17 i nadalje
  std::vector brojevi{1, 2, 3, 4, 5};
  auto p1 = brojevi.begin();
  auto p2 = brojevi.end();
  while (p1 != p2) {

    std::cout << *p1++ << " ";
  }
  return 0;
}
