#include <iostream>

int main() {
  int v1_sati;
  int v1_minute;
  int v1_sekunde;
  std::cout << "Unesite prvo vrijeme (h min s): ";
  std::cin >> v1_sati >> v1_minute >> v1_sekunde;

  int v2_sati;
  int v2_minute;
  int v2_sekunde;
  std::cout << "Unesite drugo vrijeme (h min s): ";
  std::cin >> v2_sati >> v2_minute >> v2_sekunde;

  int v1_u_sekundama = v1_sati * 3600 + v1_minute * 60 + v1_sekunde;
  int v2_u_sekundama = v2_sati * 3600 + v2_minute * 60 + v2_sekunde;

  int razlika_trenutaka = v2_u_sekundama - v1_u_sekundama;

  int razlika_sati = razlika_trenutaka / 3600;
  int razlika_minute = (razlika_trenutaka % 3600) / 60;
  int razlika_sekunde = razlika_trenutaka % 60;
  std::cout << "Izmedju ova dva trenutka proteklo je " << razlika_sati << "h "
            << razlika_minute << "m " << razlika_sekunde << "s." << std::endl;

  return 0;
}