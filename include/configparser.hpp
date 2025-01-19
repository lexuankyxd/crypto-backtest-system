#include <sstream>
#include <string>
#include <utility>
#include <vector>

typedef struct BacktestDataConfiguration {
public:
  std::vector<std::vector<std::pair<std::string, std::string>>> data_dir;
  std::string strat_name;
  bool gen_report;
  bool live_print;
  int print_dist;
  std::string to_string() {
    std::ostringstream oss; // Use ostringstream for easy string concatenation
    // Add strat_name
    oss << "Strategy Name: " << strat_name << "\n";
    // Add gen_report
    oss << "Generate Report: " << (gen_report ? "true" : "false") << "\n";
    // Add live_print
    oss << "Live Print: " << (live_print ? "true" : "false") << "\n";
    // Add print_dist
    oss << "Print Distance: " << print_dist << "\n";
    // Add data_dir
    oss << "Data Directory:\n";
    for (const auto &vec : data_dir) {
      for (const auto &pair : vec) {
        oss << "  - " << pair.first << ": " << pair.second << "\n";
      }
    }

    return oss.str(); // Return the complete string
  }
} BacktestDataConfiguration;

BacktestDataConfiguration parseConfig();
