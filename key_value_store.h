#ifndef KEY_VALUE_STORE_H
#define KEY_VALUE_STORE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

class KeyValueStore {
public:
    KeyValueStore(size_t cache_size);
    void put(const std::string& key, const std::string& value);
    auto read(const std::string& key) -> std::string;

private:
    void update_cache(const std::string& key, const std::string& value);

    size_t cache_size;
    std::unordered_map<std::string, std::string> store;
    std::list<std::pair<std::string, std::string>> cache_list;
    std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>::iterator> cache;
};

#endif // KEY_VALUE_STORE_H