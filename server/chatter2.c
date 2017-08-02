#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// For sockets
#include <sys/socket.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <sys/epoll.h>

#include "chatter2.h"
#include "queue.h"

// Функция заглушка для неиспользуемых переменных.
extern void pass(void *v);

void* chatter2(void* parms) {

    // TODO: Постараемся пока не пользовать мьютексы.

    // Приводим принятую структуру к нужной нам.
    struct chatter2_parms *cast_parms = parms;
    // thr_sl - структура которая будет хранить список сокетов
    // с которыми работаем в данный момент.
    struct sock_list thr_sl = {};
    // struct sock_list *sl = cast_parms->s32_list;

    struct epoll_event in_event = {}, *events = malloc(sizeof (struct epoll_event) * MAX_CLIENTS_S);
    memset(events, 0, sizeof (struct epoll_event) * MAX_CLIENTS_S);

    int epoll_fd, number_fds;
    //pass((void*) &number_fds);

    epoll_fd = epoll_create1(0);

    if (epoll_fd == -1) {
        printf("epoll_create1 error.\n");
        exit(EXIT_FAILURE);
    }

    in_event.events = EPOLLIN;
    in_event.data.fd = cast_parms->signal_sock;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cast_parms->signal_sock, &in_event);

    // Один клиент уже есть - это основной поток с сигнальным сокетом.
    // thr_sl.count++;

    while (true) {

        number_fds = epoll_wait(epoll_fd, events, MAX_CLIENTS_S, -1);

        // Тут поток сохраняет, в свой внутренний список, полученный список сокетов.
        // Если есть что брать и есть свободные места - заходим в цикл.
        if (cast_parms->clients_received_count > 0 && thr_sl.count < MAX_CLIENTS_S) {
            // Пока не достигнут конец и есть свободные места и входящий список не пуст.
            for (int i = 0;
                    i < MAX_CLIENTS_S &&
                    thr_sl.count < MAX_CLIENTS_S &&
                    cast_parms->clients_received_count > 0;
                    i++) {
                // Для начала добавляем в epoll.
                in_event.events = EPOLLIN;
                in_event.data.fd = cast_parms->s32clients_fd[cast_parms->clients_received_count];
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cast_parms->s32clients_fd[cast_parms->clients_received_count], &in_event);

                // Ищем свободный элемент.
                if (thr_sl.s32clients_fd[i] == ZNULL) {
                    // Присваиваем свободному элементу последний сокет в сохраняемом списке.
                    thr_sl.s32clients_fd[i] = cast_parms->s32clients_fd[cast_parms->clients_received_count - 1];
                    thr_sl.count++;
                    // После сохранения клиента во внутренний список, убираем его из сохраняемого.
                    cast_parms->s32clients_fd[cast_parms->clients_received_count] = ZNULL;
                    cast_parms->clients_received_count--;
                }
            }
            cast_parms->clients_available = MAX_CLIENTS_S - thr_sl.count;
        }



    }

}

/// Добавляет в список dst_l сокеты из списка src_l пока есть места в dst_l.
/// После добавления элемента в dst_l удаляет его из src_l.
/// \param dst_l
/// \param src_l
/// \return количество сокетов оставшихся в src_l.

int merge_sock_lists(struct sock_list *dst_l, struct sock_list *src_l) {

    if (dst_l->count >= MAX_CLIENTS_S) {
        return src_l->count;
    }

    for (int loop_count = src_l->count; loop_count > 0; loop_count--) {
        // Ищем первый пустой элемент в dst списке и добавляем в него последний
        // элемент списка src.
        for (int i = 0; i < MAX_CLIENTS_S; i++)
            if (dst_l->s32clients_fd[i] == ZNULL) {
                dst_l->s32clients_fd[i] = src_l->s32clients_fd[src_l->count - 1];
                src_l->s32clients_fd[src_l->count - 1] = ZNULL;
                src_l->count--;
                dst_l->count++;
                break;
            }
    }
    return src_l->count;

}




