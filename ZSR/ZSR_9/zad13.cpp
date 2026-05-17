#include <iostream>

class Televizor {
  int kanal{1};
  int glasnoca{1};
  bool ukljucen{true};

public:
  void Ukljuci() { ukljucen = true; }
  void Iskljuci() { ukljucen = false; }
  void PostaviGlasnocu(int glasnoca) {
    if (glasnoca < 1 || glasnoca > 9 || ukljucen == false)
      return;

    this->glasnoca = glasnoca;
  }
  void PostaviKanal(int kanal) {
    if (kanal < 1 || kanal > 150 || ukljucen == false)
      return;
    this->kanal = kanal;
  }
  void KanalNaprijed() {
    if (ukljucen == false)
      return;
    if (kanal == 150)
      kanal = 1;
    else
      kanal++;
  }
  void KanalNazad() {
    if (ukljucen == false)
      return;
    if (kanal == 1)
      kanal = 150;
    else
      kanal--;
  }
  void Pojacaj() {
    // u rasponu od 1 do 9
    if (glasnoca == 9 || ukljucen == false)
      return;
    glasnoca++;
  }
  void Stisaj() {
    if (glasnoca == 1 || ukljucen == false)
      return;
    glasnoca--;
  }

  void Prikazi() const {
    if (ukljucen == true) {
      std::cout << "-----------------------------\n";
      std::cout << "Broj kanala: " << kanal << "\n";
      std::cout << "Glasnoca: " << glasnoca << "\n";
      std::cout << "-----------------------------\n";
    }
  }
};

int main() {
  auto novi_red = [] { std::cout << "\n"; };
  Televizor Samsung;

  Samsung.PostaviKanal(2);

  Samsung.Prikazi();

  // pojacavanja Samsung-a
  novi_red();
  Samsung.Pojacaj();
  Samsung.Pojacaj();
  Samsung.Pojacaj();

  Samsung.Prikazi();

  novi_red();

  Samsung.PostaviKanal(10);
  Samsung.Prikazi();

  novi_red();

  Samsung.Pojacaj();
  Samsung.PostaviKanal(150);
  Samsung.Prikazi();

  novi_red();

  Samsung.KanalNaprijed();
  Samsung.Prikazi();
  return 0;
}