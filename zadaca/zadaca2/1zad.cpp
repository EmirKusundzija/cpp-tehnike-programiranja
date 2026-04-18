// TP 2025/2026: Zadaća 2, Zadatak 1
#include <array>
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
bool vidljivost = true;

const std::array<int, 8> pomaci_x{0, 1, 1, 1, 0, -1, -1, -1};
const std::array<int, 8> pomaci_y{1, 1, 0, -1, -1, -1, 0, 1};

const std::array<const char *, 8> nazivi_pravaca{
    "sjever", "sjeveroistok", "istok", "jugoistok",
    "jug",    "jugozapad",    "zapad", "sjeverozapad"};

int Sirina() { return xmax - xmin + 1; }
int Visina() { return ymax - ymin + 1; }

bool ValidnaPozicija(int x, int y) {
  return xmin <= x && x <= xmax && ymin <= y && y <= ymax;
}

int IndeksX(int x) { return x - xmin; }
int IndeksY(int y) { return ymax - y; }

std::vector<std::vector<int>> NapraviPocetniTeren() {
  std::vector<std::vector<int>> teren(21, std::vector<int>(21, 0));
  teren.at(10).at(10) = 3; // početno: robot na (0,0), vidljiv i polje označeno
  return teren;
}

std::vector<std::vector<int>> teren(NapraviPocetniTeren());

int &DajPolje(int x, int y) { return teren.at(IndeksY(y)).at(IndeksX(x)); }

int CjelobrojnaSredina(int a, int b) {
  long long suma = static_cast<long long>(a) + b;
  if (suma >= 0 || suma % 2 == 0)
    return suma / 2;
  return suma / 2 - 1;
}

void PreskociRazmake() {
  while (std::cin.peek() != EOF && std::cin.peek() != '\n' &&
         std::isspace(static_cast<unsigned char>(std::cin.peek())))
    std::cin.get();
}

void OdbaciLiniju() {
  while (std::cin.peek() != EOF && std::cin.peek() != '\n')
    std::cin.get();
  if (std::cin.peek() == '\n')
    std::cin.get();
}

// Stanja polja:
// 0 - prazno
// 1 - posjeceno
// 2 - robot je na neposjecenom polju
// 3 - robot je na posjecenom polju

void OslobodiTekucuPoziciju(int x, int y) {
  int &polje = DajPolje(x, y);
  if (polje == 2)
    polje = 0;
  else if (polje == 3)
    polje = 1;
}

void PostaviTekucuPoziciju(int x, int y) {
  int &polje = DajPolje(x, y);
  if (vidljivost || polje == 1 || polje == 3)
    polje = 3;
  else
    polje = 2;
}

void UskladiTekucuPozicijuSaVidljivoscu(int x, int y) {
  if (vidljivost && DajPolje(x, y) == 2)
    DajPolje(x, y) = 3;
}

void KreirajTeren(int xmin, int xmax, int ymin, int ymax, int &x, int &y,
                  Pravci &orijentacija) {
  if (xmin >= xmax || ymin >= ymax)
    throw std::range_error("Nelegalan opseg");

  Robot::xmin = xmin;
  Robot::xmax = xmax;
  Robot::ymin = ymin;
  Robot::ymax = ymax;
  vidljivost = true;

  teren =
      std::vector<std::vector<int>>(Visina(), std::vector<int>(Sirina(), 0));

  x = CjelobrojnaSredina(xmin, xmax);
  y = CjelobrojnaSredina(ymin, ymax);
  orijentacija = Pravci::Sjever;

  PostaviTekucuPoziciju(x, y);
}

bool Idi(int &x, int &y, Pravci orijentacija, int korak) {
  UskladiTekucuPozicijuSaVidljivoscu(x, y);

  int indeks_pravca = static_cast<int>(orijentacija);
  int dx = pomaci_x.at(indeks_pravca);
  int dy = pomaci_y.at(indeks_pravca);

  if (korak < 0) {
    korak = -korak;
    dx = -dx;
    dy = -dy;
  }

  for (int i = 0; i < korak; i++) {
    int novi_x = x + dx;
    int novi_y = y + dy;

    if (!ValidnaPozicija(novi_x, novi_y))
      return false;

    OslobodiTekucuPoziciju(x, y);
    x = novi_x;
    y = novi_y;
    PostaviTekucuPoziciju(x, y);
  }

  return true;
}

void Rotiraj(Pravci &orijentacija, int ugao) {
  int novi_pravac = (static_cast<int>(orijentacija) - ugao) % 8;
  if (novi_pravac < 0)
    novi_pravac += 8;
  orijentacija = static_cast<Pravci>(novi_pravac);
}

void Sakrij() { vidljivost = false; }

void Otkrij() { vidljivost = true; }

void IspisiPoziciju(int x, int y, Pravci orijentacija) {
  std::cout << "Robot je " << (vidljivost ? "vidljiv" : "nevidljiv")
            << ", nalazi se na poziciji (" << x << "," << y << ") i gleda na "
            << nazivi_pravaca.at(static_cast<int>(orijentacija)) << ".\n";
}

