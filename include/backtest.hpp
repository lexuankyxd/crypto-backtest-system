#ifndef BACKTESTCLIENT_H
#define BACKTESTCLIENT_H
#include "client.hpp"
class BackTestClient : Client {
public:
  BackTestClient(std::string conf) : Client(conf) {}
};
#endif
