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
    int hash_value = hash_function(key);
    int index = hash_value & mask_;
    int tag = hash_value & (~mask_);
    auto *item = new RingItem(tag, key, value); // 这里一定要用指针，否则该函数结束时内存会被释放
    if (table_[index] == nullptr) {
        table_[index] = new RingHeader();
        table_[index]->set_header_address(item);
        table_[index]->increase_total_counter(1);
        return;
    }
    table_[index]->put(*item);
}

auto RingManager::read(const std::string& key) -> std::string {
    int hash_value = hash_function(key);
    int index = hash_value & mask_;
    RingHeader *header = table_[index];

    int tag = hash_value & (~mask_);
    RingItem item(tag, key);

    return header == nullptr ? "" : header->read(item);
}
