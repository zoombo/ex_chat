/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   chatter2.h
 * Author: powder
 *
 * Created on 19 июля 2017 г., 14:05
 */

#ifndef CHATTER2_H
#define CHATTER2_H

#define PORT 4400

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

void* chatter2(void* parms);

#endif /* CHATTER2_H */

