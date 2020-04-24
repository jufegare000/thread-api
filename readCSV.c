#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *readCSV();

typedef struct arr
{
    int n;
    float *data;
} my_array;

void add_item(my_array *arr, float item);

void main()
{

    readCSV();
    return 0;
}

void *readCSV()
{
    FILE *fp = fopen("fichero_notas.csv", "r");

    if (!fp)
    {
        printf("Can't open file\n");
        return 0;
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
                int currentValue = field;
            }

            field = strtok(NULL, ",");
            field_count++;
        }
        printf("\n");
    }

    fclose(fp);

    return 0;
}