#include "../lightlog.h"
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>

int n = 0;

void *test(void *arg) {
    for (int i =0;i<500;i++) {
        LLOG(0) << "hello world" << " 1";
        LLOG(1) << "hello world 1";
        LLOG(2) << "hello world 1";
    }
    return nullptr;
}

void sig_exit (int signo) {
    exit(0);
}

int main (int argc, char *argv[]) {
    pthread_t tid;
    pthread_create(&tid, NULL, test, NULL);

    // signal(SIGALRM, sig_exit);
    // alarm(1);

    for (int i =0;i<500;i++) {
        LLOG(0) << "hello world " << 2;
        LLOG(1) << "hello world 2";
        LLOG(2) << "hello world 2";

    }
    pthread_join(tid, NULL);
    return 0;
}