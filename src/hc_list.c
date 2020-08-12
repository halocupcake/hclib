#include <hclib/hc_list.h>

#include <stdlib.h>
#include <string.h>

void hc_list_init(struct hc_list *const list,
                  struct hc_allocator const *const allocator,
                  void *const destroy_user_pointer,
                  void (*const destroy)(void *user_pointer, void *data))
{
    memcpy(&list->allocator, allocator, sizeof(struct hc_allocator));
    list->destroy_user_pointer = destroy_user_pointer;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void hc_list_destroy(struct hc_list *const list)
{
    while (list->size > 0) {
        void *data;
        if (hc_list_remove_next(list, NULL, &data) && list->destroy)
            list->destroy(list->destroy_user_pointer, data);
    }
    memset(list, 0, sizeof(struct hc_list));
}

bool hc_list_insert_next(struct hc_list *const list, struct hc_list_node *const node, void *const data)
{
    struct hc_list_node *new_node = malloc(sizeof(struct hc_list_node));
    if (!new_node)
        return false;

    new_node->data = data;
    if (!node) {
        if (list->size == 0)
            list->tail = new_node;

        new_node->next = list->head;
        list->head = new_node;
    } else {
        if (!node->next)
            list->tail = new_node;

        new_node->next = node->next;
        node->next = new_node;
    }

    list->size++;

    return true;
}

bool hc_list_remove_next(struct hc_list *const list, struct hc_list_node *const node, void **const data)
{
    if (list->size == 0)
        return false;

    struct hc_list_node *removed_node;
    if (!node) {
        *data = list->head->data;
        removed_node = list->head;
        list->head = list->head->next;

        if (list->size == 1)
            list->tail = NULL;
    } else {
        if (!node->next)
            return false;

        *data = node->next->data;
        removed_node = node->next;
        node->next = node->next->next;

        if (!node->next)
            list->tail = node;
    }

    free(removed_node);
    list->size--;

    return true;
}
