#include <algorithm>
#include <iostream>
#include <vector>
class KutijaApstraktna {
  double tezina_kutije;

public:
  KutijaApstraktna(double tezina) : tezina_kutije(tezina) {}
  double DajTezinu() const { return tezina_kutije; }
  virtual double DajUkupnuTezinu() const = 0;
  virtual ~KutijaApstraktna() = default;
};

class KutijaObicna : public KutijaApstraktna {
  double tezina_sadrzaja;

public:
  KutijaObicna(double tezina_kutije, double tezina_sadrzaja)
      : KutijaApstraktna(tezina_kutije), tezina_sadrzaja(tezina_sadrzaja) {}

  double DajUkupnuTezinu() const { return tezina_sadrzaja + DajTezinu(); }
};

class KutijaSaPregradama : public KutijaApstraktna {
  std::vector<double> tezine;

public:
  KutijaSaPregradama(double tezina_kutije, const std::vector<double> &tezine)
      : KutijaApstraktna(tezina_kutije), tezine(tezine) {}
  double DajUkupnuTezinu() const {

    double suma = 0;
    std::for_each(tezine.begin(), tezine.end(),
                  [&suma](double tezina_predmeta) { suma += tezina_predmeta; });
    return suma + DajTezinu();
  }
};

int main() {

  std::vector<KutijaApstraktna *> kutije;

  kutije.emplace_back(new KutijaSaPregradama(7, {1, 2, 3}));
  kutije.emplace_back(new KutijaObicna(10, 2));
  kutije.emplace_back(new KutijaSaPregradama(56.4, {1, 2, 3}));

  std::sort(kutije.begin(), kutije.end(),
            [](const KutijaApstraktna *a, const KutijaApstraktna *b) {
              return a->DajUkupnuTezinu() < b->DajUkupnuTezinu();
            });

  for (auto *kutija : kutije) {
    std::cout << kutija->DajUkupnuTezinu() << "\n";
  }
  return 0;
}