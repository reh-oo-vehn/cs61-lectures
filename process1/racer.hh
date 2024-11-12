#ifndef CS61_RACER_HH
#define CS61_RACER_HH
#include <unistd.h>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <csignal>
#include <ctime>
#include <string>
#include <format>
#include <sstream>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sched.h>
#include <errno.h>
#include "print_bytes.hh"

// dsleep(t)
//    Sleep for `t` seconds.

inline int dsleep(double t) {
    assert(t >= 0 && t < std::numeric_limits<useconds_t>::max() / 1'000'000);
    return usleep((useconds_t) (t * 1'000'000));
}


// racer_fork(work_time)
//    Create a child process that exits after `work_time` seconds. Returns the
//    child process’s pid.

inline pid_t racer_fork(double work_time) {
    pid_t p = fork();
    assert(p >= 0);
    if (p == 0) {
        if (work_time > 0) {
            dsleep(work_time);
        }
        _exit(0);
    }
    return p;
}


// racer_status(elapsed, waitresult, status)
//    Return human-readable information about the race.

inline std::string racer_status(double elapsed, pid_t waitresult, int status) {
    extern bool verbose;
    if (!verbose) {
        return "";
    } else if (waitresult == -1) {
        return std::format(" {:.06f} (parent interrupted by {})", elapsed, strerror(errno));
    } else if (waitresult == 0) {
        return std::format(" {:.06f} (child has not exited)", elapsed);
    } else if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 0) {
            return std::format(" {:.06f}", elapsed);
        }
        return std::format(" {:.06f} (child exited with status {})", elapsed, WEXITSTATUS(status));
    } else {
        return std::format(" {:.06f} (child terminated abnormally)", elapsed);
    }
}


// make_timeval(t)
//    Return `t` as a `struct timeval`.

inline struct timeval make_timeval(double d) {
    double intpart;
    double fracpart = modf(d, &intpart);
    struct timeval tv = {
        (long) intpart, (int) (fracpart * 1'000'000)
    };
    return tv;
}


// set_signal_handler(signo, handler)
//    Install `handler` as the signal handler for `signo`.
//    The `handler` is automatically re-installed after signal delivery.
//    Has the same interface as `signal()` (`man 2 signal`), but is portable.

inline int set_signal_handler(int signo, void (*handler)(int)) {
    struct sigaction sa;
    sa.sa_handler = handler;    // call `handler` on signal
    sigemptyset(&sa.sa_mask);   // don't block other signals in handler
    sa.sa_flags = 0;            // don't restart system calls
    return sigaction(signo, &sa, nullptr);
}


// parse_arguments(argc, argv)
//    Parse arguments for `-V`, `-e DELAY`, `-t DELAY`.

inline void parse_arguments(int argc, char* argv[]) {
    extern bool verbose;
    extern double work_time, timeout;
    int ch;
    while ((ch = getopt(argc, argv, "Vw:t:h")) != -1) {
        double* ptr = nullptr;
        if (ch == 'w') {
            ptr = &work_time;
        } else if (ch == 't') {
            ptr = &timeout;
        } else if (ch == 'V') {
            verbose = true;
        } else if (ch == 'h') {
            fprintf(stderr, "Usage: %s [-w WORKTIME] [-t TIMEOUT] [-V]\n", argv[0]);
            exit(0);
        }
        if (ptr) {
            char* endptr;
            double val = strtod(optarg, &endptr);
            if (*endptr == '\0') {
                *ptr = val;
            }
        }
    }
}

#endif
