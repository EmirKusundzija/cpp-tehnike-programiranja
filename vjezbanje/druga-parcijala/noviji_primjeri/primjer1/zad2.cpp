#include <iostream>
struct Kalamuta {
  virtual int foo() const { return 5; }
  long int bar() { return 4; }
  virtual int baz() const { return 3; }
  virtual ~Kalamuta() {}
};
struct Cincozna : public Kalamuta {
  int foo() const { return 6; }
  long bar() { return 8; }
  virtual int baz() { return 12; }
};
int main() {
  // Kvadratici su stavljeni da bi bilo jasno, citko i pregledno
  Kalamuta *pk = new Kalamuta, *ck = new Cincozna;
  Cincozna *cc = new Cincozna;

  // 5 [] 4 [] 3
  std::cout << pk->foo() << " " << pk->bar() << " " << pk->baz()
            << std::endl; // poziva svoje vlastite metode iz kalamute jer pk
  // pokazuje upravo na "Kalamutu"
  // 6 [] 4 [] 3
  std::cout << ck->foo() << " " << ck->bar() << " " << ck->baz()
            << std::endl; // e sad ck je pokazivac na Kalamutu a kreira se
                          // Cincozna (ovdje je jako bitno ponasanje)
  // 6 [] 8 [] 12
  std::cout << cc->foo() << " " << cc->bar() << " " << cc->baz()
            << std::endl; // naravno kao i za liniju 17, vazi isto
  // oslobadjamo resurse
  delete pk;
  delete cc;
  delete ck;
  return 0;
}
