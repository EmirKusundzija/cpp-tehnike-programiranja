
#include <iostream>
#include <stdexcept>

class StedniRacun {
  double stanje;

public:
  StedniRacun(double poc_stanje = 0) : stanje(poc_stanje) {

    if (stanje < 0)
      throw std::logic_error("Nedozvoljeno pocetno stanje");
  }
  StedniRacun &Ulozi(double pare) { return Podigni(-pare); }
  StedniRacun &Podigni(double pare) {
    if (pare > stanje)
      throw std::logic_error("Transakcija odbijena");
    stanje -= pare;
    return *this;
  }
  StedniRacun &ObracunajKamatu(double kamatna_stopa) {
    if (kamatna_stopa < 0)
      throw std::logic_error("Nedozvoljena kamatna stopa");
    return Ulozi(stanje * kamatna_stopa / 100);
  }
  double DajStanje() const { return stanje; }
};

int main() {
  StedniRacun s1, s2(100), s3 = 30;
  s1.Ulozi(30);
  s2.Ulozi(5);
  s3.Ulozi(20);
  std::cout << s1.DajStanje() << " " << s2.DajStanje() << " " << s3.DajStanje()
            << std::endl; // 30 105 50
  s1.Ulozi(20);
  s2.Podigni(50);
  std::cout << s1.DajStanje() << " " << s2.DajStanje() << " "
            << std::endl; // 50 55
  s1.Ulozi(-20);
  s2.Podigni(-50);
  std::cout << s1.DajStanje() << " " << s2.DajStanje() << " "
            << std::endl; // 30 105
  s1.ObracunajKamatu(5);
  std::cout << s1.DajStanje() << std::endl; // 31.5
  s1 = 100;
  std::cout << s1.Ulozi(50).Podigni(20).DajStanje() << std::endl;  // 130
  std::cout << s1.ObracunajKamatu(5).DajStanje() << std::endl;     // 136.5
  std::cout << StedniRacun(80).Ulozi(30).DajStanje() << std::endl; // 110
  const StedniRacun s4 = s3;
  std::cout << s4.DajStanje() << std::endl;

  return 0;
}
