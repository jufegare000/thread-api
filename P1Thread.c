#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void* factorial(void* arg);

int main(int argc, char *argv[])
{
    srand(time(0));

    pthread_t id1;
    pthread_t id2;
    int *val1 = atoi(argv[1]);
    int *val2 = atoi(argv[2]);
    pthread_create(&id1, NULL, &factorial, &val1);
    pthread_create(&id2, NULL, &factorial, &val2);
    //printf("El factorial de %s es %d\n", argv[1], factorial(atoi(argv[1])));
    //printf("El factorial de %s es %d\n", argv[2], factorial(atoi(argv[2])));

    return 0;
}

void* factorial(void* arg)
{
    int n = *((int *)arg);
    int resultado = 1;
    int num;
    for (num = 2; num <= n; num++)
    {
        resultado = resultado * num;
        printf("Factorial de %d, resultado parcial %d\n", n, resultado);
        sleep(random() % 3);
    }
    return resultado;
}
