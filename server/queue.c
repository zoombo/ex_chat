#include <stdlib.h>
#include "queue.h"
#include <string.h>

struct queue *new_queue(int messages_count, int user_socket) {
    // Выделяем место в куче для новой структуры.
    struct queue *q = malloc(sizeof (struct queue));
    // "Инициализируем" структуру нулями.
    memset(q, 0, sizeof (struct queue));

    // int mess_list_len = sizeof(char*) *messages_count;
    q->msg_list = malloc(sizeof (char*) *messages_count);
    memset(q->msg_list, NULL, sizeof (char*) *messages_count);

    *((int*) (&(q->msg_max_count))) = messages_count;

    q->user_socket = user_socket;

    return q;
}

void del_queue(struct queue *q) {
    for (int i = 0; i < q->msg_count && i < q->msg_max_count; i++) {
        if (q->msg_list[i] != NULL)
            free(q->msg_list[i]);
    }
    free(q->msg_list);
    free(q);
}


