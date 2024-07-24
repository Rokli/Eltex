#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Ошибка: Необходимо передать хотя бы одно число.\n");
        return 1;
    }

    int max = atoi(argv[1]);
    for (int i = 2; i < argc; i++) {
        int value = atoi(argv[i]);
        if (value > max) {
            max = value;
        }
    }

    printf("Максимальное значение: %d\n", max);
    return 0;
}
