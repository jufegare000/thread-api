#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void *factorial(void *arg);

int main(int argc, char *argv[])
{
    srand(time(0));
    pthread_t arrayIds[argc];
    int results[argc];
    for (int i = 0; i < argc; i++)
    {
        pthread_create(&arrayIds[i], NULL, &factorial, atoi(argv[i + 1]));
    }
    for (int j = 0; j < argc; j++)
    {
        pthread_join(arrayIds[j], (void *)&results[j]);
        printf("Factorial de: %d es: %lld con identificador: %d\n",
               atoi(argv[j + 1]),
               results[j],
               arrayIds[j]);
    }

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
