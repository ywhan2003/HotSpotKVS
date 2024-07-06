#include "client_simulator.h"

ClientSimulator::ClientSimulator(RingManager& manager, int key_length, int value_length, double hotspot_ratio, size_t total_keys, size_t hotspot_keys)
        : ring_manager_(manager), key_length_(key_length), value_length_(value_length), hotspot_ratio_(hotspot_ratio) {
    generate_keys(hotspot_keys, hotspot_keys_set_);
    generate_keys(total_keys - hotspot_keys, regular_keys_set_);
}

/**
 * @brief 运行算法
*/
auto ClientSimulator::run(int duration_seconds) -> std::vector<int> {
    // 存储每一分钟的负载量
    std::vector<int> load_count_per_minute;
    // 记录初始时间
    auto start_time = std::chrono::steady_clock::now();
    // 计算整个操作的终止时间
    auto end_time = start_time + std::chrono::seconds(duration_seconds);

    // 每一分钟为一个循环
    for (int minute = 0; minute < duration_seconds / 60; ++minute) {
        int load_count = 0;
        // 计算这一分钟的终止时间
        auto minute_end_time = start_time + std::chrono::minutes(minute + 1);
        // 在终止时间之前保持循环
        while (std::chrono::steady_clock::now() < minute_end_time && std::chrono::steady_clock::now() < end_time) {
            std::string key1 = get_key();
            std::string key2 = get_key();
            std::string value = generate_random_string(value_length_);

            ring_manager_.put(key1, value);
            ring_manager_.read(key2);
            ++load_count;
        }

        load_count_per_minute.push_back(load_count);
    }

    return load_count_per_minute;
}

/**
 * @brief 生成测试中所有会使用到的键
*/
void ClientSimulator::generate_keys(size_t num_keys, std::vector<std::string>& key_set) {
    for (size_t i = 0; i < num_keys; ++i) {
        key_set.push_back(generate_random_string(key_length_));
    }
}

/**
 * @brief 从所有键中随机挑一个键
*/
auto ClientSimulator::get_key() -> std::string {
    if (hotspot_ratio_ > 0.99 || distribution_(generator_) < HOTRATIO) {
        // 全部都是热键或随机数小于给定的值
        // 此处定义热键的概率为0.9
        return hotspot_keys_set_[distribution_(generator_) * hotspot_keys_set_.size()];
    } else {
        return regular_keys_set_[distribution_(generator_) * regular_keys_set_.size()];
    }
}

/**
 * 随机生成字符串
*/
auto ClientSimulator::generate_random_string(size_t length) -> std::string {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result;
    result.resize(length);

    std::uniform_int_distribution<int> char_distribution(0, sizeof(charset) - 2); // 最后一个字符是'\0'

    for (size_t i = 0; i < length; ++i) {
        result[i] = charset[char_distribution(generator_)];
    }

    return result;
}