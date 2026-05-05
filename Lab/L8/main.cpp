#include <iomanip>
#include <iostream>
#include <stdexcept>

// iskopirati kod sa Rijesenih zadataka
// struktura vrijeme ne sadrzi minute sate i sekunde, vec samo ukupne sekunde
// sve funkcije koje podesavaju da radi sa sekundama

struct Vrijeme {
  int sekunde;
};

void TestirajVrijeme(const Vrijeme &v) {

  int ukupno_sekundi = v.sekunde;

  int sati = ukupno_sekundi / 3600;
  int minute = (ukupno_sekundi % 3600) / 60;
  int sekunde = ukupno_sekundi % 60;

  if (sati < 0 || sati > 23 || minute < 0 || minute > 59 || sekunde < 0 ||
      sekunde > 59)
    throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme(const Vrijeme &v) {

  TestirajVrijeme(v);

  int ukupno_sekundi = v.sekunde;

  int sati = ukupno_sekundi / 3600;
  int minute = (ukupno_sekundi % 3600) / 60;
  int sekunde = ukupno_sekundi % 60;

  char stara_ispuna = std::cout.fill('0');
  std::cout << std::setw(2) << sati << ":" << std::setw(2) << minute << ":"
            << std::setw(2) << sekunde;
  std::cout.fill(stara_ispuna);
}

Vrijeme ZbirVremena(const Vrijeme &v1, const Vrijeme &v2) {
  TestirajVrijeme(v1);
  TestirajVrijeme(v2);

  Vrijeme v3;
  // 24h = 24*3600 = 86400s
  v3.sekunde = (v1.sekunde + v2.sekunde) % 86400;

  return v3;
}

int main() {
  try {
    Vrijeme v1, v2;

    // BITNO:
    // 1h = 3600s
    // 1 min = 60s

    // testni primjer iz zadatka
    // 3h 34m 52s = 12892s
    // 4h 42m 20s = 16940s
    std::cout << "Unesite prvo vrijeme (s): ";
    std::cin >> v1.sekunde;

    std::cout << "Unesite drugo vrijeme (s): ";
    std::cin >> v2.sekunde;

    std::cout << "Prvo vrijeme: ";
    IspisiVrijeme(v1);
    std::cout << std::endl << "Drugo vrijeme: ";
    IspisiVrijeme(v2);
    std::cout << std::endl << "Zbir vremena: ";
    IspisiVrijeme(ZbirVremena(v1, v2));
    std::cout << std::endl;
  } catch (std::domain_error e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
