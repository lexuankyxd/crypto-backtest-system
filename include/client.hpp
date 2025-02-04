#ifndef CLIENT_H
#define CLIENT_H
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
class Client {
  nlohmann::json config;

public:
  Client(std::string conf)
      : config(nlohmann::json::parse(std::ifstream(conf))) {}
  void run();
};
#endif
