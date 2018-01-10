#include "../lightlog.h"
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>

int n = 0;

void *test(void *arg) {
    for (int i =0;i<500;i++) {
        LLOG(INFO) << "hello world" << " 1";
        LLOG_WARN << "hello world 1";
        LLOG(ERRO) << "hello world 1";
    }
    return nullptr;
}


int main (int argc, char *argv[]) {

    LLOG_LV(INFO);
    LLOG_FILE(); 
    LLOG_FILE(); 
    LLOG_CONSOLE_OFF();

    pthread_t tid;
    pthread_create(&tid, NULL, test, NULL);

    for (int i =0;i<500;i++) {
        LLOG(0) << "hello world " << 2;
        LLOG(1) << "hello world 2";
        LLOG(2) << "hello world 2";

    }
    pthread_join(tid, NULL);
    return 0;
}