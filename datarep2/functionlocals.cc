#include <cstdio>
#include <string>
#include "print_bytes.hh"

void f(int a, int b) {
    int c = a + b;

    printf("Running f(%d, %d)...\n", a, b);
    print_object(a);
    print_object(b);
    print_object(c);
}

int main() {
    int a = 60;
    int b = 1;

    print_object(a);
    print_object(b);

    f(a, b);
}
