#include "key_value_store.h"

KeyValueStore::KeyValueStore(size_t cache_size) : cache_size_(cache_size) {}

/**
 * @brief 插入指定的键值对
*/
void KeyValueStore::put(const std::string& key, const std::string& value) {
    store_[key] = value;
    update_cache(key, value);
}

/**
 * @brief 返回指定键对应的值
*/
auto KeyValueStore::read(const std::string& key) -> std::string {
    auto cache_iter = cache_.find(key);
    if (cache_iter != cache_.end()) {
        // 键存在
        // 使用LRU策略将被访问到的键放到链表头
        cache_list_.splice(cache_list_.begin(), cache_list_, cache_iter->second);
        return cache_iter->second->second;
    }
    
    auto store_iter = store_.find(key);
    if (store_iter != store_.end()) {
        update_cache(key, store_iter->second);
        return store_iter->second;
    }
    
    return "";
}

/**
 * @brief 维护链表
*/
void KeyValueStore::update_cache(const std::string& key, const std::string& value) {
    // 找到指定键
    auto cache_iter = cache_.find(key);
    if (cache_iter != cache_.end()) {
        // 键存在
        // 使用LRU策略将被访问到的键放到链表头
        cache_list_.splice(cache_list_.begin(), cache_list_, cache_iter->second);
        // 用新的值覆盖
        cache_iter->second->second = value;
    } else {
        if (cache_list_.size() == cache_size_) {
            // 缓存放不下
            cache_.erase(cache_list_.back().first);
            cache_list_.pop_back();
        }
        cache_list_.emplace_front(key, value);
        cache_[key] = cache_list_.begin();
    }
}