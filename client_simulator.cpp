#include "client_simulator.h"

ClientSimulator::ClientSimulator(KeyValueStore& kv_store, double hotspot_ratio, size_t total_keys, size_t hotspot_keys)
    : kv_store(kv_store), hotspot_ratio(hotspot_ratio) {
    generate_keys(hotspot_keys, hotspot_keys_set);
    generate_keys(total_keys - hotspot_keys, regular_keys_set);
}

auto ClientSimulator::run(int duration_seconds) -> std::vector<int> {
    std::vector<int> load_count_per_minute;
    auto start_time = std::chrono::steady_clock::now();
    auto end_time = start_time + std::chrono::seconds(duration_seconds);

    for (int minute = 0; minute < duration_seconds / 60; ++minute) {
        int load_count = 0;
        auto minute_end_time = start_time + std::chrono::minutes(minute + 1);

        while (std::chrono::steady_clock::now() < minute_end_time && std::chrono::steady_clock::now() < end_time) {
            std::string key1 = get_key();
            std::string key2 = get_key();
            std::string value = generate_random_string(16);

            kv_store.put(key1, value);
            kv_store.read(key2);
            ++load_count;
        }

        load_count_per_minute.push_back(load_count);
    }

    return load_count_per_minute;
}

void ClientSimulator::generate_keys(size_t num_keys, std::vector<std::string>& key_set) {
    for (size_t i = 0; i < num_keys; ++i) {
        key_set.push_back(generate_random_string(8));
    }
}

auto ClientSimulator::get_key() -> std::string {
    if (distribution(generator) < hotspot_ratio) {
        return hotspot_keys_set[distribution(generator) * hotspot_keys_set.size()];
    } else {
        return regular_keys_set[distribution(generator) * regular_keys_set.size()];
    }
}

auto ClientSimulator::generate_random_string(size_t length) -> std::string {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result;
    result.resize(length);

    std::uniform_int_distribution<int> char_distribution(0, sizeof(charset) - 2); // 最后一个字符是'\0'

    for (size_t i = 0; i < length; ++i) {
        result[i] = charset[char_distribution(generator)];
    }

    return result;
}