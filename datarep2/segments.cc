#include <cstdio>
#include <string>
#include "print_bytes.hh"

int global = 61;
const int global_constant = 61;

int main() {
    int local = 61;
    int* dynamic = new int{61};

    print_object(global);
    print_object(global_constant);
    print_object(local);
    print_object(*dynamic);
}
