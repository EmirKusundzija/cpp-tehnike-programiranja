#include <iostream>
#include <vector>
int main() {
  std::vector<int> a{1, 2, 3};
  for (auto &x : a) {

    std::cout << x << " ";
  }
  return 0;
}
