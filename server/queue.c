#include <stdlib.h>
#include "queue.h"
#include <string.h>

struct queue *new_queue(int messages_max_count, int user_socket) {
    // Выделяем место в куче для новой структуры.
    struct queue *q = malloc(sizeof (struct queue));
    // "Инициализируем" структуру нулями.
    memset(q, 0, sizeof (struct queue));

    // int mess_list_len = sizeof(char*) *messages_count; // Неверно.
    // Массив указателей на сообщения.
    q->msg_list = malloc(sizeof (char*) *messages_max_count);
    memset(q->msg_list, NULL, sizeof (char*) *messages_max_count);

    *((int*) (&(q->msg_max_count))) = messages_max_count;

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

int add_message(struct queue *q, char *msg) {

    // Предполагается что msg имеет '\0' в конце.
    int msg_len = strlen(msg) + 1;
    int new_msg_ptr = malloc(msg_len);
    strcpy(new_msg_ptr, msg);
    
    // Теперь, есть вариант добавлять сообщение в конец очереди, а после его
    // отправки сдвигать очередь вперед. Т.е. наверное будет легче написать,
    // но на сдвиг очереди будет затрачиваться больше ресурсов и времени.
    // И есть вариант ничего не сдвигать, а просто представить что массив 
    // сообщений, это очередь в виде кольца и хранить в структуре позицию
    // первого сообщения, а новые сообщения добавлять в первую пустую позицию 
    // найденную за текущим сообщением.
    /*
     
     
     
     
     
     
     */
    
}


