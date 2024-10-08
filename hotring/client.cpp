#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include "ring_manager.h"
#include "client_simulator.h"

int main() {
    std::vector<std::vector<int>> results;
    std::vector<int> X_values = {40};
    size_t total_keys = 50000;

    for (int X : X_values) {
        double hotspot_ratio = X / 100.0;
        size_t hotspot_keys = total_keys * hotspot_ratio;
        RingManager manager(11);
        ClientSimulator client(manager, 8, 16, hotspot_ratio, total_keys, hotspot_keys);
        results.push_back(client.run(300));
        std::cout << X << " ";
    }
    std::cout << "finish";
    // 将结果保存到文件中
    std::ofstream outfile("load_data.txt");
    for (const auto& result : results) {
        for (int load : result) {
            outfile << load << " ";
        }
        outfile << "\n";
    }
    outfile.close();

    return 0;
}