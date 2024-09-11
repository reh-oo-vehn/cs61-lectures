#include <cstdio>
#include <string>
#include "print_bytes.hh"

int main() {
    unsigned char a = 61;
    char b = 61;
    short c = 61;
    int d = 61;
    long e = 61;
    char f[] = "61";
    float g = 61.0;

    print_object(a);
    print_object(b);
    print_object(c);
    print_object(d);
    print_object(e);
    print_object(f);
    print_object(g);
}
