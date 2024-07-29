#ifndef CLIENT_SIMULATOR_H
#define CLIENT_SIMULATOR_H

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include "key_value_store.h"

// 取到热键的概率
#define HOTRATIO 0.9

/**
 * @brief 客户端模拟器
*/
class ClientSimulator {
public:
    ClientSimulator(KeyValueStore& kv_store, int key_length, int value_length, double hotspot_ratio, size_t total_keys, size_t hotspot_keys);
    auto run(int duration_seconds) -> std::vector<int>;

private:
    void generate_keys(size_t num_keys, std::vector<std::string>& key_set);
    auto get_key() -> std::string;
    auto generate_random_string(size_t length) -> std::string;

    int key_length_;
    int value_length_;
    KeyValueStore& kv_store_;
    double hotspot_ratio_;
    std::vector<std::string> hotspot_keys_set_;
    std::vector<std::string> regular_keys_set_;
    std::default_random_engine generator_;
    std::uniform_real_distribution<double> distribution_{0.0, 1.0};
};

#endif // CLIENT_SIMULATOR_H