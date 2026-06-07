#include <iostream>
#include <stack>

int main() {
  std::stack<int> a;

  a.push(2);
  a.push(3);
  a.push(-1);
  a.push(6);
  while (!a.empty()) {
    std::cout << a.top() << " ";
    a.pop();
  }
  return 0;
}
