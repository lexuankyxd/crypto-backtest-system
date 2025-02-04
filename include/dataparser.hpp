#ifndef DATAPARSER_H
#define DATAPARSER_H
#include "datatypes.hpp"
#include <cstdio>
#include <optional>
namespace dataparser {
void initParser(FILE *, FILE *, FILE *);
std::optional<KLine> getNextKLine();
bool isDone();
void stop_force();
} // namespace dataparser
#endif
