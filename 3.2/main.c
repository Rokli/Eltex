#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

#define MAX_LENGTH_IP 128




int main(int argc, char *argv[]){
    if (argc != 4) {
        printf("Usage: gateway_ip subnet_mask num_packets\n");
        return 1;
    }

    return 0;
}