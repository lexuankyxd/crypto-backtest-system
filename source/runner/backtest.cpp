
void initBacktest() {}

void run() {
  // int mode = 0; // 0 = spot, 1
  BacktestDataConfiguration config = configparser::parseConfig();
  FILE *klines, *trades, *aggTrades;
  for (const auto &[type, path] : config.data_dir[0]) {
    // cout << type << ' ' << path << '\n';
    if (type == "kline")
      klines = fopen(path.c_str(), "r");
    else if (type == "aggTrade")
      aggTrades = fopen(path.c_str(), "r");
    else if (type == "trade")
      trades = fopen(path.c_str(), "r");
  }

  dataparser::initParser(klines, trades, aggTrades);
  reportgen::openFileStream(config.strat_name, "BTCUSDT-1s-03-12-2024");

  Alpha alpha = Alpha(10000);
  vector<Signal> sigs;
  double base_vol = 0;
  int idx = 0;
  while (1) {
    auto tmp = dataparser::getNextKLine();
    if (!tmp.has_value()) {
      if (dataparser::isDone())
        break;
      continue;
    }
    idx++;
    KLine kl = tmp.value();
    for (size_t i = 0; i < sigs.size(); i++) {
      if (sigs[i].high_out <= kl.close || sigs[i].low_out >= kl.close ||
          sigs[i].latest_exit_time <= kl.close_time) {
        alpha.bal += kl.close * sigs[i].amt;
        base_vol -= sigs[i].amt;
        sigs[i].latest_exit_time = kl.close_time;
        if (config.gen_report) {
          reportgen::writeTrade(sigs[i], kl.close);
        }
        sigs.erase(sigs.begin() + i);
        i--;
      }
    }
    Signal sig = alpha.getSignal(kl);
    if (sig.latest_exit_time != -1) {
      base_vol += sig.amt;
      alpha.bal -= sig.amt * kl.close;
      // if (alpha.bal <= 0) {
      //   printf("%lf\n", alpha.bal);
      //   printf("Game over!\n");
      //   stop_force();
      // }
      sigs.push_back(sig);
    }
    string t = convert2Time((kl.close_time + 999) / 1000);
    if (config.gen_report)
      reportgen::writeBalanceStatus(t, alpha.bal);
    if (config.live_print && (idx %= config.print_dist) == 0) {
      // cout << kl.close_time << '\n';
      printf("%s | Ballance:  %lf\n", t.c_str(),
             alpha.bal + base_vol * kl.close);
    }
  }
  reportgen::closeFileStream();
}
