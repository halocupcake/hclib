#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

#include <hclib/hc_allocator.h>

static void *memory_allocate(struct hc_allocator const *allocator, size_t size);
static void *memory_allocate_aligned(struct hc_allocator const *allocator, size_t size, size_t alignment);
static void *memory_reallocate(struct hc_allocator const *allocator, void *data, size_t size);
static void  memory_free(struct hc_allocator const *allocator, void *data);

static inline void *memory_allocate(struct hc_allocator const *const allocator, size_t size)
{
    if (allocator)
        return allocator->allocate(allocator->user_pointer, size);
    else
        return calloc(1, size);
}

static inline void *memory_allocate_aligned(struct hc_allocator const *const allocator, size_t size, size_t alignment)
{
    if (allocator)
        return allocator->allocate_aligned(allocator->user_pointer, size, alignment);
    else
        return aligned_alloc(alignment, size);
}

static inline void *memory_reallocate(struct hc_allocator const *const allocator, void *const data, size_t size)
{
    if (allocator)
        return allocator->reallocate(allocator->user_pointer, data, size);
    else
        return realloc(data, size);
}

static inline void memory_free(struct hc_allocator const *const allocator, void *const data)
{
    if (allocator)
        return allocator->free(allocator->user_pointer, data);
    else
        return free(data);
}

#endif // MEMORY_H
