#include <iostream>

class Tacka {
  double x, y;

public:
  Tacka(double X, double Y) : x(X), y(Y) {}
  void Postavi(double novo_x, double novo_y) {
    x = novo_x;
    y = novo_y;
  }
  double DajX() const { return x; }
  double DajY() const { return y; }
  static bool DaLiSuJednakeTacke(const Tacka &t1, const Tacka &t2) {
    return t1.x == t2.x && t1.y == t2.y;
  }
  void Ispisi() const { std::cout << "(" << x << ", " << y << ")\n"; }
};

class Duz {
  Tacka t1;
  Tacka t2;

public:
  Duz(Tacka A, Tacka B) : t1(A), t2(B) {}
  Duz(double x1, double y1, double x2, double y2) : t1(x1, y1), t2(x2, y2) {}
  // metode koje rade isto kao konstruktori
  void Postavi(Tacka A, Tacka B) {
    t1 = A;
    t2 = B;
  }
  void Postavi(double x1, double y1, double x2, double y2) {
    Postavi(Tacka(x1, y1), Tacka(x2, y2));
  }
  Tacka Pocetak() const { return t1; }
  Tacka Kraj() const { return t2; }
  static bool DaLiSuJednakeDuzi(const Duz &d1, const Duz &d2) {
    return d1.Pocetak().DajX() == d2.Pocetak().DajX() &&
           d1.Pocetak().DajY() == d2.Pocetak().DajY();
  }
  void Ispisi() const {
    std::cout << "(" << t1.DajX() << "," << t1.DajY() << ")-(" << t2.DajX()
              << "," << t2.DajY() << ") \n";
  }
};

int main() {
  // Demonstracija klase tacka
  Tacka A{1, 2.3};
  Tacka B{1, 2.3};
  std::cout << "Ispis tacaka A i B: ";
  A.Ispisi();
  B.Ispisi();
  std::cout << "Jednakost tacaka A i B: "
            << (Tacka::DaLiSuJednakeTacke(A, B) ? "Jednaki su!"
                                                : "Nisu jednaki!");

  // Demonstracija klase duz

  Duz DO(1, 2, 3, 4);

  DO.Ispisi();
  DO.Postavi(2, 3, 4, 5);
  DO.Ispisi();

  // jednakost duzi

  Duz RD(10, 49, 30, 40);
  Duz DR(10, 49, 30, 40);

  std::cout << "Jednakost duzi RD i DR: "
            << (Duz::DaLiSuJednakeDuzi(RD, DR) ? "Jednaki su!"
                                               : "Nisu jednaki!");

  return 0;
}