void PrikaziTeren() {
  for (int i = 0; i < Sirina() + 2; i++)
    std::cout << '#';
  std::cout << '\n';

  for (int yy = ymax; yy >= ymin; yy--) {
    std::cout << '#';
    for (int xx = xmin; xx <= xmax; xx++) {
      int polje = DajPolje(xx, yy);
      if (polje == 2 || polje == 3)
        std::cout << 'O';
      else if (polje == 1)
        std::cout << '*';
      else
        std::cout << ' ';
    }
    std::cout << "#\n";
  }

  for (int i = 0; i < Sirina() + 2; i++)
    std::cout << '#';
  std::cout << '\n';
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
  else if (komanda == Komande::Rotiraj)
    Rotiraj(orijentacija, parametar);
  else if (komanda == Komande::Sakrij)
    Sakrij();
  else if (komanda == Komande::Otkrij) {
    Otkrij();
    UskladiTekucuPozicijuSaVidljivoscu(x, y);
  } else if (komanda == Komande::PrikaziTeren)
    PrikaziTeren();

  return true;
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
  PreskociRazmake();

  if (std::cin.peek() == EOF) {
    komanda = Komande::Kraj;
    return true;
  }

  int c = std::toupper(static_cast<unsigned char>(std::cin.get()));

  if (c == 'I' || c == 'R') {
    Komande nova_komanda = (c == 'I' ? Komande::Idi : Komande::Rotiraj);
    int novi_parametar;

    PreskociRazmake();
    if (std::cin.peek() == '\n' || std::cin.peek() == EOF) {
      kod_greske = KodoviGresaka::NedostajeParametar;
      if (std::cin.peek() == '\n')
        std::cin.get();
      return false;
    }

    if (!(std::cin >> novi_parametar)) {
      kod_greske = KodoviGresaka::NeispravanParametar;
      std::cin.clear();
      OdbaciLiniju();
      return false;
    }

    int sljedeci = std::cin.peek();

    if (sljedeci == EOF || sljedeci == '\n') {
      if (sljedeci == '\n')
        std::cin.get();
      komanda = nova_komanda;
      parametar = novi_parametar;
      return true;
    }

    if (std::isspace(static_cast<unsigned char>(sljedeci))) {
      PreskociRazmake();
      if (std::cin.peek() == EOF || std::cin.peek() == '\n') {
        if (std::cin.peek() == '\n')
          std::cin.get();
        komanda = nova_komanda;
        parametar = novi_parametar;
        return true;
      }
      kod_greske = KodoviGresaka::SuvisanParametar;
      OdbaciLiniju();
      return false;
    }

    kod_greske = KodoviGresaka::NeispravanParametar;
    OdbaciLiniju();
    return false;
  }

  if (c == 'S') {
    int s = std::cin.get();

    if (s == EOF || s == '\n') {
      kod_greske = KodoviGresaka::NedostajeParametar;
      return false;
    }

    if (s != '+' && s != '-') {
      kod_greske = KodoviGresaka::PogresnaKomanda;
      OdbaciLiniju();
      return false;
    }

    Komande nova_komanda = (s == '+' ? Komande::Sakrij : Komande::Otkrij);

    PreskociRazmake();
    if (std::cin.peek() != EOF && std::cin.peek() != '\n') {
      kod_greske = KodoviGresaka::SuvisanParametar;
      OdbaciLiniju();
      return false;
    }

    if (std::cin.peek() == '\n')
      std::cin.get();
    komanda = nova_komanda;
    return true;
  }

  if (c == 'T' || c == 'K') {
    Komande nova_komanda = (c == 'T' ? Komande::PrikaziTeren : Komande::Kraj);

    PreskociRazmake();
    if (std::cin.peek() != EOF && std::cin.peek() != '\n') {
      kod_greske = KodoviGresaka::SuvisanParametar;
      OdbaciLiniju();
      return false;
    }

    if (std::cin.peek() == '\n')
      std::cin.get();
    komanda = nova_komanda;
    return true;
  }

  kod_greske = KodoviGresaka::PogresnaKomanda;
  OdbaciLiniju();
  return false;
}

} // namespace Robot

int main() {
  int t_xmin, t_xmax, t_ymin, t_ymax;
  int x, y, parametar;
  Robot::Pravci orijentacija;
  Robot::Komande komanda;
  Robot::KodoviGresaka kod_greske;

  std::cout << "Unesite dimenzije terena (xmin xmax ymin ymax): ";
  if (!(std::cin >> t_xmin >> t_xmax >> t_ymin >> t_ymax))
    return 0;
  Robot::OdbaciLiniju();

  try {
    Robot::KreirajTeren(t_xmin, t_xmax, t_ymin, t_ymax, x, y, orijentacija);
  } catch (std::range_error &) {
    std::cout << "Nije moguce kreirati takav teren!";
    return 0;
  }

  Robot::IspisiPoziciju(x, y, orijentacija);

  for (;;) {
    std::cout << "Unesi komandu: ";

    if (!Robot::UnosKomande(komanda, parametar, kod_greske)) {
      Robot::PrijaviGresku(kod_greske);
      continue;
    }

    bool uspjeh = Robot::IzvrsiKomandu(komanda, parametar, x, y, orijentacija);

    if (komanda == Robot::Komande::Idi && !uspjeh)
      std::cout << "Robot je pokusao napustiti teren!\n";

    if (komanda == Robot::Komande::Kraj)
      break;

    if (komanda != Robot::Komande::PrikaziTeren)
      Robot::IspisiPoziciju(x, y, orijentacija);
  }

  std::cout << "Dovidjenja!";
  return 0;
}
