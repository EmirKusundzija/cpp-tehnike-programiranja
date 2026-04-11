// TP 2025/2026: Zadaća 2, Zadatak 1
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace Robot {
enum class Pravci {
  Sjever,
  Sjeveroistok,
  Istok,
  Jugoistok,
  Jug,
  Jugozapad,
  Zapad,
  Sjeverozapad
};
enum class KodoviGresaka {
  PogresnaKomanda,
  NedostajeParametar,
  SuvisanParametar,
  NeispravanParametar
};
enum class Komande { Idi, Rotiraj, Sakrij, Otkrij, PrikaziTeren, Kraj };

int xmin = -10, xmax = 10, ymin = -10, ymax = 10;
bool vidljiv = true;
std::vector<std::vector<int>> teren = [] {
  std::vector<std::vector<int>> t(21, std::vector<int>(21, 0));
  t.at(10).at(10) = 3; // bit0: posjeceno, bit1: robot
  return t;
}();

const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

const char *nazivi[] = {"sjever", "sjeveroistok", "istok", "jugoistok",
                        "jug",    "jugozapad",    "zapad", "sjeverozapad"};

int Sirina() { return xmax - xmin + 1; }

int Visina() { return ymax - ymin + 1; }

bool ValidnaPozicija(int x, int y) {
  return xmin <= x && x <= xmax && ymin <= y && y <= ymax;
}

int IndeksX(int x) { return x - xmin; }
int IndeksY(int y) { return ymax - y; }

int Sredina(int a, int b) {
  long long int suma = (long long int)a + b;
  return (suma >= 0 || suma % 2 == 0) ? suma / 2 : suma / 2 - 1;
}

void Oznaci(int x, int y) {
  if (ValidnaPozicija(x, y))
    teren.at(IndeksY(y)).at(IndeksX(x)) |= 1;
}

void OznaciRobota(int x, int y) {
  if (ValidnaPozicija(x, y))
    teren.at(IndeksY(y)).at(IndeksX(x)) |= 2;
}

void UkloniRobota(int x, int y) {
  if (ValidnaPozicija(x, y))
    teren.at(IndeksY(y)).at(IndeksX(x)) &= ~2;
}

void PreskociRazmake() {
  while (std::cin.peek() != EOF && std::cin.peek() != '\n' &&
         std::isspace((unsigned char)std::cin.peek()))
    std::cin.get();
}

void OdbaciLiniju() {
  while (std::cin.peek() != EOF && std::cin.peek() != '\n')
    std::cin.get();
  if (std::cin.peek() == '\n')
    std::cin.get();
}

void KreirajTeren(int xmin, int xmax, int ymin, int ymax, int &x, int &o,
                  Pravci &orijentacija) {
  if (xmin >= xmax || ymin >= ymax)
    throw std::range_error("Nelegalan opseg");

  Robot::xmin = xmin;
  Robot::xmax = xmax;
  Robot::ymin = ymin;
  Robot::ymax = ymax;
  vidljiv = true;

  teren.assign(Visina(), std::vector<int>(Sirina(), 0));
  x = Sredina(xmin, xmax);
  o = Sredina(ymin, ymax);
  orijentacija = Pravci::Sjever;
  OznaciRobota(x, o);
  Oznaci(x, o);
}

bool Idi(int &x, int &y, Pravci orijentacija, int korak) {
  int p = (int)orijentacija, pom_x = dx[p], pom_y = dy[p];
  if (korak < 0) {
    korak = -korak;
    pom_x = -pom_x;
    pom_y = -pom_y;
  }
  for (int i = 0; i < korak; i++) {
    int n_x = x + pom_x, n_y = y + pom_y;
    if (!ValidnaPozicija(n_x, n_y))
      return false;

    UkloniRobota(x, y);
    x = n_x;
    y = n_y;
    OznaciRobota(x, y);
    if (vidljiv)
      Oznaci(x, y);
  }
  return true;
}
void Rotiraj(Pravci &orijentacija, int ugao) {
  int p = ((int)orijentacija - ugao) % 8;
  if (p < 0)
    p += 8;
  orijentacija = (Pravci)p;
}

void Sakrij() { vidljiv = false; }
void Otkrij() {
  vidljiv = true;
  for (std::size_t i = 0; i < teren.size(); i++) {
    for (std::size_t j = 0; j < teren.at(i).size(); j++) {
      if (teren.at(i).at(j) & 2)
        teren.at(i).at(j) |= 1;
    }
  }
}

void IspisiPoziciju(int x, int y, Pravci orijentacija) {
  std::cout << "Robot je " << (vidljiv ? "vidljiv" : "nevidljiv")
            << ", nalazi se na poziciji (" << x << "," << y << ") i gleda na "
            << nazivi[(int)orijentacija] << ".\n";
}

void PrikaziTeren() {
  for (int i = 0; i < Sirina() + 2; i++)
    std::cout << '#';
  std::cout << "\n";
  for (int yy = ymax; yy >= ymin; yy--) {
    std::cout << '#';
    for (int xx = xmin; xx <= xmax; xx++) {
      int polje = teren.at(IndeksY(yy)).at(IndeksX(xx));
      std::cout << ((polje & 2) ? 'O' : ((polje & 1) ? '*' : ' '));
    }
    std::cout << "#\n";
  }
  for (int i = 0; i < Sirina() + 2; i++)
    std::cout << '#';
  std::cout << "\n";
}

void PrijaviGresku(KodoviGresaka kod_greske) {
  if (kod_greske == KodoviGresaka::PogresnaKomanda)
    std::cout << "Nerazumljiva komanda!\n";
  else if (kod_greske == KodoviGresaka::NedostajeParametar)
    std::cout << "Komanda trazi parametar koji nije naveden!\n";
  else if (kod_greske == KodoviGresaka::SuvisanParametar)
    std::cout << "Zadan je suvisan parametar nakon komande!\n";
  else
    std::cout << "Parametar komande nije ispravan!\n";
}

bool IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,
                   Pravci &orijentacija) {
  if (komanda == Komande::Idi)
    return Idi(x, y, orijentacija, parametar);
  if (komanda == Komande::Rotiraj)
    Rotiraj(orijentacija, parametar);
  else if (komanda == Komande::Sakrij)
    Sakrij();
  else if (komanda == Komande::Otkrij)
    Otkrij();
  else if (komanda == Komande::PrikaziTeren)
    PrikaziTeren();
  return true;
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
  PreskociRazmake();
  if (std::cin.peek() == EOF) {
    komanda = Komande::Kraj;
    return true;
  }

  int c = std::toupper((unsigned char)std::cin.get());
  if (c == 'I' || c == 'R') {
    komanda = (c == 'I' ? Komande::Idi : Komande::Rotiraj);
    PreskociRazmake();

    if (std::cin.peek() == '\n' || std::cin.peek() == EOF) {
      kod_greske = KodoviGresaka::NedostajeParametar;
      OdbaciLiniju();
      return false;
    }

    if (!(std::cin >> parametar)) {
      kod_greske = KodoviGresaka::NeispravanParametar;
      std::cin.clear();
      OdbaciLiniju();
      return false;
    }

    int sljedeci = std::cin.peek();
    if (sljedeci != EOF && sljedeci != '\n' &&
        !std::isspace((unsigned char)sljedeci)) {
      kod_greske = KodoviGresaka::NeispravanParametar;
      OdbaciLiniju();
      return false;
    }

    PreskociRazmake();
    if (std::cin.peek() != EOF && std::cin.peek() != '\n') {
      kod_greske = KodoviGresaka::SuvisanParametar;
      OdbaciLiniju();
      return false;
    }
    if (std::cin.peek() == '\n')
      std::cin.get();
    return true;
  }

  if (c == 'S') {
    int s = std::cin.get();
    if (s == '+')
      komanda = Komande::Sakrij;
    else if (s == '-')
      komanda = Komande::Otkrij;
    else {
      kod_greske = (s == '\n' || s == EOF ? KodoviGresaka::NedostajeParametar
                                          : KodoviGresaka::NeispravanParametar);
      OdbaciLiniju();
      return false;
    }
  } else if (c == 'T')
    komanda = Komande::PrikaziTeren;
  else if (c == 'K')
    komanda = Komande::Kraj;
  else {
    kod_greske = KodoviGresaka::PogresnaKomanda;
    OdbaciLiniju();
    return false;
  }

  PreskociRazmake();
  if (std::cin.peek() != EOF && std::cin.peek() != '\n') {
    kod_greske = KodoviGresaka::SuvisanParametar;
    OdbaciLiniju();
    return false;
  }
  if (std::cin.peek() == '\n')
    std::cin.get();

  return true;
}
} // namespace Robot

