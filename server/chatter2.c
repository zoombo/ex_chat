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


void* chatter2(void* parms) {

    // TODO: Постараемся пока не пользовать мьютексы.

    // Приводим принятую структуру к нужной нам.
    struct chatter_parms *cast_parms = parms;
    // thr_sl - структура которая будет хранить список сокетов
    // с которыми работаем в данный момент.
    struct sock_list thr_sl = {}, *sl = cast_parms->s32_list;

    struct epoll_event ev = {}, *events = malloc(sizeof (struct epoll_event) * MAX_CLIENTS_S);
    memset(events, 0, sizeof (struct epoll_event)*MAX_CLIENTS_S);

    int epoll_fd, number_fds;

    epoll_fd = epoll_create1(0);

    if (epoll_fd == -1) {
        printf("epoll_create1 error.\n");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = cast_parms->signal_sock;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cast_parms->signal_sock, &ev);

    // Один клиент уже есть - это основной поток с сигнальным сокетом.
    // thr_sl.count++;

    while (true) {

        number_fds = epoll_wait(epoll_fd, events, MAX_CLIENTS_S, -1);

        if (sl->count > 0) {
            for (int i = 0; i < sl->count && thr_sl.count < MAX_CLIENTS_S; i++) {
                thr_sl.s32clients_fd[thr_sl.count + i] = sl->s32clients_fd[i];
            }
        }
    }

}