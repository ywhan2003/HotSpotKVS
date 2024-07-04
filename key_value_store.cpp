#include "key_value_store.h"

KeyValueStore::KeyValueStore(size_t cache_size) : cache_size(cache_size) {}

void KeyValueStore::put(const std::string& key, const std::string& value) {
    store[key] = value;
    update_cache(key, value);
}

auto KeyValueStore::read(const std::string& key) -> std::string {
    auto cache_iter = cache.find(key);
    if (cache_iter != cache.end()) {
        cache_list.splice(cache_list.begin(), cache_list, cache_iter->second);
        return cache_iter->second->second;
    }
    
    auto store_iter = store.find(key);
    if (store_iter != store.end()) {
        update_cache(key, store_iter->second);
        return store_iter->second;
    }
    
    return "";
}

void KeyValueStore::update_cache(const std::string& key, const std::string& value) {
    auto cache_iter = cache.find(key);
    if (cache_iter != cache.end()) {
        cache_list.splice(cache_list.begin(), cache_list, cache_iter->second);
        cache_iter->second->second = value;
    } else {
        if (cache_list.size() == cache_size) {
            cache.erase(cache_list.back().first);
            cache_list.pop_back();
        }
        cache_list.emplace_front(key, value);
        cache[key] = cache_list.begin();
    }
}