#ifndef DATATYPES_H
#define DATATYPES_H

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

typedef struct Trade {
  int64_t id, time;
  double price, quantity, quote_quantity;
  bool maker, best_match;

  std::string to_string() const {
    std::ostringstream oss;
    oss << "{ id: " << id << ", time: " << time << ", price: " << price
        << ", quantity: " << quantity << ", quote_quantity: " << quote_quantity
        << ", maker: " << std::boolalpha << maker
        << ", best_match: " << std::boolalpha << best_match << "}";
    return oss.str();
  }
} Trade;

typedef struct AggTrade {
  int64_t id, first_id, last_id, timestamp;
  double price, quantity;
  bool maker, best_match;
  std::vector<Trade> trades;

  std::string to_string() const {
    std::ostringstream oss;
    oss << "{ id: " << id << ", first_id: " << first_id
        << ", last_id: " << last_id << ", timestamp: " << timestamp
        << ", price: " << price << ", quantity: " << quantity
        << ", maker: " << std::boolalpha << maker
        << ", best_match: " << std::boolalpha << best_match
        << ", trades: " << trades.size();

    oss << "}";
    return oss.str();
  }
} AggTrade;

typedef struct KLine {
  int64_t open_time, close_time;
  double open, high, low, close, volume, quote_vol, taker_base_vol,
      taker_quote_vol;
  short number_of_trade;
  std::vector<AggTrade> agg_trades;

  std::string to_string() const {
    std::ostringstream oss;
    oss << "{ open_time: " << open_time << ", close_time: " << close_time
        << ", open: " << open << ", high: " << high << ", low: " << low
        << ", close: " << close << ", volume: " << volume
        << ", quote_vol: " << quote_vol
        << ", taker_base_vol: " << taker_base_vol
        << ", taker_quote_vol: " << taker_quote_vol
        << ", number_of_trade: " << number_of_trade
        << ", agg_trades: " << agg_trades.size();
    oss << "}";
    return oss.str();
  }
} KLine;

typedef struct Signal {
  int64_t latest_exit_time;
  double high_out, low_out, amt; // high and low will be in base -> quote ratio,
                                 // amt is the amount of base asset bought

  std::string to_string() const {
    std::ostringstream oss;
    oss << "{ latest_exit_time: " << latest_exit_time
        << ", high_out: " << high_out << ", low_out: " << low_out << "}";
    return oss.str();
  }
} Signal;

#endif
