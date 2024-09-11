#include <cstdio>
#include <cstdint>
#include <set>
#include "print_bytes.hh"

int main() {
    std::set<uintptr_t> used_addresses;

    unsigned long count = 0;
    while (true) {
        ++count;
        int* p = new int{61};
        uintptr_t p_address = reinterpret_cast<uintptr_t>(p);
        if (used_addresses.contains(p_address)) {
            printf("Dynamic memory reused on allocation #%zu\n", count);
            exit(0);
        }
        used_addresses.insert(p_address);
        delete p;
        ++count;
    }
}
