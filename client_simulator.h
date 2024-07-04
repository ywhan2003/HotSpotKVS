#ifndef CLIENT_SIMULATOR_H
#define CLIENT_SIMULATOR_H

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include "key_value_store.h"

class ClientSimulator {
public:
    ClientSimulator(KeyValueStore& kv_store, double hotspot_ratio, size_t total_keys, size_t hotspot_keys);
    auto run(int duration_seconds) -> std::vector<int>;

private:
    void generate_keys(size_t num_keys, std::vector<std::string>& key_set);
    auto get_key() -> std::string;
    auto generate_random_string(size_t length) -> std::string;

    KeyValueStore& kv_store;
    double hotspot_ratio;
    std::vector<std::string> hotspot_keys_set;
    std::vector<std::string> regular_keys_set;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution{0.0, 1.0};
};

#endif // CLIENT_SIMULATOR_H