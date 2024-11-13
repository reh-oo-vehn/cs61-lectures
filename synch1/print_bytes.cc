#include "print_bytes.hh"
#include <cassert>
#include <cstdint>

static void fprint_bytes_ascii(FILE* f, const void* ptr, size_t size,
                               bool ascii);
static void fprint_ascii(FILE* f, const unsigned char* p, size_t pos);
static size_t snprint_bytes_ascii(char* buf, size_t bufsz, const void* ptr,
                                  size_t size, bool ascii);
static int snprint_ascii(char* buf, size_t bufpos, size_t bufsz,
                         const unsigned char* ptr, size_t pos);

void print_bytes(const void* ptr, size_t size) {
    fprint_bytes_ascii(stdout, ptr, size, false);
}

void print_bytes_ascii(const void* ptr, size_t size) {
    fprint_bytes_ascii(stdout, ptr, size, true);
}

void fprint_bytes(FILE* f, const void* ptr, size_t size) {
    fprint_bytes_ascii(f, ptr, size, false);
}

void fprint_bytes_ascii(FILE* f, const void* ptr, size_t size) {
    fprint_bytes_ascii(f, ptr, size, true);
}

void fprint_bytes_ascii(FILE* f, const void* ptr, size_t size, bool ascii) {
    const unsigned char* byteptr = reinterpret_cast<const unsigned char*>(ptr);
    for (size_t i = 0; i != size; ++i) {
        if (i % 16 == 0) {
            uintptr_t address = reinterpret_cast<uintptr_t>(ptr) + i;
            // print `address` with apostrophe separators
            for (int shift = sizeof(address) * 8 - 16; shift >= 0; shift -= 16) {
                uintptr_t chunk = address >> shift;
                if (chunk == 0 && shift > 16) {
                    continue;
                }
                const char* fmt;
                if (shift > 16 && chunk <= 0xffff) {
                    fmt = "%x'";
                } else if (shift > 0) {
                    fmt = "%04x'";
                } else {
                    fmt = "%04x";
                }
                fprintf(f, fmt, chunk & 0xffff);
            }
        }
        fprintf(f, "%s%02x", (i % 8 == 0 ? "  " : " "), byteptr[i]);
        if (i % 16 == 15 || i == size - 1) {
            if (ascii) {
                fprint_ascii(f, byteptr, i);
            } else {
                fputs("\n", f);
            }
        }
    }
}

static void fprint_ascii(FILE* f, const unsigned char* byteptr, size_t pos) {
    // Print an ASCII report that ends with byte p[pos].
    // The first byte printed is p[first], where first is the max multiple
    // of 16 having `first < pos`. The report starts at column 51.
    size_t first = pos - (pos % 16);  // first char to print
    int n = pos + 1 - first;          // # chars to print
    char asciibuf[17];
    for (size_t i = first; i != first + n; ++i) {
        auto b = byteptr[i];
        asciibuf[i - first] = (b >= 32 && b < 127 ? b : '.');
    }
    fprintf(f, "%*s|%.*s|\n", 51 - (3 * n + (n > 8)), "", n, asciibuf);
}



size_t snprint_bytes(char* buf, size_t bufsz, const void* ptr, size_t size) {
    return snprint_bytes_ascii(buf, bufsz, ptr, size, false);
}

size_t snprint_bytes_ascii(char* buf, size_t bufsz, const void* ptr, size_t size) {
    return snprint_bytes_ascii(buf, bufsz, ptr, size, true);
}

size_t snprint_bytes_ascii(char* buf, size_t bufsz, const void* ptr, size_t size,
                           bool ascii) {
    if (bufsz == 0) {
        return 0;
    }
    const unsigned char* byteptr = reinterpret_cast<const unsigned char*>(ptr);
    size_t bufpos = 0;
    for (size_t i = 0; i != size; ++i) {
        if (i % 16 == 0) {
            uintptr_t address = reinterpret_cast<uintptr_t>(ptr) + i;
            // print `address` with apostrophe separators
            for (int shift = sizeof(address) * 8 - 16; shift >= 0; shift -= 16) {
                uintptr_t chunk = address >> shift;
                if (chunk == 0 && shift > 16) {
                    continue;
                }
                const char* fmt;
                if (shift > 16 && chunk <= 0xffff) {
                    fmt = "%x'";
                } else if (shift > 0) {
                    fmt = "%04x'";
                } else {
                    fmt = "%04x";
                }
                bufpos += snprintf(buf + bufpos, bufpos >= bufsz ? 0 : bufsz - bufpos,
                                   fmt, chunk & 0xffff);
            }
        }
        bufpos += snprintf(buf + bufpos, bufpos >= bufsz ? 0 : bufsz - bufpos,
                           "%s%02x", (i % 8 == 0 ? "  " : " "), byteptr[i]);
        if (i % 16 == 15 || i == size - 1) {
            if (ascii) {
                bufpos += snprint_ascii(buf, bufpos, bufsz, byteptr, i);
            } else {
                if (bufpos + 1 < bufsz) {
                    buf[bufpos] = '\n';
                    buf[bufpos + 1] = '\0';
                }
                bufpos += 2;
            }
        }
    }
    return bufpos;
}

static int snprint_ascii(char* buf, size_t bufpos, size_t bufsz,
                         const unsigned char* byteptr, size_t pos) {
    size_t first = pos - (pos % 16);  // first char to print
    int n = pos + 1 - first;          // # chars to print
    char asciibuf[17];
    for (size_t i = first; i != first + n; ++i) {
        auto b = byteptr[i];
        asciibuf[i - first] = (b >= 32 && b < 127 ? b : '.');
    }
    return snprintf(buf + bufpos, bufpos >= bufsz ? 0 : bufsz - bufpos,
                    "%*s|%.*s|\n", 51 - (3 * n + (n > 8)), "", n, asciibuf);
}
