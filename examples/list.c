#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hclib/hc_list.h>

struct email {
    char const *recipient;
    char const *message;
};

static struct email *email_create(char const *recipient, char const *message);
static void          email_destroy(struct email *email);

static void          list_destroy_email(void *user_pointer, void *data);

int main(int argc, char *argv[])
{
    struct hc_list email_chain;
    hc_list_init(&email_chain, NULL, list_destroy_email);

    char const *const messages[] = {
        "u big nerd ;^)", "hey", "bob", "how", "are", "ya"
    };
    unsigned const message_count = sizeof(messages) / sizeof(char const *);

    for (unsigned i = 0; i < message_count; i++) {
        struct email *email = email_create("Bob", messages[i]);
        if (!email) {
            fprintf(stderr, "couldn't create an email!\n");
            return EXIT_FAILURE;
        }

        struct hc_list_node *email_node = hc_list_node_create(NULL, email);
        if (!hc_list_insert_next(&email_chain, hc_list_get_tail(&email_chain), email_node)) {
            fprintf(stderr, "couldn't insert an email into the list!\n");
            return EXIT_FAILURE;
        }
    }

    // oops we dont want to send that first part to bobby boy
    struct hc_list_node *offensive_email = hc_list_remove_next(&email_chain, NULL);
    if (!offensive_email) {
        fprintf(stderr, "couldn't remove an email from the head of the list!\n");
        return EXIT_FAILURE;
    }
    list_destroy_email(NULL, offensive_email->data);
    hc_list_node_destroy(offensive_email, NULL);

    printf("reading %zu emails in a chain...\n\n", hc_list_get_size(&email_chain));
    struct hc_list_node *node = hc_list_get_head(&email_chain);
    while (node) {
        if (hc_list_node_is_head(node, &email_chain))
            printf("-------------------\n");

        struct email *email = hc_list_node_get_data(node);

        printf("recipient: %s\n"
               "message: %s\n"
               "-------------------\n",
               email->recipient,
               email->message);

        node = hc_list_node_get_next(node);
    }
    printf("\nalright that's all of the emails\n");

    hc_list_destroy(&email_chain, NULL);

    return 0;
}

static struct email *email_create(char const *const recipient, char const *const message)
{
    struct email *email = malloc(sizeof(struct email));
    if (!email)
        goto error;

    char *email_recipient = calloc(sizeof(char), strlen(recipient) + 1);
    if (!email_recipient)
        goto cleanup_email;

    char *email_message = calloc(sizeof(char), strlen(message) + 1);
    if (!email_message)
        goto cleanup_recipient;

    strcpy(email_recipient, recipient);
    strcpy(email_message, message);

    email->recipient = email_recipient;
    email->message = email_message;

    return email;

cleanup_recipient:
    free(email_message);
cleanup_email:
    free(email);
error:
    return NULL;
}

static void email_destroy(struct email *const email)
{
    free(email->message);
    free(email->recipient);
    free(email);
}

static void list_destroy_email(void *const user_pointer, void *const data)
{
    email_destroy(data);
}
