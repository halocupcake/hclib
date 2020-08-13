#include <hclib/hc_list.h>

#include <string.h>

#include "memory.h"

struct hc_list_node *hc_list_node_create(struct hc_allocator const *const allocator, void *const data)
{
    struct hc_list_node *const node = memory_allocate(allocator, sizeof(struct hc_list_node));
    if (!node)
        return NULL;

    node->data = data;

    return node;
}

void *hc_list_node_destroy(struct hc_list_node *const node, struct hc_allocator const *const allocator)
{
    void *const data = node->data;
    memory_free(allocator, node);
    return data;
}

void hc_list_init(struct hc_list *const list,
                  void *const destroy_user_pointer,
                  void (*const destroy)(void *user_pointer, void *data))
{
    list->destroy_user_pointer = destroy_user_pointer;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void hc_list_destroy(struct hc_list *const list, struct hc_allocator const *const allocator)
{
    while (list->size > 0) {
        struct hc_list_node *const node = hc_list_remove_next(list, NULL);

        void *const data = hc_list_node_destroy(node, allocator);
        if (list->destroy)
            list->destroy(list->destroy_user_pointer, data);
    }

    memset(list, 0, sizeof(struct hc_list));
}

bool hc_list_insert_next(struct hc_list *const list, struct hc_list_node *const node, struct hc_list_node *const next_node)
{
    if (!node) {
        if (list->size == 0)
            list->tail = next_node;

        next_node->next = list->head;
        list->head = next_node;
    } else {
        if (!node->next)
            list->tail = next_node;

        next_node->next = node->next;
        node->next = next_node;
    }

    list->size++;

    return true;
}

struct hc_list_node *hc_list_remove_next(struct hc_list *const list, struct hc_list_node *const node)
{
    if (list->size == 0)
        return NULL;

    struct hc_list_node *removed_node = NULL;
    if (!node) {
        removed_node = list->head;
        list->head = list->head->next;

        if (list->size == 1)
            list->tail = NULL;
    } else {
        if (!node->next)
            return NULL;

        removed_node = node->next;
        node->next = node->next->next;

        if (!node->next)
            list->tail = node;
    }

    list->size--;

    return removed_node;
}
