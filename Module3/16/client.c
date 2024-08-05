#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(const char *msg) {
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[]) {
  int my_sock, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buff[1024];
  printf("TCP DEMO CLIENT\n");
  if (argc < 3) {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }

  portno = atoi(argv[2]);

  my_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (my_sock < 0) error("ERROR opening socket");

  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }

  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);

  serv_addr.sin_port = htons(portno);

  if (connect(my_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");

  while ((n = recv(my_sock, &buff[0], sizeof(buff) - 1, 0)) > 0) {
    buff[n] = '\0';

    printf("S=>C:%s", buff);

    printf("S<=C:");
    fgets(&buff[0], sizeof(buff) - 1, stdin);
    // buff[sizeof(buff)  - 1] = '\0';
    if (!strcmp(&buff[0], "quit\n")) {
      printf("Exit...");
      close(my_sock);
      return 0;
    }
    if (!strcmp(&buff[0], "f\n")) {
      FILE *fp = fopen("file_to_send.txt", "rb");
      while (1) {
        size_t bytes_read = fread(buff, sizeof(char), 1024, fp);
        if (bytes_read > 0) {
          send(my_sock, buff, bytes_read, 0);
        }
        if (bytes_read < 1024) break;  
      }

      fclose(fp);
    }
    send(my_sock, &buff[0], strlen(&buff[0]), 0);
  }
  printf("Recv error \n");
  close(my_sock);
  return -1;
}