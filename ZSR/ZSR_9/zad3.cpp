#include <cmath>
#include <iostream>

class Tacka {
  double x = 0, y = 0;

public:
  void Postavi(double x, double y) {
    this->x = x;
    this->y = y;
  }

  void PostaviPolarno(double ro, double theta) {
    x = ro * std::cos(theta);
    y = ro * std::sin(theta);
  }
  double DajX() const { return x; }
  double DajY() const { return y; }
  double DajRho() const { return std::sqrt(x * x + y * y); }
  double DajTheta() const { return std::atan2(y, x); }
  void PostaviX(double x) { this->x = x; }
  void PostaviY(double y) { this->y = y; }
  bool DaLiJeKoordinatniPocetak() const { return (x == 0 && y == 0); }
  void Transliraj(double delta_x, double delta_y) {
    x += delta_x; // x+Dx
    y += delta_y; // y+Dy
  }
  void Rotiraj(double alpha) {
    Tacka O;
    Rotiraj(alpha, O);
  }
  void Rotiraj(double alpha, const Tacka &centar) {

    double x_novo = centar.x + (x - centar.x) * std::cos(alpha) -
                    (y - centar.y) * std::sin(alpha);
    double y_novo = centar.y + (x - centar.x) * std::sin(alpha) +
                    (y - centar.y) * std::cos(alpha);

    x = x_novo;
    y = y_novo;
  }
  friend bool DaLiSuIdenticne(const Tacka &t1, const Tacka &t2) {
    return t1.x == t2.x && t1.y == t2.y;
  }
  friend double Rastojanje(const Tacka &t1, const Tacka &t2) {
    return std::sqrt((t2.x - t1.x) * (t2.x - t1.x) +
                     (t2.y - t1.y) * (t2.y - t1.y));
  }
};

int main() {

  Tacka q1, q2, q3, q4, ox, oy;

  q1.Postavi(1, 1);
  q2.Postavi(-1, 1);
  q3.Postavi(-1, -1);
  q4.Postavi(1, -1);
  ox.Postavi(5, 0);
  oy.Postavi(0, 5);

  auto Ispisi = [](const Tacka &t, const std::string &naziv) {
    std::cout << naziv << ": ";
    std::cout << "(x, y) = (" << t.DajX() << ", " << t.DajY() << "), ";
    std::cout << "(rho, theta) = (" << t.DajRho() << ", " << t.DajTheta()
              << ")\n";
  };

  Ispisi(q1, "I kvadrant");
  Ispisi(q2, "II kvadrant");
  Ispisi(q3, "III kvadrant");
  Ispisi(q4, "IV kvadrant");
  Ispisi(ox, "Na x-osi");
  Ispisi(oy, "Na y-osi");

  Tacka t;
  t.PostaviPolarno(5, 0);
  Ispisi(t, "PostaviPolarno");

  t.PostaviX(3);
  t.PostaviY(4);
  Ispisi(t, "Nakon PostaviX/PostaviY");

  t.Transliraj(1, -2);
  Ispisi(t, "Nakon translacije");

  std::cout << "Rastojanje q1-q2: " << Rastojanje(q1, q2) << "\n";
  std::cout << "Da li su q1 i q2 identicne: "
            << (DaLiSuIdenticne(q1, q2) ? "Da" : "Ne") << "\n";

  const double PI = 4 * std::atan(1);
  t.Rotiraj(PI / 2);
  Ispisi(t, "Nakon rotacije oko O za 90 stepeni");

  t.Rotiraj(PI / 6, q1);
  Ispisi(t, "Nakon rotacije oko q1 za 30 stepeni");
  return 0;
}