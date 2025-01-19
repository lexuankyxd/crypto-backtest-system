#include "../../include/dataparser.hpp"
#include "../../include/datatypes.hpp"
#include <atomic>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <mutex>
#include <optional>
#include <thread>
#include <vector>

FILE *k, *tr, *at;
std::vector<KLine> data_frames;
std::mutex mtx;
std::atomic<bool> done = false;
// super slow, will optimize later
std::vector<Trade> readTradesBetweenTime(int64_t first_id, int64_t last_id) {
  static std::vector<Trade> trade_buffer;
  std::vector<Trade> ts;
  for (Trade t : trade_buffer)
    if (t.id >= first_id && t.id <= last_id)
      ts.push_back(t);
  while (!feof(tr)) {
    Trade t = Trade();
    char maker[10], best_match[10];
    fscanf(tr, "%ld,%lf,%lf,%lf,%ld,%s,%s", &t.id, &t.price, &t.quantity,
           &t.quote_quantity, &t.time, maker, best_match);
    t.maker = maker[0] == 'T', t.best_match = best_match[0] == 'T';
    if (t.id >= first_id && t.id <= last_id)
      ts.push_back(t);
    else {
      trade_buffer.push_back(t);
      break;
    }
  }
  return ts;
}

std::vector<AggTrade> readAggTradesBetweenTime(int64_t open_time,
                                               int64_t close_time) {
  static std::vector<AggTrade> agg_trades_buffer;
  std::vector<AggTrade> agg_trades;
  for (AggTrade a : agg_trades_buffer)
    if (a.timestamp >= open_time && a.timestamp <= close_time)
      agg_trades.push_back(a);
  while (!feof(at)) {
    AggTrade a = AggTrade();
    char maker[10], best_match[10];
    fscanf(at, "%ld,%lf,%lf,%ld,%ld,%ld,%s,%s", &a.id, &a.price, &a.quantity,
           &a.first_id, &a.last_id, &a.timestamp, maker, best_match);
    a.maker = maker[0] == 'T', a.best_match = best_match[0] == 'T';
    a.trades = readTradesBetweenTime(a.first_id, a.last_id);
    if (a.timestamp >= open_time && a.timestamp <= close_time)
      agg_trades.push_back(a);
    else {
      agg_trades_buffer.push_back(a);
      break;
    }
  }
  return agg_trades;
}

void readKLine() {
  int cnt = 0;
  while (!feof(k)) {
    KLine kl = KLine();
    int tmp;
    fscanf(k, "%ld,%lf,%lf,%lf,%lf,%lf,%ld,%lf,%hd,%lf,%lf,%d", &kl.open_time,
           &kl.open, &kl.high, &kl.low, &kl.close, &kl.volume, &kl.close_time,
           &kl.quote_vol, &kl.number_of_trade, &kl.taker_base_vol,
           &kl.taker_quote_vol, &tmp);
    kl.agg_trades = readAggTradesBetweenTime(kl.open_time, kl.close_time);
    std::lock_guard<std::mutex> lock(mtx);
    data_frames.push_back(kl);
    // if (data_frames.size() == 1)
    //   break;
  }
  done = true;
}

void initParser(FILE *kl, FILE *t, FILE *a) {
  k = kl, tr = t, at = a;
  std::thread thr(readKLine);
  thr.detach();
}

std::optional<KLine> getNextKLine() {
  static int index = 0;
  std::lock_guard<std::mutex> lock(mtx);
  if (index < data_frames.size())
    return data_frames[index++];
  return std::optional<KLine>();
}

std::optional<std::vector<KLine>> getKLineInRange(int64_t open_time,
                                                  int64_t close_time) {
  // std::lock_guard<std::mutex> lock(mtx);
  // auto start = std::lower_bound(
  //     data_frames.begin(), data_frames.end(), open_time,
  //     [open_time](KLine t) { return t.open_time < open_time; });
  // auto end = std::upper_bound(
  //                data_frames.begin(), data_frames.end(), close_time,
  //                [close_time](KLine t) { return t.close_time < close_time; })
  //                -
  //            1;
  // if (start != data_frames.end())
  //   return std::vector<KLine>(start, end);
  return std::optional<std::vector<KLine>>();
}

bool isDone() { return done; }
