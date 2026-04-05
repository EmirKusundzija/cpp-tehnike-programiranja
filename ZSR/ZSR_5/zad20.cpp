#include <algorithm>
#include <iostream>

template <typename IterTip>
bool JednakiBlokovi(IterTip p1, IterTip p2, IterTip p3) {
  while (p1 != p2) {
    if (*p1 != *p3)
      return false;
    p1++;
    p3++;
  }
  return true;
}

int main() {

  int a[5]{1, 2, 3, 0x3, 4};
  int b[5]{1, 2, 3, 0x3, 4};

  bool test1 = JednakiBlokovi(a, a + 5, b);

  std::cout << "Homemade funkcija: " << std::boolalpha << test1 << "\n";

  bool test2 = std::equal(a, a + 5, b);

  std::cout << "std::equal: " << std::boolalpha << test2 << "\n";
  return 0;
}