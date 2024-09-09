#include <cstdio>
#include <string>
#include "print_bytes.hh"

int main() {
    const char hi[] = "Hi";
    const char string[] = "CS 61 is here";

    print_object_ascii(hi);
    print_object_ascii(string);

    /*
    const char* digits = "0123456789";
    print_bytes(digits, 10);

    char digit_zero = '0';
    print_object(digit_zero);
    */
}
