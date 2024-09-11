#include <cstdio>
#include <string>
#include <charconv>
#include <cstring>
#include "print_bytes.hh"

std::string stringify(int i) {
    char buffer[4];

    assert(i >= 0 && i < 1000);
    buffer[0] = i / 100 + '0';
    buffer[1] = (i / 10) % 10 + '0';
    buffer[2] = i % 10 + '0';
    buffer[3] = '\0';
    print_bytes_ascii(buffer, strlen(buffer));

    return std::string{buffer};
}


int main() {
    std::string result = stringify(61);
    print_object(result);
    print_bytes_ascii(result.data(), result.length());
}
