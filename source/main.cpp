#include "../include/alpha.hpp"
#include "../include/configparser.hpp"
#include "../include/dataparser.hpp"
#include "../include/datatypes.hpp"
#include <bits/stdc++.h>
#include <cstdio>
#include <ctime>
#include <unistd.h>

using namespace std;
FILE *klines, *trades, *aggTrades;
int main(int argc, char *argv[]) {
  cin.tie(NULL);
  int mode = 0; // 0 = spot, 1
  BacktestDataConfiguration config = parseConfig();
  for (const auto &[type, path] : config.data_dir[0]) {
    // cout << type << ' ' << path << '\n';
    if (type == "kline")
      klines = fopen(path.c_str(), "r");
    else if (type == "aggTrade")
      aggTrades = fopen(path.c_str(), "r");
    else if (type == "trade")
      trades = fopen(path.c_str(), "r");
  }

  initParser(klines, trades, aggTrades);
  Alpha alpha = Alpha(0);
  vector<Signal> sigs;
  double base_vol = 0;
  int cnt = 0, idx = 0;
  while (1) {
    auto tmp = getNextKLine();
    if (!tmp.has_value()) {
      if (isDone())
        break;
      continue;
    }
    idx++;
    KLine kl = tmp.value();
    for (int i = 0; i < sigs.size(); i++) {
      if (sigs[i].high_out <= kl.close || sigs[i].low_out >= kl.close ||
          sigs[i].latest_exit_time <= kl.close_time) {
        alpha.bal += kl.close * sigs[i].amt;
        base_vol -= sigs[i].amt;
        sigs.erase(sigs.begin() + i);
      }
    }
    Signal sig = alpha.getSignal(kl);
    if (sig.latest_exit_time == -1) {
      cnt++;
    } else {
      base_vol += sig.amt;
      alpha.bal -= sig.amt * kl.close;
      sigs.push_back(sig);
    }
    if (config.live_print && (idx %= config.print_dist) == 0)
      printf("%ld: %lf %d\n", kl.close_time, alpha.bal + base_vol * kl.close,
             cnt);
  }
}
