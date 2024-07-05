#ifndef KEY_VALUE_STORE_H
#define KEY_VALUE_STORE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

class KeyValueStore {
using KVPair = std::pair<std::string, std::string>;

public:
    KeyValueStore(size_t cache_size);
    void put(const std::string& key, const std::string& value);
    auto read(const std::string& key) -> std::string;

private:
    void update_cache(const std::string& key, const std::string& value);

    size_t cache_size_;
    std::unordered_map<std::string, std::string> store_;
    std::list<KVPair> cache_list_;
    std::unordered_map<std::string, std::list<KVPair>::iterator> cache_; // 某个键在链表中的位置
};

#endif // KEY_VALUE_STORE_H