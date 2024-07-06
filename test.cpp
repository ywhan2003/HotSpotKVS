//#include "ring_manager.h"
//#include <iostream>
//#include <random>
//#include <chrono>
//#include <string>
//#include <unordered_map>
//#include <vector>
//
//#define KEY_LENGTH 8
//#define VALUE_LENGTH 16
//
//std::default_random_engine generator_;
//std::vector<std::string> key_set;
//
//auto generate_random_string(size_t length) -> std::string {
//    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//    std::string result;
//    result.resize(length);
//
//    std::uniform_int_distribution<int> char_distribution(0, sizeof(charset) - 2); // 最后一个字符是'\0'
//
//    for (size_t i = 0; i < length; ++i) {
//        result[i] = charset[char_distribution(generator_)];
//    }
//
//    return result;
//}
//
//int main() {
//    RingManager manager(1);
//
//    std::vector<std::string> key_set;
//
//    for (int i = 0; i < 4; i++) {
//        auto key = generate_random_string(KEY_LENGTH);
//        auto value = generate_random_string(VALUE_LENGTH);
//        key_set.push_back(key);
//        manager.put(key, value);
//        std::cout << "Put success " << i << std::endl;
//    }
//
//    for (int i = 0; i < 4; i++) {
//        auto key = key_set[i];
//        auto value = generate_random_string(VALUE_LENGTH);
//        manager.put(key, value);
//        std::cout << "Put success " << i << std::endl;
//    }
//
//    for (int i = 0; i < 4; i++) {
//        auto key = key_set[i];
//        std::cout << i << ". " << manager.read(key) << std::endl;
//    }
//
//    return 0;
//}