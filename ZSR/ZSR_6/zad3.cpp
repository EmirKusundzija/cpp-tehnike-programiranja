#include <iostream>
#include <stdexcept>

template <typename TipElemenata>
TipElemenata *KreirajNiz(int n, TipElemenata default_vrijednost) {
  TipElemenata *niz = nullptr;
  try {
    niz = new TipElemenata[n];
    for (int i = 0; i < n; i++) {
      niz[i] = default_vrijednost;
    }
  } catch (...) {
    throw std::runtime_error("Kreiranje nije uspijelo.");
  }
  return niz;
}

int main() {

  try {
    auto a = KreirajNiz(30, 3);
    for (int i = 0; i < 30; i++) {
      std::cout << a[i] << " ";
    }
    delete[] a;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}