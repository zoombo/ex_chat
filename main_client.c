/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dimasik
 *
 * Created on 13 июля 2017 г., 14:46
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// For sockets
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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

    struct sockaddr_in dst_serv_addr = {};
    int s32client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    dst_serv_addr.sin_family = AF_INET;
    dst_serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &dst_serv_addr.sin_addr);

    connect(s32client_fd, (struct sockaddr*) &dst_serv_addr, sizeof (dst_serv_addr));

    char *sending_msg = "Hi! How are you?";
    char buf[1024];
    //printf("%d\n", sizeof(buf));
    
    send(s32client_fd, sending_msg, strlen(sending_msg), 0);

    int recv_len = 0;
    recv_len = recv(s32client_fd, buf, sizeof (buf), 0);
    for (int i = 0; i < recv_len; i++) {
        putchar(*(buf + i));
    }
    nl;

    shutdown(s32client_fd, SHUT_RDWR);
    close(s32client_fd);

    return (EXIT_SUCCESS);
}

