#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CHAR 32
#define str1 "Enter 1 parameter\r\n"
#define str2 "Enter 2 parameter\r\n"
#define str3 "Enter action\r\n"

void dostuff(int);

void error(const char *msg) {
  perror(msg);
  exit(1);
}

int nclients = 0;

void printusers() {
  if (nclients) {
    printf("%d user on-line\n", nclients);
  } else {
    printf("No User on line\n");
  }
}

int GetAction(char action[]) {
  if (strcmp(action, "+") == 0) return 1;
  if (strcmp(action, "-") == 0) return 2;
  if (strcmp(action, "*") == 0) return 3;
  if (strcmp(action, "/") == 0) return 4;
  if (strcmp(action, "f") == 0) return 5;
}

int summ(int a, int b) { return a + b; }

int difference(int a, int b) { return a - b; }

int multiplication(int a, int b) { return a * b; }

int division(int a, int b) { return a / b; }

int main(int argc, char *argv[]) {
  char buff[1024];
  int sockfd, newsockfd;
  int portno;
  int pid;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  printf("TCP SERVER DEMO\n");

  if (argc < 2) {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) error("ERROR opening socket");

  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  listen(sockfd, 5);
  clilen = sizeof(cli_addr);

  while (1) {
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) error("ERROR on accept");
    nclients++;

    struct hostent *hst = gethostbyaddr((char *)&cli_addr.sin_addr, 4, AF_INET);
    printf("+%s [%s] new connect!\n", (hst) ? hst->h_name : "Unknown host",
           (char *)inet_ntoa(cli_addr.sin_addr));
    printusers();

    pid = fork();
    if (pid < 0) error("ERROR on fork");
    if (pid == 0) {
      close(sockfd);
      dostuff(newsockfd);
      exit(0);
    } else {
      close(newsockfd);
    }
  }
  close(sockfd);
  return 0;
}
void dostuff(int sock) {
  int bytes_recv;
  int a, b;
  char action[MAX_CHAR];
  char buff[1024];

  write(sock, str1, strlen(str1));

  bytes_recv = read(sock, &buff[0], sizeof(buff));
  if (bytes_recv < 0) error("ERROR reading from socket");
  a = atoi(buff);

  write(sock, str2, strlen(str2));
  bytes_recv = read(sock, &buff[0], sizeof(buff));
  if (bytes_recv < 0) error("ERROR reading from socket");
  b = atoi(buff);

  write(sock, str3, strlen(str3));
  bytes_recv = read(sock, &action, sizeof(action));
  if (bytes_recv < 0) error("ERROR reading from socket");
  action[bytes_recv - 1] = '\0';

  int act = GetAction(action);

  switch (act) {
    case 1:
      a = summ(a, b);
      snprintf(buff, sizeof(buff), "%d", a);
      buff[strlen(buff)] = '\n';
      write(sock, &buff[0], strlen(buff) + 1);
      break;
    case 2:
      a = difference(a, b);
      snprintf(buff, sizeof(buff), "%d", a);
      buff[strlen(buff)] = '\n';
      write(sock, &buff[0], strlen(buff) + 1);
      break;
    case 3:
      a = multiplication(a, b);
      snprintf(buff, sizeof(buff), "%d", a);
      buff[strlen(buff)] = '\n';
      write(sock, &buff[0], strlen(buff) + 1);
      break;
    case 4:
      a = division(a, b);
      snprintf(buff, sizeof(buff), "%d", a);
      buff[strlen(buff)] = '\n';
      write(sock, &buff[0], strlen(buff) + 1);
      break;
    case 5:
      FILE *fp = fopen("file_to_server.txt", "wb");
      while ((bytes_recv = recv(sock, buff, sizeof(buff), 0)) > 0) {
        fwrite(buff, sizeof(char), bytes_recv, fp);
      }
      fclose(fp);
      break;
    default:
      break;
  }
  write(sock, &buff[0], strlen(buff) + 1);
  nclients--;
  printf("-disconnect\n");
  printusers();
  return;
}