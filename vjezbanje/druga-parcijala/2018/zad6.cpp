#include <algorithm>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>
class Vektor : public std::vector<double> {
public:
  using std::vector<double>::vector;

  int DajVelicinu() const { return this->size(); }
  void GurajNazad(double element) { this->push_back(element); }
  void Sortiraj() { std::sort(this->begin(), this->end()); }
  void Sortiraj(const std::function<bool(double, double)> &a) {
    std::sort(this->begin(), this->end(), a);
  }
  Vektor &operator+=(const Vektor &drugi) {
    this->insert(this->end(), drugi.begin(), drugi.end());
    return *this;
  }

  Vektor operator+(const Vektor &drugi) const {
    Vektor rez = *this;
    rez += drugi;
    return rez;
  }
  Vektor operator*(const Vektor &drugi) const {
    if (this->size() != drugi.size())
      throw std::logic_error("Vektori moraju biti iste duzine!");

    Vektor rez = *this;
    for (int i{}; i < rez.size(); i++) {
      rez[i] *= drugi[i];
    }
    return rez;
  }
  double &operator()(int i) { return this->at(i - 1); }
  const double &operator()(int i) const { return this->at(i - 1); }
  bool DaLiSadrzi(double element) const {
    auto it = std::find(this->begin(), this->end(), element);
    return it != this->end();
  }
  friend std::ostream &operator<<(std::ostream &tok, const Vektor &v) {
    tok << "[";
    for (int i{}; i < v.size(); i++) {

      if (i > 0) {

        tok << ",";
      }
      tok << v[i];
    }
    tok << "]";
    return tok;
  }
  bool operator!() const { return this->empty(); }
  Vektor &operator++() {
    std::for_each(this->begin(), this->end(),
                  [](double &element) { element++; });
    return *this;
  }
  explicit operator double() {
    double suma{};
    std::for_each(this->begin(), this->end(),
                  [&suma](double element) { suma += element; });
    return suma;
  }
  explicit operator double() const {
    double suma{};
    std::for_each(this->begin(), this->end(),
                  [&suma](double element) { suma += element; });
    return suma;
  }
  Vektor operator++(int) {
    Vektor temp = *this;
    ++(*this);
    return temp;
  }
};

int main() {
  auto NR = []() { std::cout << "\n"; };
  Vektor a{1, 3, 2, 10, 7, 8};
  a.Sortiraj();
  std::cout << a;
  NR();
  Vektor b{3.4, 6.7, -5.6};
  std::cout << b;
  NR();
  std::cout << "Da li sadrzi element 6.7 unutar vektora b? "
            << (b.DaLiSadrzi(6.7) ? "Da\n" : "Ne\n");
  b++;
  std::cout << b;
  NR();
  std::cout << double(b);

  Vektor spojen = a + b;
  std::cout << "Spojeni a + b: " << spojen;
  NR();
  return 0;
}