#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void *factorial(void *arg);

int main(int argc, char *argv[])
{
    srand(time(0));

    pthread_t id1;
    pthread_t id2;
    int val1 = atoi(argv[1]);
    int val2 = atoi(argv[2]);
    long long int *res1, *res2;
    pthread_create(&id1, NULL, &factorial, &val1);
    pthread_create(&id2, NULL, &factorial, &val2);
    pthread_join(id1, (void *)&res1);
    pthread_join(id2, (void *)&res2);
    printf("Factorial de: %d es: %lld \n", val1, res1);
    printf("Factorial de: %d es: %lld \n", val2, res2);
    return 0;
}

void *factorial(void *arg)
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
