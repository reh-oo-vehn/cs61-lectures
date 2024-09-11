#include <cstdio>
#include <string>
#include <charconv>
#include <cstring>
#include "print_bytes.hh"

const char* stringify(int i) {
    char buffer[4];
    assert(i >= 0 && i < 1000);

    // Goal: Put a textual representation of `i` into `buffer`
    // and return it. Example: If i == 61, then put "061" into
    // `buffer`, with a terminating NUL character '\0' to end
    // the string.
    buffer[0] = i / 100 + '0';
    buffer[1] = (i / 10) % 10 + '0';
    buffer[2] = i % 10 + '0';
    buffer[3] = '\0';

    return buffer;
}


int main() {
    const char* result = stringify(61);
    print_bytes_ascii(result, strlen(result));
}
