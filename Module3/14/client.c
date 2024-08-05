#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

#define SERVER_PORT 8080
#define MAX_LENGTH_CHAR 1024

int sockfd;

void cleanup(int signum) {
    close(sockfd);
    exit(0);
}

int main(int argc, char **argv) {
    int n;
    char sendline[MAX_LENGTH_CHAR], recvline[MAX_LENGTH_CHAR];
    struct sockaddr_in servaddr, cliaddr;

    if (argc != 3) {
        printf("Аргументы: client.out <IP address> <Port>\n");
        exit(1);
    }

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    memset(&cliaddr, 0, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(atoi(argv[2]));
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0) {
        perror("bind error");
        close(sockfd);
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);

    if (inet_aton(argv[1], &servaddr.sin_addr) == 0) {
        printf("Invalid IP address\n");
        close(sockfd);
        exit(1);
    }

    signal(SIGINT, cleanup);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork error");
        close(sockfd);
        return 1;
    }

    if (pid == 0) { 
        for (;;) {
            if (fgets(sendline, sizeof(sendline), stdin) == NULL) {
                perror("fgets error");
                exit(1);
            }

            if (sendto(sockfd, sendline, strlen(sendline) + 1, 0,
                       (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
                perror("sendto error");
                exit(1);
            }
        }
    } else { 
        for (;;) {
            if ((n = recvfrom(sockfd, recvline, sizeof(recvline), 0,
                              (struct sockaddr *)NULL, NULL)) < 0) {
                perror("recvfrom error");
                exit(1);
            }
            printf("\nReceived: %s", recvline); 
            memset(recvline, 0, sizeof(recvline));
        }
    }

    close(sockfd); 
    return 0;
}
