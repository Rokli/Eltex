#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME "/my_queue"
#define MAX_SIZE 256

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; 
    attr.mq_msgsize = MAX_SIZE; 
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_RDONLY);
    
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    
    while(1){
        ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read >= 0) {
            printf("Получил: %s\n", buffer);
        } else {
            perror("mq_receive");
            return 1;
        }
    }



    if (mq_close(mq) == -1) {
        perror("mq_close");
        return 1;
    }

    if (mq_unlink(QUEUE_NAME) == -1) {
        perror("mq_unlink");
        return 1;
    }
    return 0;
}