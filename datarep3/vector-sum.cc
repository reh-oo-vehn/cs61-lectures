#include <vector>
#include <cstdio>
#include "print_bytes.hh"

unsigned long vector_sum(std::vector<unsigned long> vector) {
    unsigned long sum = 0;
    for (auto value : vector) {
        sum += value;
    }
    return sum;
}

int main() {
    std::vector<unsigned long> v;
    for (unsigned long i = 0; i != 100'000'000; ++i) {
        v.push_back(i);
    }
    printf("%zu\n", vector_sum(v));
}
