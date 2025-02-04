#ifndef REPORTGEN_H
#define REPORTGEN_H
#include "datatypes.hpp"
#include <string>
namespace reportgen {
void openFileStream(std::string, std::string);
void closeFileStream();
void writeTrade(Signal, double);
void writeBalanceStatus(std::string, double);
} // namespace reportgen
#endif
