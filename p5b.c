#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

typedef  struct arr
{
    int n;
    float *data;
} my_array;

void* get_vector_from_file(char *file_name, my_array *arr);
void add_item(my_array *arr, float item);
float get_item(my_array *arr, int index);
void print_values(my_array *arr);
void free_arr(my_array *arr);
void sum_between(my_array *arr, int init, int end, float *sum);


int main(int argc, char *argv[])
{
   my_array arr={};
   get_vector_from_file(argv[1],&arr);
   float sum1,sum2=0;
   int mitad=(int) arr.n/2;
   sum_between(&arr,0,mitad,&sum1);
   sum_between(&arr,mitad,arr.n,&sum2);
   print_values(&arr);
   printf("numero de items: %d \n",arr.n);
   printf("mitad: %f \n",mitad);
   printf("resultado suma primer mitad: %f \n",sum1);
   printf("resultado suma segunda mitad: %f \n",sum2);
   printf("resultado total: %f \n",(sum2+sum1));
   free_arr(&arr);
   return EXIT_SUCCESS;
}

void* get_vector_from_file(char *file_name, my_array *arr){
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  float sum=0;
  ssize_t line_size;
  FILE *fp = fopen(file_name, "r");
  if (!fp)
  {
    fprintf(stderr, "Error abriendo el archivo '%s'\n", file_name);
    return NULL;
  }
  line_size = getline(&line_buf, &line_buf_size, fp);
  while (line_size >= 0)
  {
    line_count++;
    float new_value=atof(line_buf);;
    add_item(arr,new_value);
    line_size = getline(&line_buf, &line_buf_size, fp);
  }
  printf("Resultado suma: %f \n",sum);
  free(line_buf);
  line_buf = NULL;
  fclose(fp);
}

void add_item(my_array *arr, float item){
    void* tmp;
    if(arr->n==0){
        tmp = malloc(sizeof(float));
        arr->n=1;
        arr->data=tmp;
    }
    else
    {
        arr->n=arr->n+1;
        tmp = realloc(arr->data, arr->n*sizeof(float));
        if (tmp != NULL) {
            arr->data=tmp;
        }
    }
    
    arr->data[arr->n-1]=item;
}

float get_item(my_array *arr, int index){
    return arr->data[index];
}


void print_values(my_array *arr){
    printf("\n\n ---------------Valores en la lista ------------------\n\n");
    for(int i=0; i<arr->n; i++){
         printf("item:%d = %f\n",i,get_item(arr,i));
    }
}

void free_arr(my_array *arr){
    free(arr->data);
}

void sum_between(my_array *arr, int init, int end, float *sum){
     for(int i=init; i<end; i++){
         *sum=*sum + get_item(arr,i);
    }
}

