#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH_IP 128


uint32_t ConvertToInt32(char *ip)
{
    uint32_t address = 0;
    char *ptr;
    for (int i = 3; i > -1; i--)
    {
        uint8_t octet = strtoul(ip, &ptr, 10);
        ip = ++ptr;
        address |= octet << (8 * i);
    }
    return address;
}

uint32_t ConSubnet(uint32_t ip, uint32_t mask)
{
    return (ip & mask);
}

int CompareSubnets(uint32_t ip_subnet1, uint32_t ip_subnet2)
{
    return ip_subnet1 == ip_subnet2;
}

int Start(char *ip_gateway, char *ip_mask, int numbers_packet)
{
    int counter = 0;
    uint32_t mask = ConvertToInt32(ip_mask);
    uint32_t subnet = ConSubnet(ConvertToInt32(ip_gateway), mask);

    for (int i = 0; i < numbers_packet; i++)
    {
        uint32_t ip_destination = rand() << 16;
        if (CompareSubnets(subnet, ConSubnet(ip_destination, mask))) counter++;
    }

    return counter;
}


int main(int argc, char *argv[]){
    srand(time(NULL));

    if (argc != 4) {
        printf("Неправильно введены аргументы: <IP_адресс> <маска> <количество пакетов>\n");
        return 1;
    }

    int numberPackage = strtoul(argv[3], NULL, 10);

    if (numberPackage != 0)
    {
        int subnetCount = Start(argv[1], argv[2], numberPackage);
        int differentSubnetCount = numberPackage - subnetCount;
        printf("Количество адресов подсети шлюза: %d\n", subnetCount);
        printf("Количество адресов других сетей: %d\n", differentSubnetCount);
        printf("Процентов: %.1f\%\n", (float)subnetCount *100 / numberPackage);
    }
    
    return 0;
}