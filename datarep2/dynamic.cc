#include <cstdio>
#include <string>
#include "print_bytes.hh"

int main() {
    int* a;
    int* b;
    int* c;
    int* array;

    a = new int{60};
    b = new int{1};
    c = new int{*a + *b};

    print_object(*a);
    print_object(*b);
    print_object(*c);

    array = new int[3];
    array[0] = *a;
    array[1] = *b;
    array[2] = array[0] + array[1];

    print_bytes(array, sizeof(int) * 3);

    delete a;
    delete b;
    delete c;
    delete[] array;

    a = new int{60};
    b = new int{1};
    c = new int{*a + *b};

    print_object(*a);
    print_object(*b);
    print_object(*c);

    array = new int[3];
    array[0] = *a;
    array[1] = *b;
    array[2] = array[0] + array[1];

    print_bytes(array, sizeof(int) * 3);
}
