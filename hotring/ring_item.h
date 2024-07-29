#ifndef RING_ITEM_H
#define RING_ITEM_H

#include <string>

class RingItem {
public:
    RingItem(int tag, const std::string& key)  
        : tag_(tag), key_(key), value_(""), metadata_(""), 
            rehash_(0), occupied_(0), counter_(1), next_address_(this) {}

    RingItem(int tag, const std::string& key, const std::string& value) 
        : tag_(tag), key_(key), value_(value), metadata_(""), 
            rehash_(0), occupied_(0), counter_(1), next_address_(this) {}

    RingItem(const std::string& metadata, int tag, const std::string& key, const std::string& value)
        : metadata_(metadata), tag_(tag), key_(key), value_(value), 
            rehash_(0), occupied_(0), counter_(1), next_address_(this) {}

    auto get_metadata() const -> std::string { return metadata_; }
    void set_metadata(std::string& metadata) { metadata_ = metadata; }

    auto get_tag() const -> unsigned int { return tag_; }
    void set_tag(unsigned int tag) { tag_ = tag; }

    auto get_rehash() const -> char { return rehash_; }
    void set_rehash(char rehash) { rehash_ = rehash; }

    auto get_occupied() const -> char { return occupied_; }
    void set_occupied(char occupied) { occupied_ = occupied; }

    auto get_counter() const -> unsigned int { return counter_; }
    void increase_counter(int count) { counter_ += count; }

    auto get_next_address() const -> RingItem * { return next_address_; }
    void set_next_address(RingItem *address) { next_address_ = address; }

    auto get_key() const -> std::string { return key_; }
    void set_key(const std::string& key) { key_ = key; }

    auto get_value() const -> std::string { return value_; }
    void set_value(const std::string& value) { value_ = value; }

    bool operator<(const RingItem& item) const {
        return this->tag_ == item.get_tag() ? this->key_ < item.get_key() : this->tag_ < item.get_tag();
    }

    bool operator>(const RingItem& item) const {
        return this->tag_ == item.get_tag() ? this->key_ > item.get_key() : this->tag_ > item.get_tag();
    }

    bool operator==(const RingItem& item) const {
        return this->tag_ == item.get_tag() ? this->key_ == item.get_key() : false;
    }

private:
    std::string metadata_;
    unsigned int tag_; // 与哈希值的前一部分
    char rehash_; // 用于控制数据量增大之后的重哈希
    char occupied_; // 控制并发的正确性
    unsigned int counter_; // 当前项被访问的次数
    RingItem *next_address_; // 下一项的地址
    std::string key_;
    std::string value_;
};


#endif // RING_ITEM_H