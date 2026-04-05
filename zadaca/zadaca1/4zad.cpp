// TP 2025/2026: Zadaća 1, Zadatak 4
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <vector>

std::string UManjaSlova(std::string s) {
  for (int i = 0; i < s.length(); i++)
    s.at(i) = std::tolower((unsigned char)s.at(i));
  return s;
}

std::string Cenzura(std::string recenica,
                    std::vector<std::string> zabranjene_rijeci) {
  std::string temp = "";
  std::string rijec = "";
  // provjera ispravnosti rijeci
  for (int i = 0; i < zabranjene_rijeci.size(); i++)
    for (int j = 0; j < zabranjene_rijeci.at(i).length(); j++) {
      if (!std::isalpha((unsigned char)zabranjene_rijeci.at(i).at(j)) &&
          !std::isdigit((unsigned char)zabranjene_rijeci.at(i).at(j)))
        throw std::logic_error("Neispravna rijec");
    }

  for (int i = 0; i <= recenica.length(); i++) {
    if (i == recenica.length() ||
        (!std::isalpha((unsigned char)recenica.at(i)) &&
         !std::isdigit((unsigned char)recenica.at(i)))) {
      if (!rijec.empty()) {
        bool je_zabranjena = false;
        for (int r_pozicija = 0; r_pozicija < zabranjene_rijeci.size();
             r_pozicija++) {
          std::string r = UManjaSlova(rijec);
          std::string z = UManjaSlova(zabranjene_rijeci.at(r_pozicija));

          if (r == z) {
            je_zabranjena = true;
            break;
          }
        }
        if (je_zabranjena) {
          temp += std::string(rijec.size(), '*');
        } else {
          temp += rijec;
        }
        rijec = "";
      }
      if (i < recenica.length()) {
        temp += recenica.at(i);
      }
    } else {
      rijec += recenica.at(i);
    }
  }

  return temp;
}

int main() {

  std::string recenica;

  std::cout << "Unesite recenicu: ";
  std::getline(std::cin, recenica);
  try {
    std::vector<std::string> lista_zabranjenih_rijeci;
    std::string no_rijec;
    std::cout << "Unesite zabranjene rijeci (. za kraj): ";
    while (std::cin >> no_rijec && no_rijec != ".")
      lista_zabranjenih_rijeci.push_back(no_rijec);
    std::string cenzura_recenice = Cenzura(recenica, lista_zabranjenih_rijeci);
    std::cout << "\nCenzurisana recenica: " << cenzura_recenice;
  } catch (std::logic_error) {
    std::cout << "GRESKA: Nelegalne zabranjene rijeci!\n";
  }

  return 0;
}
