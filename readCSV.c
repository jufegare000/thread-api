#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

typedef struct arr
{
    int n;
    float *data;
} my_array;

void *read(char *filename, my_array *arr);
void add_item(my_array *arr, float item);
float calculate_mid(my_array *arr);
float get_item(my_array *arr, int index);
float calculateSquareOfIminusMid(float xi, float mid);
float calculate_standard_deviation(my_array *arr);
float calculate_product(int length, float other);
float calculate_partial(my_array *arr, float mid);

void main(int argc, char *argv[])
{

    my_array arr = {};
    read(argv[1], &arr);

    float stand_dev = calculate_standard_deviation(&arr);

    printf("%f", stand_dev);
    return 0;
}

float calculate_standard_deviation(my_array *arr)
{
    float mid = 0;
    pthread_t id, id2;
    pthread_create(&id, NULL, calculate_mid, arr);

    pthread_join(id, NULL);
    float partial = calculate_partial(arr, mid);
    float patialResult = calculate_product(arr->n, partial);
    return sqrt(patialResult);
}

float calculate_product(int length, float other)
{
    float inverse = 1 / ((float)length - 1.0);
    return inverse * other;
}

float calculateSquareOfIminusMid(float xi, float mid)
{
    float minus = xi - mid;
    return minus * minus;
}

void *read(char *filename, my_array *arr)
{
    FILE *fp = fopen(filename, "r");

    if (!fp)
    {
        printf("Can't open file\n");
        return -1;
    }

    char buf[1024];
    int row_count = 0;
    int field_count = 0;
    while (fgets(buf, 1024, fp))
    {
        field_count = 0;
        row_count++;

        if (row_count == 1)
        {
            continue;
        }

        char *field = strtok(buf, ",");
        while (field)
        {
            if (field_count == 1)
            {
                printf("Note:\t");
                printf("%s\n", field);
                float currentValue = atof(field);
                add_item(arr, currentValue);
            }

            field = strtok(NULL, ",");
            field_count++;
        }
        printf("\n");
    }

    fclose(fp);

    return 0;
}

void add_item(my_array *arr, float item)
{
    void *tmp;
    if (arr->n == 0)
    {
        tmp = malloc(sizeof(float));
        arr->n = 1;
        arr->data = tmp;
    }
    else
    {
        arr->n = arr->n + 1;
        tmp = realloc(arr->data, arr->n * sizeof(float));
        if (tmp != NULL)
        {
            arr->data = tmp;
        }
    }
    arr->data[arr->n - 1] = item;
}

float calculate_mid(my_array *arr)
{
    float mid = 0;
    for (int i = 0; i < arr->n; i++)
    {
        mid += get_item(arr, i);
    }
    return mid / arr->n;
}

float get_item(my_array *arr, int index)
{
    return arr->data[index];
}

float calculate_partial(my_array *arr, float mid)
{
    float partial = 0;
    for (int i = 0; i < arr->n; i++)
    {
        partial += calculateSquareOfIminusMid(get_item(arr, i), mid);
    }
    return partial;
}