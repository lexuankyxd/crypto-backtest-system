#include "dataparser.hpp"
#include "datatypes.hpp"

class Alpha {
public:
  double bal;
  explicit Alpha(double);
  Signal getSignal(KLine);
};
