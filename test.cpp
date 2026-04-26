#include <iostream>
#include <vector>
int main() {
  std::vector<int> a{1, 2, 3, 4, 6};

  for (auto &x : a) {
    std::cout << x << " ";
  }
  return 0;
}
