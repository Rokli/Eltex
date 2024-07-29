#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME "/my_queue"
#define QUEUE_NAME_EXIT "/exit"
#define MAX_SIZE 256

int main() {
    mqd_t mq,ex;
    struct mq_attr attr;
    char buffer[MAX_SIZE];

   
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; 
    attr.mq_msgsize = MAX_SIZE; 
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    ex = mq_open(QUEUE_NAME_EXIT, O_CREAT | O_RDWR, 0644, &attr);

    if (mq == (mqd_t)-1 || ex == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while(1){
        printf("Введите сообщение: ");
        fgets(buffer, MAX_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if(strcmp(buffer,"exit") == 0){
            if (mq_send(ex, buffer, strlen(buffer) + 1, 1) == -1) {
                perror("mq_send");
                break;
            }
            printf("Диалог закончен\n");
            break;
        }

        if (mq_send(mq, buffer, strlen(buffer) + 1, 1) == -1) {
            perror("mq_send");
            break;
        }

        ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);

        if (bytes_read >= 0) {
            printf("Получил: %s\n", buffer);
        } else {
            perror("mq_receive");
            break;
        }
    }

    if (mq_close(mq) == -1 ||  mq_close(ex) == -1) {
        perror("mq_close");
        return 1;
    }

    if (mq_unlink(QUEUE_NAME) == -1 || mq_unlink(QUEUE_NAME_EXIT) == -1) {
        perror("mq_unlink");
        return 1;
    }

    return 0;
}
