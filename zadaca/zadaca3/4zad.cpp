// TP 2025/2026: Zadaća 3, Task 4
#include <forward_list>
#include <iostream>
#include <stdexcept>
#include <vector>
// N - broj blokova (od 1 do N)
// M -  korak razbrajanja
std::vector<int> Razbrajanje(int N, int M) {
  std::vector<int> rez;
  if (N <= 0 || M <= 0)
    return rez;
  rez.reserve(N);

  std::forward_list<int> lista(N);
  int br = 1; // pocetni blok
  for (auto &x : lista) {
    x = br++;
  }
  rez.push_back(1);
  lista.pop_front();

  auto prethodni = lista.before_begin();
  auto trenutni = lista.begin();
  int preostali_blokovi = N - 1;

  while (preostali_blokovi > 0) {
    int broj_pomjeranja = (M - 1) % preostali_blokovi;
    for (int i = 0; i < broj_pomjeranja; i++) {
      prethodni = trenutni;
      trenutni++;

      if (trenutni == lista.end()) {
        prethodni = lista.before_begin();
        trenutni = lista.begin();
      }
    }

    rez.push_back(*trenutni);
    trenutni = lista.erase_after(prethodni);
    preostali_blokovi--;

    if (trenutni == lista.end()) {
      prethodni = lista.before_begin();
      trenutni = lista.begin();
    }
  }

  return rez;
}

int OdabirKoraka(int N, int K) {
  if (N <= 0 || K < 1 || K > N)
    throw std::domain_error("Broj blokova i redni broj bloka su pozitivni "
                            "cijeli brojevi i redni broj bloka ne moze biti "
                            "veci od broja blokova");
  if (N == 1)
    return 1;
  if (K == 1)
    return 0;

  for (int M = 1; M <= N * N; M++) {
    std::vector<int> rez = Razbrajanje(N, M);

    if (!rez.empty() && rez.at(rez.size() - 1) == K)
      return M;
  }
  return 0;
}

int main() {
  int N, K;

  std::cout << "Unesite broj blokova u gradu: ";
  std::cin >> N;
  std::cout << "Unesite redni broj bloka u kojem se nalazi sjediste stranke: ";
  std::cin >> K;

  try {
    int trazeni_korak = OdabirKoraka(N, K);
    std::cout << "Trazeni korak: " << trazeni_korak << std::endl;
  } catch (std::domain_error &e) {
    std::cout << e.what() << "\n";
  }

  return 0;
}
