#include <cstdio>
#include <string>
#include "print_bytes.hh"

[[gnu::noinline]] /* inhibit optimizations we don’t want */
void f(int a, int b) {
    int c = a + b;

    printf("Running f(%d, %d)...\n", a, b);
    print_object(a);
    print_object(b);
    print_object(c);

    if (b > 0) {
        f(a + 1, b - 1);
    }
}

int main(int argc, char* argv[]) {
    // we must have exactly 3 arguments (including the program name)
    assert(argc == 3);

#if SAN
    printf("\n* This program produces surprising results when compiled with sanitizers!\n\n");
#endif

    // convert texts to integers
    int a = std::stoi(argv[1]);
    int b = std::stoi(argv[2]);

    print_object(a);
    print_object(b);

    f(a, b);
}
