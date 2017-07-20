/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dimasik
 *
 * Created on 12 июля 2017 г., 16:25
 */

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
/*
 * 
 */
#include "queue.h"
#include "chatter2.h"

/*
 * 
 */

// Функция заглушка для неиспользуемых переменных.
void pass(void *v) {
    return;
}

#define nl printf("\n")

/*
 * 
 */

void* chatter(void* parms) {

    // TODO: Постараемся пока не пользовать мьютексы.

    // Приводим принятую структуру к нужной нам.
    struct chatter_parms *cast_parms = parms;
    // thr_sl - структура которая будет хранить список сокетов
    // с которыми работаем в данный момент.
    struct sock_list thr_sl = {}, *sl = cast_parms->s32_list;

    struct epoll_event ev = {}, *events = malloc(sizeof (struct epoll_event) * MAX_CLIENTS_S);
    memset(events, 0, sizeof (struct epoll_event)*MAX_CLIENTS_S);

    int epoll_fd, number_fds;
    pass((void*)&number_fds);
    
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

int add_sock(struct sock_list *sl, int s32sock_fd) {
    // TODO: эта функция добавляет сокет подсоединившегося клиента к списку
    // обрабатываемых сокетов.
    return 0;
}

int main(int argc, char** argv) {

    int status = 0;
    struct sockaddr_in serv_addr = {};
    int s32listener_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s32listener_fd == -1) {
        printf("Error create socket.\n");
        return -1;
    }

    int optval = 1;
    /* Когда мы закрываем сокет, он продолжает висеть некоторое время с 
     * состоянием TIME_WAIT и пока ОС его не закроет сокет с такими же 
     * параметрами (с таким же портом) открыть нельзя.
     * setsockopt можно задать параметр SO_REUSEADDR и тогда сокет можно
     * использовать повторно сразуже.
     */
    setsockopt(s32listener_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Повесить на все доступные интерфейсы.
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    status = bind(s32listener_fd, (struct sockaddr*) &serv_addr, sizeof (serv_addr));
    if (status == -1) {
        printf("Error bind socket.\n");
        return -1;
    }

    status = listen(s32listener_fd, 10);
    if (status == -1) {
        printf("Error listen socket.\n");
        return -1;
    }

    int s32accept_fd = 0;
    char *msg = "Hello!";
    //    char buf[1024];
    struct queue * clients[MAX_CLIENTS_S] = {};
    int clients_count = 0;



    while (true) {

        s32accept_fd = accept(s32listener_fd, 0, 0);

        clients[clients_count] = new_queue(MAX_MESSAGES, s32accept_fd);
        add_message(clients[0], msg);
        send_msg(clients[0]);



    }
    shutdown(s32listener_fd, SHUT_RDWR);
    close(s32listener_fd);

    return (EXIT_SUCCESS);
}

