#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double recv_from_adc() { return 3.3 * (double)rand() / RAND_MAX; }

int main() {
  /*
   *         5 * R_therm
   * V = -----------------
   *     R_therm + R_sense
   *
   *      R_sense * V
   * R = -------------
   *        5 - V
   * */
  srand(time(NULL));
  srand(rand());
  double voltage = recv_from_adc();
  double resistance = (10 * voltage) / (5 - voltage);
  printf(" V = %f V\n R = %f k.ohm\n", voltage, resistance);

  return 0;
}
