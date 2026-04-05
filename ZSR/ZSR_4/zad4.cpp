#include <cmath>
#include <iostream>
const double RAD = 180 / (4 * std::atan(1.0));
void Pretvorba(double ugao, double &stepeni) { stepeni = ugao * RAD; }
void Pretvorba(double ugao, int &stepeni, int &minute, int &sekunde) {
  double ukupno = ugao * RAD;
  stepeni = int(ukupno);
  double ostatak = (ukupno - stepeni) * 60;
  minute = int(ostatak);
  sekunde = int((ostatak - minute) * 60);
}
int main() {
  double s;
  Pretvorba(1.326, s);

  std::cout << "Pretvaranje iz radijana u sekunde iznosi: " << s << "\n";

  int x, y, z;
  Pretvorba(1.326, x, y, z);
  std::cout << "Pretvaranje iz radijana u stepene, minute i sekunde iznosi: "
            << x << " " << y << " " << z << "\n";
  return 0;
}