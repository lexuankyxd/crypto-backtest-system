#include "../../include/configparser.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <utility>
// always search for config.json file at project root.
using json = nlohmann::json;
namespace configparser {
BacktestDataConfiguration parseConfig() {
  std::ifstream f("config.json");

  BacktestDataConfiguration config;
  json data = json::parse(f);
  config.print_dist = data["print_dist"];
  config.live_print = data["live_print"];
  config.gen_report = data["gen_report"];
  config.strat_name = data["strat_name"];
  for (auto a : data["data"]) {
    config.data_dir.push_back(
        std::vector<std::pair<std::string, std::string>>());
    for (auto b : a) {
      config.data_dir[0].push_back(std::make_pair(b["type"], b["dir"]));
    }
  }
  return config;
}
} // namespace configparser
