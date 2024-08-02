#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define MAX_LEGTH_CHAR 1024

int main() {
  int sockfd;
  int clieln, n;
  char buffer[MAX_LEGTH_CHAR];
  struct sockaddr_in servaddr, cliaddr;

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERVER_PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror(NULL);
    exit(1);
  }
  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror(NULL);
    close(sockfd);
    exit(1);
  }

  while (1) {
    clieln = sizeof(cliaddr);

    if ((n = recvfrom(sockfd, buffer, 999, 0, (struct sockaddr *)&cliaddr,&clieln)) < 0) {
      perror(NULL);
      close(sockfd);
      exit(1);
    }
    printf("%s\n", buffer);
    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr,clieln) < 0) {
      perror(NULL);
      close(sockfd);
      exit(1);
    }
  }
  sleep(1);
  return 0;
}