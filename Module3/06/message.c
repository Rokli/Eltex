#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 100

typedef struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
}msg_buffer;

int main() {
    key_t key = ftok("chat", 65); 
    int msgid = msgget(key, 0666 | IPC_CREAT); 

    msg_buffer message;

    while (1) {
        msgrcv(msgid, &message, sizeof(message), 0, 0); 

        if (message.msg_type == 4) { 
            printf("Диалог закончен.\n");
            break;
        }

        printf("Получено: %s\n", message.msg_text);
        
        printf("Введите сообщение: ");
        fgets(message.msg_text, MSG_SIZE, stdin);

        message.msg_text[strcspn(message.msg_text, "\n")] = 0; 
        message.msg_type = 2;
        msgsnd(msgid, &message, sizeof(message), 0); 
    }

    msgctl(msgid, IPC_RMID, NULL); 
    return 0;
}
