#include <cstdio>
#include <string>
#include "print_bytes.hh"

int main() {
    int a = 60;
    int b = 1;
    int c = a + b;

    print_object(a);
    print_object(b);
    print_object(c);

    int array[3];
    array[0] = a;
    array[1] = b;
    array[2] = a + b;

    print_object(array);
}
