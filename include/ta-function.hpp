#ifndef TA_FUNCTION_H
#define TA_FUNCTION_H
#include <queue>
namespace tafunctions {
typedef struct SMA {
  long unsigned int d;
  std::queue<double> vals;
  double sum = 0;
  // SMA(int days) {if(days <= 0) throw std::invalid_argument("days must be
  // greater than 0"); }; // is this really needed?
  SMA(int days) : d(days){};
  void push(double v) {
    sum += v;
    vals.push(v);
    if (vals.size() > d) {
      sum -= vals.front();
      vals.pop();
    }
  };
  double getVal() { return sum / d; }
} SMA;
} // namespace tafunctions
#endif
