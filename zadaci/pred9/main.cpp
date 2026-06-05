#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::vector<int> a{1, 2, 3};

  std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, "\n"));

  return 0;
}
