#include <iostream>
#include <vector>
#include <fstream>
#include "key_value_store.h"
#include "client_simulator.h"

int main() {
    std::vector<std::vector<int>> results;
    std::vector<int> X_values = {20, 40, 100};
    size_t total_keys = 50000;

    for (int X : X_values) {
        double hotspot_ratio = X / 100.0;
        size_t hotspot_keys = total_keys * hotspot_ratio;

        KeyValueStore kv_store(50000, 1000000);
        ClientSimulator client(kv_store, 8, 16, hotspot_ratio, total_keys, hotspot_keys);
        results.push_back(client.run(300));
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