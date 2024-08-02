#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

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

int myfunc(int a, int b) { return a + b; }

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

    struct hostent *hst;
    hst = gethostbyaddr((char *)&cli_addr.sin_addr, 4, AF_INET);
    printf("+%s [%s] new connect!\n", (hst) ? hst->h_name : "Unknown host",
           (char *)inet_ntoa(cli_addr.sin_addr));
    printusers();
    pid = fork();
    if (pid < 0) error("ERROR on fork");
    if (pid == 0) {
      close(sockfd);
      dostuff(newsockfd);
      exit(0);
    } else
      close(newsockfd);
  }
  close(sockfd);
  return 0;
}

void dostuff(int sock) {
  int bytes_recv;  // размер принятого сообщения
  int a, b;        // переменные для myfunc
  char buff[20 * 1024];
  #define str1 "Enter 1 parameter\r\n"
  #define str2 "Enter 2 parameter\r\n"
  // отправляем клиенту сообщение
  write(sock, str1, sizeof(str1));
  // обработка первого параметра
  bytes_recv = read(sock, &buff[0], sizeof(buff));
  if (bytes_recv < 0) error("ERROR reading from socket");
  a = atoi(buff);  // преобразование первого параметра в int
  // отправляем клиенту сообщение
  write(sock, str2, sizeof(str2));
  bytes_recv = read(sock, &buff[0], sizeof(buff));
  if (bytes_recv < 0) error("ERROR reading from socket");
  b = atoi(buff);  // преобразование второго параметра в int
  a = myfunc(a, b);  // вызов пользовательской функции
  snprintf(buff, strlen(buff), "%d", a);  // преобразование результата в строку
  buff[strlen(buff)] = '\n';  // добавление к сообщению символа конца строки
  // отправляем клиенту результат
  write(sock, &buff[0], sizeof(buff));
  nclients--;  // уменьшаем счетчик активных клиентов
  printf("-disconnect\n");
  printusers();
  return;
}