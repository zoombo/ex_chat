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
#define PORT 4400
#define nl printf("\n")

/*
 * 
 */
#define MAX_CLIENTS_S 100

struct sock_list {
    int count;
    int s32clients_fd[MAX_CLIENTS_S];
};

struct chatter_parms {
    struct sock_list *s32_list;
    int signal_sock;
};

/*
 * 
 */

void* chatter(void* parms) {
    
    // Постараемся пока не пользовать мьютексы.
    struct chatter_parms *cast_parms = parms;
    struct sock_list *sl = cast_parms->s32_list;

    struct epoll_event ev, *events = malloc(sizeof (struct epoll_event) * MAX_CLIENTS_S);
    memset(events, 0, sizeof(struct epoll_event)*MAX_CLIENTS_S);
    
    int epoll_fd, number_fds;

    epoll_fd = epoll_create1(0);

    if (epoll_fd == -1) {
        printf("epoll_create1 error.\n");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = cast_parms->signal_sock;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cast_parms->signal_sock, &ev);
    
    while (true) {
        
        number_fds = epoll_wait(epoll_fd, events, MAX_CLIENTS_S, -1);
        
        if (sl->count > 0) {
            for (int i = 0; i < sl->count; i++) {
                
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
    // set SO_REUSEADDR on a socket to true (1):
    setsockopt(s32listener_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
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
    /*
        char *msg = "Hello!";
        char buf[1024];
     */
    //for (int i = 0; i < 1; i++) {
    while (true) {

        s32accept_fd = accept(s32listener_fd, 0, 0);
        /*
            send(s32accept_fd, msg, strlen(msg), 0);

            int recv_len = 0;
            recv_len = recv(s32accept_fd, buf, sizeof (buf), 0);

            for (int i = 0; i < recv_len; i++) {
                putchar(*(buf + i));
            }
            nl;

            //send(s32accept_fd, msg, strlen(msg), 0);

            shutdown(s32accept_fd, SHUT_RDWR);
            close(s32accept_fd);
         */

        // add_sock()

    }
    shutdown(s32listener_fd, SHUT_RDWR);
    close(s32listener_fd);

    return (EXIT_SUCCESS);
}

