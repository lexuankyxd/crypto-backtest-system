#include "alpha.hpp"
#include "ta-function.hpp"
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

SMA sma50 = SMA(50), sma200 = SMA(200);
int cnt = 0;
Alpha::Alpha(double bal) : bal(bal) {}

Signal Alpha::getSignal(const KLine kl) {
  Signal s = Signal();
  cnt++;
  sma50.push(kl.close);
  sma200.push(kl.close);
  // printf("sma50: %10lf| sma200: %10lf\n", sma50.getVal(), sma200.getVal());
  if (cnt < 200 || sma50.getVal() < sma200.getVal()) {
    s.latest_exit_time = -1;
    return s;
  }
  s.low_out = kl.close * 0.95;
  s.high_out = sma50.getVal() / sma200.getVal() * kl.close;
  s.amt = 1 / kl.close * 100;
  s.created_at = kl.close_time;
  s.in_price = kl.close;
  s.latest_exit_time = kl.close_time + 1000 * 60 * 5;
  return s;
}
