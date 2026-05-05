#include <iostream>
#include <stdexcept>

struct Vrijeme {
  int sati, minute, sekunde;
};

void JeLiIspravno(const Vrijeme &v) {
  if (v.sati < 0 || v.sati > 23 || v.minute < 0 || v.minute > 59 ||
      v.sekunde < 0 || v.sekunde > 59)
    throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme(const Vrijeme &v) {

  std::cout << (v.sati < 10 ? "0" : "") << v.sati << ":"
            << (v.minute < 10 ? "0" : "") << v.minute << ":"
            << (v.sekunde < 10 ? "0" : "") << v.sekunde << "\n";
}

Vrijeme ZbirVremena(const Vrijeme &v1, const Vrijeme &v2) {
  JeLiIspravno(v1);
  JeLiIspravno(v2);
  Vrijeme v3{v1.sati + v2.sati, v1.minute + v2.minute, v1.sekunde + v2.sekunde};
  v3.minute += v3.sekunde / 60;
  v3.sekunde %= 60;
  v3.sati += v3.minute / 60;
  v3.minute %= 60;
  v3.sati %= 24;
  return v3;
}

int main() {
  try {

    Vrijeme v1, v2;
    std::cout << "Unesite prvo vrijeme (h m s): ";
    std::cin >> v1.sati >> v1.minute >> v1.sekunde;
    JeLiIspravno(v1);
    std::cout << "Unesite drugo vrijeme (h m s): ";
    std::cin >> v2.sati >> v2.minute >> v2.sekunde;
    JeLiIspravno(v2);
    std::cout << "Prvo vrijeme: ";
    IspisiVrijeme(v1);
    std::cout << "Drugo vrijeme: ";
    IspisiVrijeme(v2);
    std::cout << "Zbit vremena: ";
    IspisiVrijeme(ZbirVremena(v1, v2));
  } catch (std::domain_error &e) {
    std::cout << e.what() << "\n";
  }
  return 0;
}
