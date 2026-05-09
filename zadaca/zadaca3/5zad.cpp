// TP 2025/2026: Zadaća 3, Task 5
#include <iostream>
#include <stdexcept>
#include <vector>

struct Blok {
  int redni_broj;
  Blok *sljedeci;
};

// N - broj blokova (od 1 do N)
// M -  korak razbrajanja
std::vector<int> Razbrajanje(int N, int M) {
  std::vector<int> rez;
  if (N <= 0 || M <= 0)
    return rez;
  rez.reserve(N);

  Blok *pocetak = nullptr;
  Blok *prethodni = nullptr;
  for (int i = 1; i <= N; i++) {
    Blok *novi = new Blok{i, nullptr};
    if (pocetak == nullptr)
      pocetak = novi;
    else
      prethodni->sljedeci = novi;
    prethodni = novi;
  }
  prethodni->sljedeci = pocetak;

  Blok *p = pocetak;
  Blok *p1 = prethodni;
  int preostali_blokovi = N;

  while (preostali_blokovi > 0) {
    int broj_pomjeranja =
        preostali_blokovi == N ? 0 : (M - 1) % preostali_blokovi;
    for (int i = 0; i < broj_pomjeranja; i++) {
      p1 = p;
      p = p->sljedeci;
    }

    rez.push_back(p->redni_broj);
    if (preostali_blokovi == 1) {
      delete p;
      break;
    }

    p1->sljedeci = p->sljedeci;
    Blok *za_brisanje = p;
    p = p->sljedeci;
    delete za_brisanje;
    preostali_blokovi--;
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
    std::cout << e.what() << std::endl;
  }

  return 0;
}
