#include <queue>
#include <stdexcept>

typedef struct SMA {
  int d;
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
