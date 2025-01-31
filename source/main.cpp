#include "../include/alpha.hpp"
#include "../include/configparser.hpp"
#include "../include/dataparser.hpp"
#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <unistd.h>

using namespace std;
FILE *klines, *trades, *aggTrades;
int main(int argc, char *argv[]) {
  char buffer[PATH_MAX];
  if (getcwd(buffer, sizeof(buffer)) != NULL) {
    std::cout << "Current working directory: " << buffer << std::endl;
  } else {
    std::cerr << "Error getting current working directory" << std::endl;
  }
  cin.tie(NULL);
  // int mode = 0; // 0 = spot, 1
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
  getchar();
  // openFileStream(config.strat_name, "BTCUSDT-1s-03-12-2024");
  // Alpha alpha = Alpha(10000);
  // vector<Signal> sigs;
  // double base_vol = 0;
  // int cnt = 0, idx = 0;
  // while (1) {
  //   auto tmp = getNextKLine();
  //   if (!tmp.has_value()) {
  //     if (isDone())
  //       break;
  //     continue;
  //   }
  //   idx++;
  //   KLine kl = tmp.value();
  //   for (int i = 0; i < sigs.size(); i++) {
  //     if (sigs[i].high_out <= kl.close || sigs[i].low_out >= kl.close ||
  //         sigs[i].latest_exit_time <= kl.close_time) {
  //       alpha.bal += kl.close * sigs[i].amt;
  //       base_vol -= sigs[i].amt;
  //       sigs[i].latest_exit_time = kl.close_time;
  //       if (config.gen_report) {
  //         writeTrade(sigs[i], kl.close);
  //       }
  //       sigs.erase(sigs.begin() + i);
  //       i--;
  //     }
  //   }
  //   Signal sig = alpha.getSignal(kl);
  //   if (sig.latest_exit_time != -1) {
  //     base_vol += sig.amt;
  //     alpha.bal -= sig.amt * kl.close;
  //     // if (alpha.bal <= 0) {
  //     //   printf("%lf\n", alpha.bal);
  //     //   printf("Game over!\n");
  //     //   stop_force();
  //     // }
  //     sigs.push_back(sig);
  //   }
  //   char buffer[26];
  //   int64_t t = (int)round((double)kl.close_time / 1000);
  //   strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", localtime(&t));
  //   if (config.gen_report)
  //     writeBalanceStatus(buffer, alpha.bal);
  //   if (config.live_print && (idx %= config.print_dist) == 0) {
  //     // cout << kl.close_time << '\n';
  //     printf("%s | Ballance:  %lf\n", buffer, alpha.bal + base_vol *
  //     kl.close);
  //   }
  // }
  // closeFileStream();
}
