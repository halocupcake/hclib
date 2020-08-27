#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

#include <hclib/hc_allocator.h>

// the allocator argument in each function can be NULL
static void *memory_allocate(struct hc_allocator const *allocator, size_t size);
static void *memory_allocate_aligned(struct hc_allocator const *allocator, size_t size, size_t alignment);
static void *memory_reallocate(struct hc_allocator const *allocator, void *data, size_t size);
static void *memory_reallocate_aligned(struct hc_allocator const *allocator, void *data, size_t size, size_t alignment);
static void  memory_free(struct hc_allocator const *allocator, void *data);
static void  memory_free_aligned(struct hc_allocator const *allocator, void *data);

static inline void *memory_allocate(struct hc_allocator const *const allocator, size_t size)
{
    if (allocator)
        return allocator->allocate(allocator->user_pointer, size);
    else
        return malloc(size);
}

static inline void *memory_allocate_aligned(struct hc_allocator const *const allocator, size_t size, size_t alignment)
{
    if (allocator)
        return allocator->allocate_aligned(allocator->user_pointer, size, alignment);
    else
#if defined(_MSC_VER) || defined(__MINGW32__)
        // TODO this needs _aligned_free apparently
        return _aligned_malloc(size, alignment); // fuck you Windows
#else
        return aligned_alloc(alignment, size);
#endif
}

static inline void *memory_reallocate(struct hc_allocator const *const allocator, void *const data, size_t size)
{
    if (allocator)
        return allocator->reallocate(allocator->user_pointer, data, size);
    else
        return realloc(data, size);
}

static inline void *memory_reallocate_aligned(struct hc_allocator const *const allocator, void *const data, size_t size, size_t alignment)
{
    if (allocator)
        return allocator->reallocate_aligned(allocator->user_pointer, data, size, alignment);
    else
#if defined(_MSC_VER) || defined(__MINGW32__)
        return _aligned_realloc(data, size, alignment);
#else
        return realloc(data, size);
#endif
}

static inline void memory_free(struct hc_allocator const *const allocator, void *const data)
{
    if (allocator)
        return allocator->free(allocator->user_pointer, data);
    else
        free(data);
}

static inline void memory_free_aligned(struct hc_allocator const *const allocator, void *const data)
{
    if (allocator)
        return allocator->free_aligned(allocator->user_pointer, data);
    else
#if defined(_MSC_VER) || defined(__MINGW32__)
        _aligned_free(data); // fuck you Windows
#else
        free(data);
#endif
}

#endif // MEMORY_H