using namespace Robot;

int main() {
  int t_xmin, t_xmax, t_ymin, t_ymax;
  int x, y, parametar;
  Pravci orijentacija;
  Komande komanda;
  KodoviGresaka kod_greske;

  std::cout << "Unesite dimenzije terena (xmin xmax ymin ymax): ";
  if (!(std::cin >> t_xmin >> t_xmax >> t_ymin >> t_ymax))
    return 0;
  OdbaciLiniju();

  try {
    KreirajTeren(t_xmin, t_xmax, t_ymin, t_ymax, x, y, orijentacija);
  } catch (std::range_error &) {
    std::cout << "Nije moguce kreirati takav teren!";
    return 0;
  }

  IspisiPoziciju(x, y, orijentacija);
  for (;;) {
    std::cout << "Unesite komandu: ";
    if (!UnosKomande(komanda, parametar, kod_greske)) {
      PrijaviGresku(kod_greske);
      continue;
    }

    bool uspjeh = IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
    if (komanda == Komande::Idi && !uspjeh)
      std::cout << "Robot je pokusao napustiti teren!\n";

    if (komanda == Komande::Kraj)
      break;

    if (komanda != Komande::PrikaziTeren)
      IspisiPoziciju(x, y, orijentacija);
  }

  std::cout << "Dovidjenja!";
  return 0;
}
