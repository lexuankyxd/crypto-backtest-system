#include "../../include/dataparser.hpp"
#include "../../include/datatypes.hpp"
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
// #include <iostream>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
#include <vector>

FILE *k, *tr, *at;
std::queue<KLine> data_frames;
std::mutex mtx;
std::atomic<bool> done = false;
std::atomic<bool> stop_reading = false;
namespace dataparser {
// super slow, will optimize later
std::vector<Trade> readTradesBetweenTime(int64_t first_id, int64_t last_id) {
  static std::queue<Trade> trade_buffer;
  std::vector<Trade> ts;
  while (!trade_buffer.empty()) {
    Trade &t = trade_buffer.front();
    if (t.id >= first_id && t.id <= last_id) {
      ts.push_back(t);
      trade_buffer.pop();
    } else {
      break;
    }
  }
  while (true) {
    Trade t = Trade();
    char maker[10], best_match[10];
    int res =
        fscanf(tr, "%ld,%lf,%lf,%lf,%ld,%s,%s", &t.id, &t.price, &t.quantity,
               &t.quote_quantity, &t.time, maker, best_match);
    if (res == EOF)
      break;
    t.maker = maker[0] == 'T', t.best_match = best_match[0] == 'T';
    if (t.id >= first_id && t.id <= last_id)
      ts.push_back(t);
    else {
      trade_buffer.push(t);
      break;
    }
  }
  return ts;
}

std::vector<AggTrade> readAggTradesBetweenTime(int64_t open_time,
                                               int64_t close_time) {
  static std::queue<AggTrade> agg_trades_buffer;
  std::vector<AggTrade> agg_trades;
  while (!agg_trades_buffer.empty()) {
    AggTrade &a = agg_trades_buffer.front();
    if (a.timestamp >= open_time && a.timestamp <= close_time) {
      agg_trades.push_back(a);
      agg_trades_buffer.pop();
    } else {
      break;
    }
  }
  while (true) {
    AggTrade a = AggTrade();
    char maker[10], best_match[10];
    int res = fscanf(at, "%ld,%lf,%lf,%ld,%ld,%ld,%s,%s", &a.id, &a.price,
                     &a.quantity, &a.first_id, &a.last_id, &a.timestamp, maker,
                     best_match);
    if (res == EOF)
      break;
    a.maker = maker[0] == 'T', a.best_match = best_match[0] == 'T';
    a.trades = readTradesBetweenTime(a.first_id, a.last_id);
    if (a.timestamp >= open_time && a.timestamp <= close_time)
      agg_trades.push_back(a);
    else {
      agg_trades_buffer.push(a);
      break;
    }
  }
  return agg_trades;
}

void readKLine() {
  while (!stop_reading) {
    KLine kl = KLine();
    int tmp;
    int res =
        fscanf(k, "%ld,%lf,%lf,%lf,%lf,%lf,%ld,%lf,%hd,%lf,%lf,%d",
               &kl.open_time, &kl.open, &kl.high, &kl.low, &kl.close,
               &kl.volume, &kl.close_time, &kl.quote_vol, &kl.number_of_trade,
               &kl.taker_base_vol, &kl.taker_quote_vol, &tmp);
    if (res == EOF)
      break;
    kl.agg_trades = readAggTradesBetweenTime(kl.open_time, kl.close_time);
    // std::lock_guard<std::mutex> lock(mtx);
    data_frames.push(kl);
    // std::cout << cnt << '\n';
    // if (cnt == 100 * 60)
    //   break;
    // std::cout << "\033[F\033[K";
    // printf("Data frames per sec: %lf, Agg trade per sec: %lf, Trades per sec:
    // "
    //        "%lf\n",
    //        (double)kl_cnt / ((double)(clock() - start) / CLOCKS_PER_SEC),
    //        (double)agg_trade_cnt / ((double)(clock() - start) /
    //        CLOCKS_PER_SEC), (double)trade_cnt / ((double)(clock() - start) /
    //        CLOCKS_PER_SEC));
    // if ((double)kl_cnt / ((double)(clock() - start) / CLOCKS_PER_SEC) < 50)
    //   break;
  }
  done = true;
  printf("Reading thread stopped\n");
}

void initParser(FILE *kl, FILE *t, FILE *a) {
  k = kl, tr = t, at = a;
  std::thread thr(readKLine);
  thr.detach();
}

std::optional<KLine> getNextKLine() {
  // static int index = 0;
  std::lock_guard<std::mutex> lock(mtx);
  if (data_frames.empty() || stop_reading)
    return std::optional<KLine>();
  auto tmp = data_frames.front();
  data_frames.pop();
  return tmp;
}

bool isDone() { return done; }
void stop_force() {
  stop_reading = true;
  printf("stop called\n");
}
} // namespace dataparser
