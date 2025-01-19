#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

typedef struct {
  long long open_time, close_time;
  int n_trades;
  long double open, high, low, close, volume, quote_asset_volume,
      taker_buy_base_asset_vol, taker_buy_quote_asset_vol;
} KLine;

typedef struct {
  long long tradeId, time;
  long double price, qty, quoteQty;
  bool isBuyerMaker, isBestMatch;
} Trade;

typedef struct {
  long long aggTradeId, firstTradeId, lastTradeId, timestamp;
  long double price, qty;
  bool isBuyMaker, isBestMatch;
  vector<Trade> trades;
} AggTrades;

typedef struct DataFrame {
  KLine kl;
  vector<AggTrades *> aggTrade;
} DataFrame;

KLine *parseKLine(FILE *f) {
  KLine *kline = (KLine *)malloc(sizeof(KLine));
  fscanf(f, "%lld,%Lf,%Lf,%Lf,%Lf,%Lf,%lld,%Lf,%d,%Lf,%Lf", &kline->open_time,
         &kline->open, &kline->high, &kline->low, &kline->close, &kline->volume,
         &kline->close_time, &kline->quote_asset_volume, &kline->n_trades,
         &kline->taker_buy_base_asset_vol, &kline->taker_buy_quote_asset_vol);
  return kline;
}

AggTrades *parseAggTrade(FILE *f) {
  AggTrades *aggTrades = (AggTrades *)malloc(sizeof(AggTrades));
  fscanf(f, "")
}

void parseTrade(FILE *f, Trade *trade) {
  char s[200];
  fgets(s, 200, f);
}
// using the data format of binance historical data, so this just read and
// rewriting them in the designated data file that the system reads from.
int main(int argc, char *argv[]) {
  FILE *kl = fopen("./data/BTCUSDT-1s-2024-12-03.csv", "r");
  FILE *at = fopen("./data/BTCUSDT-aggTrages-2024-12-03.csv", "r");
  FILE *t = fopen("./data/BTCUSDT-trades-2024-12-03.csv", "r");
  long long st = 0, et = 0;
  vector<KLine *> kl_v = vector<KLine *>();
  while (!feof(kl)) {
    DataFrame *df = new DataFrame;
    kl_v.push_back(parseKLine(kl));
  }

  return 0;
}
