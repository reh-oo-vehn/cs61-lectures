#include <cstdio>
#include <string>
#include <charconv>
#include <cstring>
#include "print_bytes.hh"

struct short_string {
    char buffer[4];
};

short_string stringify(int i) {
    short_string ss;

    assert(i >= 0 && i < 1000);
    ss.buffer[0] = i / 100 + '0';
    ss.buffer[1] = (i / 10) % 10 + '0';
    ss.buffer[2] = i % 10 +'0';
    ss.buffer[3] = '\0';
    printf("In stringify:\n");
    print_object(ss);

    return ss;
}


int main() {
    short_string result = stringify(61);
    printf("In main:\n");
    print_object(result);
    print_bytes_ascii(result.buffer, strlen(result.buffer));
}
