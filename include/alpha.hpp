// #ifdef ALPHA_H
// #define ALPHA_H
#include "datatypes.hpp"

class Alpha {
public:
  double bal;
  double locked_bal;
  explicit Alpha(double);
  Signal getSignal(KLine);
};
// #endif
