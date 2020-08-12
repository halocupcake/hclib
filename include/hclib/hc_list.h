#ifndef HC_LIST_H
#define HC_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>

#include "hc_def.h"
#include "hc_allocator.h"

struct hc_list_node {
    void *               data;
    struct hc_list_node *next;
};

struct hc_list {
    void *               destroy_user_pointer;
    void                 (*destroy)(void *user_pointer, void *data);

    struct hc_list_node *head;
    struct hc_list_node *tail;

    size_t               size;
};

HC_API struct hc_list_node *hc_list_node_create(struct hc_allocator const *allocator, void *data);
HC_API void *               hc_list_node_destroy(struct hc_list_node *node, struct hc_allocator const *allocator); // returns data

static void *               hc_list_node_get_data(struct hc_list_node const *node);
static struct hc_list_node *hc_list_node_get_next(struct hc_list_node const *node);
static bool                 hc_list_node_is_head(struct hc_list_node const *node, struct hc_list const *list);
static bool                 hc_list_node_is_tail(struct hc_list_node const *node);

HC_API void                 hc_list_init(struct hc_list *list,
                                         void *destroy_user_pointer,
                                         void (*destroy)(void *user_pointer, void *data));
HC_API void                 hc_list_destroy(struct hc_list *list, struct hc_allocator const *allocator); // will free nodes

HC_API bool                 hc_list_insert_next(struct hc_list *list, struct hc_list_node *node, struct hc_list_node *next_node);
HC_API struct hc_list_node *hc_list_remove_next(struct hc_list *list, struct hc_list_node *node);

static struct hc_list_node *hc_list_get_head(struct hc_list const *list);
static struct hc_list_node *hc_list_get_tail(struct hc_list const *list);
static size_t               hc_list_get_size(struct hc_list const *list);



static inline void *hc_list_node_get_data(struct hc_list_node const *const node)
{
    return node->data;
}

static inline struct hc_list_node *hc_list_node_get_next(struct hc_list_node const *const node)
{
    return node->next;
}

static inline bool hc_list_node_is_head(struct hc_list_node const *const node, struct hc_list const *const list)
{
    return node == list->head;
}

static inline bool hc_list_node_is_tail(struct hc_list_node const *const node)
{
    return node->next == NULL;
}

static inline struct hc_list_node *hc_list_get_head(struct hc_list const *const list)
{
    return list->head;
}

static inline struct hc_list_node *hc_list_get_tail(struct hc_list const *const list)
{
    return list->tail;
}

static inline size_t hc_list_get_size(struct hc_list const *const list)
{
    return list->size;
}

#ifdef __cplusplus
}
#endif

#endif // HC_LIST_H
