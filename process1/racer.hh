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
#include <sstream>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sched.h>
#include <errno.h>

// timestamp()
//    Return current time in seconds since January 1, 1970 UTC.

inline double timestamp() {
    struct timespec ts;
    int r = clock_gettime(CLOCK_REALTIME, &ts);
    assert(r >= 0);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}


// dsleep(t)
//    Sleep for `t` seconds.

inline int dsleep(double t) {
    assert(t >= 0 && t < std::numeric_limits<useconds_t>::max() / 1'000'000);
    return usleep((useconds_t) (t * 1'000'000));
}


// racer_fork(delay)
//    Create a child process that exits after `delay` seconds. Returns the
//    child process’s pid.

inline pid_t racer_fork(double delay) {
    pid_t p = fork();
    assert(p >= 0);
    if (p == 0) {
        if (delay > 0) {
            dsleep(delay);
        }
        exit(0);
    }
    return p;
}


// racer_status(waitresult, status)
//    Return human-readable information about the race.

inline std::string racer_status(pid_t waitresult, int status) {
    extern bool verbose;
    if (!verbose) {
        return "";
    }
    std::stringstream ss;
    if (waitresult == -1) {
        ss << " (parent interrupted by " << strerror(errno) << ")";
    } else if (waitresult == 0) {
        ss << " (child did not exit in time)";
    } else if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 0) {
            return "";
        }
        ss << " (child exited with status " << WEXITSTATUS(status) << ")";
    } else {
        ss << " (child terminated abnormally)";
    }
    return ss.str();
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
