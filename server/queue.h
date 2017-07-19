
#ifndef QUEUE_H
#define QUEUE_H

// Максимальное кол-во сообщений в одной очереди.
#define MAX_MESSAGES 10

// Структура описывающая очередь для одного клиента.

struct queue {
    // Имя пользователя.
    char *username;
    // Идентификатор клиента (cookie, etc)
    int user_id;
    // ID чат-комнаты.
    int room_id;
    // Сокет пользователя.
    int user_socket;
    // Список сообщений которые должны быть переданы пользователю.
    char **msg_list;
    // Текущее количество сообщений в очереди.
    int msg_count;
    // Максимальная длинна очереди.
    const int msg_max_count;
};

/// Создать новую очередь.
/// \param messages_count - максимальная длинна очереди.
/// \param user_socket - сокет пользователя которому 
/// будут отправляется сообщения из данной очереди.
/// \return - если ошибка вернется -1, иначе 0.
struct queue *new_queue(int messages_max_count, int user_socket);

/// Добавить сообщение в очередь.
/// \param q
/// \param msg - указатель на сообщение размещенное в куче(!!!).
/// \return 
int add_message(struct queue *q, char *msg);

/// Отправляет сообщение.
/// \param q
/// \return 
int send_msg(struct queue *q);

/// Удалить очередь.
/// \param q
void del_queue(struct queue *q);

#endif /* QUEUE_H */

