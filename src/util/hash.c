#include "hash.h"


size_t hash_int(const void* p) {
	return (size_t)(*((int*)p));
}

size_t hash_str(const void* p) {
    const char* str = (const char*)p;
    size_t hash = 0;
    while (*str) {
        hash = hash * 31 + *str;
        ++str;
    }
    return hash;
}