#include "ring_manager.h"
#include <iostream>

/**
 * @param 设置几位是真的hash
*/
RingManager::RingManager(int k) : k_(k), table_size_(1) {
    // 判断至少数组至少能放多少个元素
    table_size_ <<= k;

    // 此时得到的table_size_一定不小于最小值
    table_.resize(table_size_, nullptr);

    // 设置当前的mask
    mask_ = table_size_ - 1;
}

void RingManager::put(const std::string& key, const std::string& value) {
    int index = hash_function(key);
    int tag = index & (~mask_);
    RingItem item(tag, key, value);
    std::cout << index << std::endl;
    if (table_[index] == nullptr) {
        std::cout << "here" << std::endl;
        table_[index] = new RingHeader();
        table_[index]->set_header_address(&item);
        table_[index]->increase_total_counter(1);
        return;
    }
    table_[index]->put(item);
}

auto RingManager::read(const std::string& key) -> std::string {
    int index = hash_function(key);
    RingHeader *header = table_[index];

    int tag = index & (~mask_);
    RingItem item(tag, key);

    return header == nullptr ? "" : header->read(item);
}

auto RingManager::hash_function(const std::string& key) -> int {
    size_t hash_value = hasher_(key);
    return (hash_value & 0x3);
}