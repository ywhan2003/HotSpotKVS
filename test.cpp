#include "ring_manager.h"
#include <iostream>

int main() {
    RingManager manager(2);

    std::string key = "11111111";
    std::string value = "1111111111111111";
    std::cout << key << " ";
    manager.put(key, value);
    return 0;
}