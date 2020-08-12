#ifndef HC_ALLOCATOR_H
#define HC_ALLOCATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct hc_allocator {
    void *user_pointer;

    void *(*allocate)(void *user_pointer, size_t size);
    void *(*allocate_aligned)(void *user_pointer, size_t size, size_t alignment);
    void *(*reallocate)(void *user_pointer, void *data, size_t size);              // data can be NULL
    void  (*free)(void *user_pointer, void *data);                                 // data can be NULL
};

#ifdef __cplusplus
}
#endif

#endif // HC_ALLOCATOR_H
