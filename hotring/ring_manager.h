#ifndef RING_MANAGER_H
#define RING_MANAGER_H

#include <vector>
#include "ring_header.h"
#include <functional>

class RingManager {
public:
    RingManager(int k);
    void put(const std::string& key, const std::string& value);
    auto read(const std::string& key) -> std::string;

private:
    auto hash_function(const std::string& key) -> int { return hasher_(key); };

    std::vector<RingHeader *> table_; // 管理每一个环的哈希表
    int table_size_; // 哈希表的大小
    int k_; // 一个哈希值中，前n-k位为tag，后k位为hash
    int mask_;
    std::hash<std::string> hasher_; // 哈希函数对象
};

#endif // RING_MANAGER_H