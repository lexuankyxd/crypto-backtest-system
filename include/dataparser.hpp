#include "datatypes.hpp"
#include <cstdint>
#include <cstdio>
#include <optional>

void initParser(FILE *, FILE *, FILE *);
std::optional<KLine> getNextKLine();
std::optional<std::vector<KLine>> getKLineInRange(int64_t, int64_t);
bool isDone();
void stop_force();
