#include <cmath>
#include <iostream>

class Vektor {
  double x, y, z;

public:
  Vektor() : x(0), y(0), z(0) {}
  Vektor(double x_novo, double y_novo);
  Vektor(double x_novo, double y_novo, double z_novo);

  void Postavi(double x_novo, double y_novo, double z_novo);
  double DajX() const { return x; }
  double DajY() const { return y; }
  double DajZ() const { return z; }

  double DuzinaVektora() const {
    double zbir = x * x + y * y + z * z;
    return std::sqrt(zbir);
  }
  friend std::ostream &operator<<(std::ostream &tok, const Vektor &v);
  Vektor operator+(const Vektor &v) const;
  Vektor operator-(const Vektor &v) const;
};

Vektor::Vektor(double x_novo, double y_novo) : x(x_novo), y(y_novo), z(0) {}
Vektor::Vektor(double x_novo, double y_novo, double z_novo)
    : x(x_novo), y(y_novo), z(z_novo) {}

void Vektor::Postavi(double x_novo, double y_novo, double z_novo) {
  x = x_novo;
  y = y_novo;
  z = z_novo;
}
std::ostream &operator<<(std::ostream &tok, const Vektor &v) {
  tok << "{" << v.x << "," << v.y << "," << v.z << "}";
  return tok;
}
Vektor Vektor::operator+(const Vektor &v) const {
  return Vektor(x + v.x, y + v.y, z + v.z);
}

Vektor Vektor::operator-(const Vektor &v) const {
  return Vektor(x - v.x, y - v.y, z - v.z);
}

int main() {
  Vektor v(2, 3, 4);

  std::cout << v << "\n";
  std::cout << v.DuzinaVektora() << "\n";
  return 0;
}