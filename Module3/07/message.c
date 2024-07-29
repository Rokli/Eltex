#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME "/my_queue"
#define QUEUE_NAME_EXIT "/exit"
#define MAX_SIZE 256

int check_queue_exit(mqd_t mq, const char *queue_name) {
    char buffer[MAX_SIZE];
    struct mq_attr attr;

    if (mq_getattr(mq, &attr) == -1) {
        perror("mq_getattr");
        return 0;
    }

    if (attr.mq_curmsgs > 0) {
        printf("Диалог закончен\n");
        return 1;        
    } else {
        return 0;
    }
}

void check_queue(mqd_t mq, const char *queue_name) {
    char buffer[MAX_SIZE];
    struct mq_attr attr;

    if (mq_getattr(mq, &attr) == -1) {
        perror("mq_getattr");
        return;
    }

    if (attr.mq_curmsgs >= 0) {
       ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);

        if (bytes_read >= 0) {
            printf("Получил: %s\n", buffer);
        } else {
            return;
        }

        printf("Введите сообщение: ");
        fgets(buffer, MAX_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (mq_send(mq, buffer, strlen(buffer) + 1, 1) == -1) {
            perror("mq_send");
            return;
        }
    } else {
        return;
    }
}

int main() {
    mqd_t mq,ex;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; 
    attr.mq_msgsize = MAX_SIZE; 
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0644, &attr);
    ex = mq_open(QUEUE_NAME_EXIT, O_CREAT | O_RDWR, 0644, &attr);

    if (mq == (mqd_t)-1 || ex == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while(1){
        
        if(check_queue_exit(ex,QUEUE_NAME_EXIT)){
            break;
        } 
        
        check_queue(mq,QUEUE_NAME);
    }

    if (mq_close(mq) == -1 ||  mq_close(ex) == -1) {
        perror("mq_close");
        return 1;
    }

    if (mq_unlink(QUEUE_NAME_EXIT) == -1) {
        perror("mq_unlink");
        return 1;
    }

    return 0;
}