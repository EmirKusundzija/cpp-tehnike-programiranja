// TP 2025/2026: Zadaća 5, Zadatak 6
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

template <typename TipElemenata>
void TransformirajBinarnuDatoteku(
    std::string_view ime_datoteke, bool treba_izvrnuti = true,
    std::function<TipElemenata(TipElemenata)> f =
        [](const auto &x) { return x; }) {
  std::fstream datoteka(std::string(ime_datoteke),
                        std::ios::in | std::ios::out | std::ios::binary);
  if (!datoteka)
    throw std::logic_error("Datoteka ne postoji");

  datoteka.seekg(0, std::ios::end);
  std::streamoff duzina_datoteke = datoteka.tellg();

  if (!datoteka ||
      duzina_datoteke % static_cast<std::streamoff>(sizeof(TipElemenata)) != 0)
    throw std::logic_error("Problemi u pristupu datoteci");

  std::streamoff broj_elemenata =
      duzina_datoteke / static_cast<std::streamoff>(sizeof(TipElemenata));

  if (!treba_izvrnuti) {
    for (std::streamoff i = 0; i < broj_elemenata; i++) {
      TipElemenata element;
      std::streamoff pozicija =
          i * static_cast<std::streamoff>(sizeof(TipElemenata));

      datoteka.seekg(pozicija, std::ios::beg);
      datoteka.read(reinterpret_cast<char *>(&element), sizeof element);
      if (!datoteka)
        throw std::logic_error("Problemi u pristupu datoteci");

      element = f(element);

      datoteka.seekp(pozicija, std::ios::beg);
      datoteka.write(reinterpret_cast<const char *>(&element), sizeof element);
      if (!datoteka)
        throw std::logic_error("Problemi u pristupu datoteci");
    }

    return;
  }

  for (std::streamoff i = 0; i < broj_elemenata / 2; i++) {
    TipElemenata lijevi, desni;
    std::streamoff lijeva_pozicija =
        i * static_cast<std::streamoff>(sizeof(TipElemenata));
    std::streamoff desna_pozicija =
        (broj_elemenata - 1 - i) *
        static_cast<std::streamoff>(sizeof(TipElemenata));

    datoteka.seekg(lijeva_pozicija, std::ios::beg);
    datoteka.read(reinterpret_cast<char *>(&lijevi), sizeof lijevi);
    if (!datoteka)
      throw std::logic_error("Problemi u pristupu datoteci");

    datoteka.seekg(desna_pozicija, std::ios::beg);
    datoteka.read(reinterpret_cast<char *>(&desni), sizeof desni);
    if (!datoteka)
      throw std::logic_error("Problemi u pristupu datoteci");

    lijevi = f(lijevi);
    desni = f(desni);

    datoteka.seekp(lijeva_pozicija, std::ios::beg);
    datoteka.write(reinterpret_cast<const char *>(&desni), sizeof desni);
    if (!datoteka)
      throw std::logic_error("Problemi u pristupu datoteci");

    datoteka.seekp(desna_pozicija, std::ios::beg);
    datoteka.write(reinterpret_cast<const char *>(&lijevi), sizeof lijevi);
    if (!datoteka)
      throw std::logic_error("Problemi u pristupu datoteci");
  }

  if (broj_elemenata % 2 != 0) {
    TipElemenata srednji;
    std::streamoff pozicija =
        (broj_elemenata / 2) *
        static_cast<std::streamoff>(sizeof(TipElemenata));

    datoteka.seekg(pozicija, std::ios::beg);
    datoteka.read(reinterpret_cast<char *>(&srednji), sizeof srednji);
    if (!datoteka)
      throw std::logic_error("Problemi u pristupu datoteci");

    srednji = f(srednji);

    datoteka.seekp(pozicija, std::ios::beg);
    datoteka.write(reinterpret_cast<const char *>(&srednji), sizeof srednji);
    if (!datoteka)
      throw std::logic_error("Problemi u pristupu datoteci");
  }
}

template <typename TipElemenata>
void KreirajBinarnuDatoteku(const std::string &ime_datoteke,
                            const TipElemenata elementi[], int broj_elemenata) {
  std::ofstream datoteka(ime_datoteke, std::ios::binary);
  if (!datoteka)
    throw std::logic_error("Problemi u pristupu datoteci");

  datoteka.write(reinterpret_cast<const char *>(elementi),
                 broj_elemenata * sizeof(TipElemenata));
  if (!datoteka)
    throw std::logic_error("Problemi u pristupu datoteci");
}

template <typename TipElemenata>
void IspisiBinarnuDatoteku(const std::string &ime_datoteke) {
  std::ifstream datoteka(ime_datoteke, std::ios::binary);
  if (!datoteka)
    throw std::logic_error("Datoteka ne postoji");

  TipElemenata element;
  while (datoteka.read(reinterpret_cast<char *>(&element), sizeof element))
    std::cout << element << ' ';

  if (!datoteka.eof())
    throw std::logic_error("Problemi u pristupu datoteci");

  std::cout << '\n';
}

int main() {
  try {
    int brojevi[]{1, 2, 3, 4, 5};
    KreirajBinarnuDatoteku("BROJEVI.DAT", brojevi, 5);

    std::cout << "Pocetni sadrzaj datoteke:\n";
    IspisiBinarnuDatoteku<int>("BROJEVI.DAT");

    TransformirajBinarnuDatoteku<int>("BROJEVI.DAT", false,
                                      [](int x) { return x * x; });
    std::cout << "Nakon kvadriranja bez izvrtanja redoslijeda:\n";
    IspisiBinarnuDatoteku<int>("BROJEVI.DAT");

    TransformirajBinarnuDatoteku<int>("BROJEVI.DAT");
    std::cout << "Nakon izvrtanja redoslijeda bez izmjene vrijednosti:\n";
    IspisiBinarnuDatoteku<int>("BROJEVI.DAT");

    TransformirajBinarnuDatoteku<int>("BROJEVI.DAT", true,
                                      [](int x) { return -x; });
    std::cout << "Nakon negiranja i ponovnog izvrtanja redoslijeda:\n";
    IspisiBinarnuDatoteku<int>("BROJEVI.DAT");

    try {
      TransformirajBinarnuDatoteku<int>("NEPOSTOJECA.DAT");
    } catch (const std::logic_error &e) {
      std::cout << e.what() << '\n';
    }

    {
      std::ofstream losa_datoteka("LOSA.DAT", std::ios::binary);
      char znak = 'A';
      losa_datoteka.write(&znak, 1);
    }

    try {
      TransformirajBinarnuDatoteku<int>("LOSA.DAT");
    } catch (const std::logic_error &e) {
      std::cout << e.what() << '\n';
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << '\n';
  }

  return 0;
}
