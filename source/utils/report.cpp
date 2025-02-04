#include "../../include/report.hpp"
#include "../../include/datatypes.hpp"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

std::ofstream tradesPlaced;
std::ofstream balanceTrack;
namespace reportgen {
void openFileStream(std::string alg_name, std::string data_name) {
  tradesPlaced =
      std::ofstream("report/trades-" + alg_name + "-" + data_name + ".csv");
  balanceTrack =
      std::ofstream("report/balance-" + alg_name + "-" + data_name + ".csv");
  printf("File stream opened\n");
}

void writeTrade(Signal s, double exit_price) {
  tradesPlaced << s.created_at << ',' << s.latest_exit_time << ',' << s.in_price
               << ',' << exit_price << ',' << s.amt << ',' << s.high_out << ','
               << s.low_out << '\n';
  // printf("%s\n", s.to_string().c_str());
}

void writeBalanceStatus(std::string t, double balance) {
  balanceTrack << t << ',' << balance << '\n';
}

void closeFileStream() {
  tradesPlaced.close();
  balanceTrack.close();
  printf("Report generated\n");
}
} // namespace reportgen
