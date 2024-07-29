#ifndef RING_HEADER_H
#define RING_HEADER_H

#include "ring_item.h"

class RingHeader {
public:
    RingHeader() : active_(0), total_counter_(0), header_address_(nullptr) {}

    auto get_active() const -> char { return active_; }
    void set_active(char active) { active_ = active; }

    auto get_total_counter() const -> unsigned int { return total_counter_; }
    void increase_total_counter(int count) { total_counter_ += count; }

    auto get_header_address() const -> RingItem * { return header_address_; }
    void set_header_address(RingItem *address) { header_address_ = address; }

    void put(RingItem& item);
    auto read(RingItem& item) -> std::string;

private:
    auto traverse(const RingItem& item, bool *found) const -> RingItem *;
    auto end(const RingItem& item, const RingItem& reached_item, bool *found) const -> bool;

    const unsigned int R = 5; // 再经历5次搜索后进行热点转移
    unsigned int current = 0; // 目前已经搜索的次数
    char active_; // 控制统计采样
    unsigned int total_counter_; // 该环被访问的次数
    RingItem *header_address_; // 指向的第一个item
};


#endif // RING_HEADER_H
