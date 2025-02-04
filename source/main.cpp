#include "alpha.hpp"
#include "backtest.hpp"
#include "configparser.hpp"
#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <string>
#include <unistd.h>

using std::cout, std::vector, std::cerr, std::string;

string convert2Time(int64_t t) {
  char buffer[26];
  strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", localtime(&t));
  return buffer;
}

int main(int argc, char *argv[]) {
  nlohmann::json config = nlohmann::json::parse(std::ifstream("config.json"));
  switch (config["mode_config"]["mode"].template get<std::string>()[0]) {
  case 'b':
    cout << "backtesting\n";
    backtest::init();
    break;
  case 'l':
    break;
  case 'p':
    break;
  }
}
