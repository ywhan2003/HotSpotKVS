#ifndef KEY_VALUE_STORE_H
#define KEY_VALUE_STORE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

/**
 * @brief KVS存储系统
*/
class KeyValueStore {
using KVPair = std::pair<std::string, std::string>;

public:
    KeyValueStore(size_t cache_size, size_t k);
    void put(const std::string& key, const std::string& value);
    auto read(const std::string& key) -> std::string;

private:
    void update_cache(const std::string& key, const std::string& value);
    void record_access(const std::string& key);
    void move_to_hot(const std::string& key, const std::string& value);

    size_t cache_size_;
    size_t k_;
    std::unordered_map<std::string, std::string> store_;
    std::list<KVPair> cold_list_;  // 不超过k次访问的链表
    std::list<KVPair> hot_list_;   // 超过k次访问的链表
    std::unordered_map<std::string, std::list<KVPair>::iterator> cold_cache_;
    std::unordered_map<std::string, std::list<KVPair>::iterator> hot_cache_;
    std::unordered_map<std::string, int> access_count_;  // 记录访问次数
};

#endif // KEY_VALUE_STORE_H