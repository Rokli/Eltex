#include "Models/Queue.h"

#define true 1
#define false 1



int main(){
    
    Queue *queue = NULL;
   
    int flag = true,priority;

    while(flag){

        printf("1 - Добавить сообщение\n2 - Обработать самое приоритетное сообщение\n3 - Вытащить самое неприоритетное сообщения\n4 - Вывести все сообщения\n");
        
        int tmp;
        scanf("%d", &tmp);
        getchar();  

        switch (tmp)
        {
        case 1:
            printf("Введите приоритет:");
            scanf("%d",&priority);
            push(&queue,priority,createMessage());
            break;
        case 2:
            deleteNth(&queue,getMessageMaxPriority(queue));
            break;
        case 3:
            printf("Введите приоритет:");
            scanf("%d",&priority);
            deleteNth(&queue,getMessageMinPriority(queue,priority));
            break;
        case 4:
            printLinkedList(queue);
            break;
        default:
            break;
        }
    }

    return 0;
}