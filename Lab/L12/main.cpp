#include <functional>
#include <iostream>
#include <stdexcept>
class StedniRacun {
  double stanje;

public:
  StedniRacun(double pocetno_stanje = 0) : stanje(pocetno_stanje) {
    if (stanje < 0)
      throw std::logic_error("Nedozvoljeno pocetno stanje");
  }
  StedniRacun &Ulozi(double iznos) { return Podigni(-iznos); }
  StedniRacun &Podigni(double iznos) {
    if (iznos > stanje)
      throw std::logic_error("Transakcija odbijena");
    stanje -= iznos;
    return *this;
  }
  double DajStanje() const { return stanje; }
  StedniRacun &ObracunajKamatu(double kamatna_stopa) {
    if (kamatna_stopa < 0)
      throw std::logic_error("Nedozvoljena kamatna stopa");
    return Ulozi(stanje * kamatna_stopa / 100);
  }

  StedniRacun &operator++() {
    this->Ulozi(1);
    return *this;
  }
  StedniRacun operator++(int) {
    StedniRacun staro_stanje = *this;
    this->Ulozi(1);
    return staro_stanje;
  }

  StedniRacun &operator--() {
    this->Podigni(1);
    return *this;
  }

  StedniRacun operator--(int) {
    StedniRacun staro_stanje = *this;
    this->Podigni(1);
    return staro_stanje;
  }

  StedniRacun &operator+=(double iznos) { return this->Ulozi(iznos); }

  StedniRacun &operator-=(double iznos) { return this->Podigni(iznos); }

  StedniRacun operator+(double iznos) const {
    StedniRacun novi = *this;
    novi += iznos;
    return novi;
  }

  StedniRacun operator-(double iznos) const {
    StedniRacun novi = *this;
    novi -= iznos;
    return novi;
  }

  friend std::ostream &operator<<(std::ostream &tok, const StedniRacun &r);
  friend std::istream &operator>>(std::istream &tok, StedniRacun &r);
};

std::ostream &operator<<(std::ostream &tok, const StedniRacun &r) {
  tok << r.stanje;
  return tok;
}

std::istream &operator>>(std::istream &tok, StedniRacun &r) {
  double temp_stanje;

  tok >> temp_stanje;

  if (temp_stanje < 0) {
    tok.setstate(std::ios::failbit);
  } else {
    r.stanje = temp_stanje;
  }

  return tok;
}

// pomocna funkcija za testiranje izuzetaka (Sa rijesenih zadataka)
template <typename TipIzuzetka, typename FunkcijskiTip>
void TestirajIzuzetak(FunkcijskiTip akcija) {
  try {
    akcija();
  } catch (TipIzuzetka &e) {
    std::cout << e.what() << std::endl;
  }
}

int main() {
  // Testni primjer od prof. Jurica
  // StedniRacun s1, s2(100), s3 = 30;
  // s1.Ulozi(30); s2.Ulozi(5); s3.Ulozi(20);
  // std::cout << s1.DajStanje() << " " << s2.DajStanje() << " "
  // << s3.DajStanje() << std::endl; // 30 105 50
  // s1.Ulozi(20); s2.Podigni(50);
  // std::cout << s1.DajStanje() << " " << s2.DajStanje() << " " << std::endl;
  // // 50 55 s1.Ulozi(-20); s2.Podigni(-50); std::cout << s1.DajStanje() << " "
  // << s2.DajStanje() << " " << std::endl; // 30 105 s1.ObracunajKamatu(5);
  // std::cout << s1.DajStanje() << std::endl; // 31.5
  // s1 = 100;
  // std::cout << s1.Ulozi(50).Podigni(20).DajStanje() << std::endl; // 130
  // std::cout << s1.ObracunajKamatu(5).DajStanje() << std::endl; // 136.5
  // std::cout << StedniRacun(80).Ulozi(30).DajStanje() << std::endl; // 110
  // const StedniRacun s4 = s3;
  // std::cout << s4.DajStanje() << std::endl; // 50
  // TestirajIzuzetak<std::logic_error>([]() { StedniRacun s5(-30); });
  // TestirajIzuzetak<std::logic_error>([&]() { s1.Podigni(1000); });
  // TestirajIzuzetak<std::logic_error>([&]() { s1.ObracunajKamatu(-5); });
  // TestirajIzuzetak<std::logic_error>([&]() { s1.Ulozi(-1000); });

  // testiranje operatora
  StedniRacun op(130);

  std::cout << "Stanje racuna op: " << op << "\n";
  std::cout << "---------------------------------------\n";
  // postfiksni operatori;

  op++;

  std::cout << "Stanje nakon postfiksnog ++ operatora: " << op << "\n";
  std::cout << "---------------------------------------\n";
  op--;

  std::cout << "Stanje nakon postfiksnog -- operatora: " << op << "\n";
  std::cout << "---------------------------------------\n";
  // prefiksni operatori
  --op;

  std::cout << "Stanje nakon prefiksnog -- operatora: " << op << "\n";
  std::cout << "---------------------------------------\n";
  ++op;

  std::cout << "Stanje nakon prefiksnog ++ operatora: " << op << "\n";
  std::cout << "---------------------------------------\n";
  // testiranje unosa

  StedniRacun fin_racun;
  StedniRacun pomocni(100);
  double broj;
  std::cout << "Unesite iznos vaseg finog racuna: ";
  if (std::cin >> fin_racun) {
    std::cout << "Super, unijeli ste kako treba vrijednost!\n";
  } else {
    std::cout << "Sramota, nije uneseno kako treba!\n";
    // famozno, izvini oprosti
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }

  std::cout << "Unesite broj koji omogucuje jednokratknu manipulaciju sa "
               "operatorima: ";
  std::cin >> broj;

  fin_racun += broj;

  std::cout << "Operator += primjenjen na operand " << broj
            << " racun sada iznosi: " << fin_racun << "KM!\n";

  fin_racun -= broj;

  std::cout << "Operator -= primjenjen na operand " << broj
            << " racun sada iznosi: " << fin_racun << "KM!\n";

  fin_racun = pomocni + 130;

  std::cout << "Operator + primjenjen na operande 130 i na racun pomocni u "
               "iznosu od 100KM. Racun sada iznosi: "
            << fin_racun << "KM!\n";

  fin_racun = pomocni - 5;

  std::cout << "Operator - primjenjen na operande 5 i na racun pomocni u "
               "iznosu od 100KM. Racun sada iznosi: "
            << fin_racun << "KM!\n";

  std::cout << "Izuzetak pri pogresnom podizanju od 1000: ";

  TestirajIzuzetak<std::logic_error>([&]() { op -= 1000; });
  return 0;
}