#ifndef CS61_SPINLOCK_FAIRNESS_HH
#define CS61_SPINLOCK_FAIRNESS_HH
#include <cstddef>
#include <cstdio>

struct runcounters {
    static constexpr size_t max = 40;
    unsigned long c[max + 1];

    runcounters() {
        for (size_t i = 0; i != max + 1; ++i) {
            c[i] = 0;
        }
    }

    void add(size_t n) {
        ++c[n < max ? n : max];
    }
    void add(const runcounters& x) {
        for (size_t i = 0; i != max + 1; ++i) {
            c[i] += x.c[i];
        }
    }

    void print() {
        for (size_t i = 0; i != max; i += 4) {
            printf("%4zu: %12lu %12lu %12lu %12lu\n", i, c[i], c[i + 1], c[i + 2], c[i + 3]);
        }
        printf("%3zu+: %12lu\n", max, c[max]);
    }
};

template <typename T>
void fairness_threadfunc(T* lock, size_t nrounds, unsigned long* id, runcounters* ct) {
    size_t run = 0, expected = 0;

    for (size_t i = 0; i != nrounds; ++i) {
        lock->lock();

        if (*id != expected && run != 0) {
            ct->add(run);
            run = 0;
        }
        ++run;
        ++*id;
        expected = *id;

        lock->unlock();
    }

    ct->add(run);
}

#endif
