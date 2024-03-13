#include <bitset>
#include <vector>
#include <iostream>
#include <array>
#include <fstream>
#include <iomanip>
#include "MurmurHash3.h" // Assume MurmurHash3_x64_128 is in this header

class BloomFilter {
private:
    std::vector<bool> bits;
    int m; // Size of the bit array
    int k; // Number of hash functions
    uint64_t seed = 522031910736;

public:
    BloomFilter(int m, int k) : m(m), k(k), bits(m, false) {}

    void add(int input) {
        uint64_t hash_output[2];
        MurmurHash3_x64_128(&input, sizeof(input), seed, &hash_output);
        for (int i = 0; i < k; ++i) {
            // Use different seeds for different hash functions
            bits[(hash_output[i % 2] + i * hash_output[1 - i % 2]) % m] = true;
        }
    }

    bool possibly_contains(int input) {
        uint64_t hash_output[2];
        MurmurHash3_x64_128(&input, sizeof(input), seed, &hash_output);
        for (int i = 0; i < k; ++i) {
            if (!bits[(hash_output[i % 2] + i * hash_output[1 - i % 2]) % m]) {
                return false; // Definitely not in set
            }
        }
        return true; // Possible false positive
    }

    double calculate_false_positive_rate() {
        int false_positives = 0;
        for (int i = 100; i < 200; ++i) { // Use numbers 100-199 for testing
            if (possibly_contains(i)) {
                ++false_positives;
            }
        }
        return static_cast<double>(false_positives) / 100.0; // Calculate rate
    }
};

int main() {
    std::ofstream results_file("bloom_filter_results.csv");

    // Write the top-left cell of the table as empty
    results_file << "(m\\k),";

    // Write the CSV headers for k values
    for (int k = 1; k <= 8; ++k) {
        results_file << "k=" << k << (k < 8 ? "," : "\n");
    }

    // Test for m in 200..1600
    for (int m = 200; m <= 500; m += 100) {
        // Write the m value at the beginning of the row
        results_file << "m=" << m << ",";

        // Test for k in 1..8
        for (int k = 1; k <= 8; ++k) {
            BloomFilter bf(m, k);

            // Add elements 0-99
            for (int i = 0; i < 100; ++i) {
                bf.add(i);
            }

            // Calculate the false positive rate using elements 100-199
            double false_positive_rate = bf.calculate_false_positive_rate();
            std::cout <<std::fixed << std::setprecision(5)<< false_positive_rate ;
            // Write results to the CSV file
            results_file <<std::fixed << std::setprecision(5)<< false_positive_rate << (k < 8 ? "," : "\n");

        }
    }

    // Close the file
    results_file.close();

    std::cout << "Testing completed. Results saved to bloom_filter_results.csv." << std::endl;

    return 0;
}