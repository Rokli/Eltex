#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define MAX_LEGTH_CHAR 1024

int sockaddr_in_cmp(const struct sockaddr_in *a, const struct sockaddr_in *b) {
  int result = 0;

  if (a->sin_family != b->sin_family) {
    return -1;
  }

  if (memcmp(&a->sin_addr, &b->sin_addr, sizeof(a->sin_addr)) != 0) {
    return -1;
  }

  if (ntohs(a->sin_port) != ntohs(b->sin_port)) {
    return -1;
  }

  return 0;
}

int main() {
  int sockfd;
  int clieln, n;
  char buffer[MAX_LEGTH_CHAR];
  struct sockaddr_in servaddr, cliaddr, cliaddr_first, cliaddr_second;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0);

  if (sockfd < 0) {
    perror(NULL);
    exit(1);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERVER_PORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  memset(&cliaddr_first, 0, sizeof(cliaddr_first));
  cliaddr_first.sin_family = AF_INET;
  cliaddr_first.sin_port = htons(20);

  memset(&cliaddr_second, 0, sizeof(cliaddr_second));
  cliaddr_second.sin_family = AF_INET;
  cliaddr_second.sin_port = htons(30);

  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror(NULL);
    close(sockfd);
    exit(1);
  }

  for (;;) {
    clieln = sizeof(cliaddr);

    if ((n = recvfrom(sockfd, buffer, MAX_LEGTH_CHAR, 0,
                      (struct sockaddr *)&cliaddr, &clieln)) < 0) {
      perror(NULL);
      exit(1);
    }
    printf("%s\n", buffer);
    clieln = sizeof(cliaddr_first);
    if (sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&cliaddr_first, sizeof(cliaddr_first)) < 0) {
      perror(NULL);
      exit(1);
    }
    clieln = sizeof(cliaddr_second);
    if (sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&cliaddr_second,
               sizeof(cliaddr_second)) < 0) {
      perror(NULL);
      exit(1);
    }
    memset(&cliaddr, 0, sizeof(cliaddr));
    memset(buffer, 0, sizeof(buffer));
  }

  return 0;
}