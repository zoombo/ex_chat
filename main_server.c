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

/*
 * 
 */
#define PORT 4400
#define nl printf("\n")

/*
 * 
 */
int main(int argc, char** argv) {

    int status = 0;
    struct sockaddr_in serv_addr = {};
    int s32listener_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s32listener_fd == -1) {
        printf("Error create socket.\n");
        return -1;
    }

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
    //sets

    int s32accept_fd = 0;
    char *msg = "Hello!";
    char buf[1024];
    for (int i = 0; i < 1; i++) {

        s32accept_fd = accept(s32listener_fd, 0, 0);
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

    }
    shutdown(s32listener_fd, SHUT_RDWR);
    close(s32listener_fd);

    return (EXIT_SUCCESS);
}

