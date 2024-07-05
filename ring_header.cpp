#include "ring_header.h"
#include <iostream>

void RingHeader::put(RingItem& item) {
    bool found = false;
    RingItem *location = traverse(item, &found);

    if (found) {
        location->set_value(item.get_value());
        location->increase_counter(1);
        increase_total_counter(1);
        return;
    }
    
    item.set_next_address(location->get_next_address());
    location->set_next_address(&item);
    increase_total_counter(1);
}

auto RingHeader::read(RingItem& item) -> std::string {
    bool found = false;
    RingItem *location = traverse(item, &found);
    
    if (found) {
        location->increase_counter(1);
        increase_total_counter(1);
        return location->get_value();
    }

    increase_total_counter(1);
    return "";
}

/**
 * @brief 遍历整个环
 * @param 需要插入的环
 * @param 是否找到
 * @return 找到需要插入或搜索的位置
*/
auto RingHeader::traverse(const RingItem& item, bool *found) const -> RingItem * {
    RingItem *ptr = get_header_address();

    while (!end(item, *ptr, found)) {
        ptr = ptr->get_next_address();
    }

    return ptr;
}

/**
 * @brief 判断是否结束遍历
 * @param item 需要插入的item
 * @param reached_item 原本就有的目前遍历到的节点
 * @param found [bool *] 返回是否找到了  
*/
auto RingHeader::end(const RingItem& item, const RingItem& reached_item, bool *found) const -> bool {
    if (item == reached_item) {
        *found = true;
        return true;
    }

    *found = false;
    if (reached_item.get_next_address() == get_header_address()) {
        // 只有一个元素
        return true;
    }

    const RingItem& next_item = *(reached_item.get_next_address());
    const RingItem& next_next_item = *(next_item.get_next_address());

    // 在最小项前面
    bool case1 = next_item < reached_item && next_item < next_next_item && item < next_item;
    // 在最大项前面
    bool case2 = next_item > reached_item && next_item > next_next_item && item > next_item;
    // 在两者之间
    bool case3 = next_item < item && item < reached_item;
    bool case4 = next_item > item && item > reached_item;

    return case1 || case2 || case3 || case4;
}