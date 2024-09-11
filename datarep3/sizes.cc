#include <cstddef>
#include <cstdio>
#include "print_bytes.hh"

int main() {
    printf("%zu\n", sizeof(std::max_align_t));
    printf("%zu\n", alignof(std::max_align_t));
}
