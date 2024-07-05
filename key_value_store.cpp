#include "key_value_store.h"

KeyValueStore::KeyValueStore(size_t cache_size, size_t k) : cache_size_(cache_size), k_(k) {}

/**
 * @brief 插入指定的键值对
*/
void KeyValueStore::put(const std::string& key, const std::string& value) {
    store_[key] = value;
    record_access(key);
    update_cache(key, value);
}

/**
 * @brief 返回指定键对应的值
*/
auto KeyValueStore::read(const std::string& key) -> std::string {
    auto hot_cache_iter = hot_cache_.find(key);
    if (hot_cache_iter != hot_cache_.end()) {
        record_access(key);
        // 使用LRU策略将被访问到的键放到链表头
        hot_list_.splice(hot_list_.begin(), hot_list_, hot_cache_iter->second);
        return hot_cache_iter->second->second;
    }

    auto cold_cache_iter = cold_cache_.find(key);
    if (cold_cache_iter != cold_cache_.end()) {
        record_access(key);
        // 使用LRU策略将被访问到的键放到链表头
        cold_list_.splice(cold_list_.begin(), cold_list_, cold_cache_iter->second);
        if (access_count_[key] >= k_) {
            move_to_hot(key, cold_cache_iter->second->second);
        }
        return cold_cache_iter->second->second;
    }
    
    auto store_iter = store_.find(key);
    if (store_iter != store_.end()) {
        record_access(key);
        update_cache(key, store_iter->second);
        return store_iter->second;
    }
    
    return "";
}

/**
 * @brief 维护链表
*/
void KeyValueStore::update_cache(const std::string& key, const std::string& value) {
    // 先检查是否在cold cache中
    auto cold_cache_iter = cold_cache_.find(key);
    if (cold_cache_iter != cold_cache_.end()) {
        // 将键放到表头
        cold_list_.splice(cold_list_.begin(), cold_list_, cold_cache_iter->second);
        cold_cache_iter->second->second = value;
        if (access_count_[key] >= k_) {
            move_to_hot(key, value);
        }
        return;
    }
    
    // 再检查是否在hot cache中
    auto hot_cache_iter = hot_cache_.find(key);
    if (hot_cache_iter != hot_cache_.end()) {
        // 将键放到表头
        hot_list_.splice(hot_list_.begin(), hot_list_, hot_cache_iter->second);
        hot_cache_iter->second->second = value;
        return;
    }

    // 新的key，先放到cold cache
    if (cold_list_.size() + hot_list_.size() == cache_size_) {
        // 先淘汰
        if (cold_list_.size() > 0) {
            auto last = cold_list_.end();
            last--;
            cold_cache_.erase(last->first);
            cold_list_.pop_back();
        } else {
            auto last = hot_list_.end();
            last--;
            hot_cache_.erase(last->first);
            hot_list_.pop_back();
        }
    }
    cold_list_.emplace_front(key, value);
    cold_cache_[key] = cold_list_.begin();
    if (access_count_[key] >= k_) {
        move_to_hot(key, value);
    }
}

/**
 * @brief 记录键的访问次数
*/
void KeyValueStore::record_access(const std::string& key) {
    access_count_[key]++;
}

/**
 * @brief 将键从cold cache移动到hot cache
*/
void KeyValueStore::move_to_hot(const std::string& key, const std::string& value) {
    auto it = cold_cache_.find(key);
    if (it != cold_cache_.end()) {
        hot_list_.emplace_front(key, value);
        hot_cache_[key] = hot_list_.begin();
        cold_list_.erase(it->second);
        cold_cache_.erase(it);
    }
}