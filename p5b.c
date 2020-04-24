#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>

typedef  struct arr
{
    int n;
    float *data;
} my_array;

typedef  struct args
{
    my_array *arr;
    int init;
    int end;
} my_args;


void* get_vector_from_file(char *file_name, my_array *arr);
void add_item(my_array *arr, float item);
float get_item(my_array *arr, int index);
void print_values(my_array *arr);
void free_arr(my_array *arr);
void *sum_between(void *args);


int main(int argc, char *argv[])
{
   my_array arr={};
   get_vector_from_file(argv[1],&arr);
   
   int mitad=(int) arr.n/2;

    my_args args1={&arr,0,mitad};
    my_args args2={&arr,mitad,arr.n};

    pthread_t id1;
    pthread_t id2;
    float *sum1, *sum2;
    
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);   // Instante inicial

    pthread_create(&id1, NULL, &sum_between, &args1);
    pthread_create(&id2, NULL, &sum_between, &args2);

    pthread_join(id1, (void **)&sum1);
    pthread_join(id2, (void **)&sum2);

    float val1=*sum1;
    float val2=*sum2;

    gettimeofday(&tf, NULL);   // Instante final
    tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
    
    //print_values(&arr);
    printf("numero de items: %d \n",arr.n);
    //printf("mitad: %d \n",mitad);
    //printf("resultado suma primer mitad: %f \n",val1);
    //printf("resultado suma segunda mitad: %f \n",val2);
    printf("resultado suma: %f \n",(val1+val2));
    free_arr(&arr);
    free(sum1);
    free(sum2);
    printf("Total tiempo: %g milisegundos\n", tiempo);
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

void *sum_between(void *arg){
    my_args args=*((my_args *)arg);
    float ret;
    ret=0;
    for(int i=args.init; i<args.end; i++){
         ret=ret + get_item(args.arr,i);
    }
   
    float *returnf = malloc(sizeof(float));
    *returnf = ret;
    return returnf;
}


