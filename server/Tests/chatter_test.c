/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   chatter_test.c
 * Author: powder
 *
 * Created on 2 августа 2017 г., 19:36
 */

#include <stdio.h>
#include <stdlib.h>
#include "../chatter2.h"

/*
 * Simple C Test Suite
 */

/*
void test1() {
    printf("chatter_test test 1\n");
}

void test2() {
    printf("chatter_test test 2\n");
    printf("%%TEST_FAILED%% time=0 testname=test2 (chatter_test) message=error message sample\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% chatter_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (chatter_test)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (chatter_test) \n");

    printf("%%TEST_STARTED%% test2 (chatter_test)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (chatter_test) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
 */

int main(void) {
    struct sock_list dst_lst = {}, src_lst = {};

    dst_lst.s32clients_fd[0] = ZNULL;
    dst_lst.s32clients_fd[1] = 100;
    dst_lst.s32clients_fd[2] = 101;
    dst_lst.s32clients_fd[3] = ZNULL;
    dst_lst.s32clients_fd[4] = 102;
    dst_lst.count = 3;

    src_lst.s32clients_fd[0] = 200;
    src_lst.s32clients_fd[1] = 201;
    src_lst.s32clients_fd[2] = 202;
    src_lst.count = 3;

    int result = merge_sock_lists(&dst_lst, &src_lst);
    if (result == 0)
        printf("\"merge_sock_lists\" returned : %d ;\n", result);

    for (int i = 0; i < MAX_CLIENTS_S; i++) {
        printf("%d ", dst_lst.s32clients_fd[i]);
        // DEBUG.
        if (i != 0 && i % 10 == 0)
            printf("\n");
        // END_DEBUG.
    }
    printf("\n");

}
