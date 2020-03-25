/* Условие ИЗ №2:
Сравните и выведите в консоль время работы последовательного и параллельного 
с использованием нескольких потоков алгоритмов, каждый из которых выделяет в 
динамической памяти числовой массив размером 100 Мб и инициализирует его значениями 
по следующему шаблону: 0, 1, 2, 3, 0, 1, 2, 3, …
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include "functionality.h"

//----------just one thread/one process work with array
char * non_parallel()
{
    char * array = malloc(REQUIRED_SIZE);
    if( array == 0 ) { return NULL; }
    for(int i = 0; i < REQUIRED_SIZE; i++)
    {
        array[i] = i % 4;
    }
    return array;
}

//----------multithread work with array
typedef struct {
    pthread_mutex_t mutex;
    char * array; //array of int here
    char job_done[4]; //thread job completed flag
} thread_data;

thread_data data = {PTHREAD_MUTEX_INITIALIZER, NULL, {0, 0, 0, 0} };

void * filling_thread(void *arg)
{
    int thread_num = *(int *)arg;
    free(arg);
    for(int i = thread_num; i < REQUIRED_SIZE; i += 4)
    {
        while (1)
        {
            int errflag = pthread_mutex_lock(&data.mutex);
            if(errflag != 0) continue;

            data.array[i] = i % 4;

            errflag = pthread_mutex_unlock(&data.mutex);
            if(errflag != 0) continue;
            break;
        }
    }
    data.job_done[thread_num] = 1;
    return NULL;
}

char * parallel()
{
    data.array = malloc(REQUIRED_SIZE);
    if( data.array == 0 ) { return NULL; }

    pthread_t thread_id[4];

    for (int i = 0; i < 4; i++)
    {
        int * arg = (int *)malloc(sizeof(int));
        *arg = i;
        
        pthread_create(&thread_id[i], NULL, filling_thread, arg);
    }

    //check if array is filled;
    while(1)
    {
        if(data.job_done[0] == 1 && 
            data.job_done[1] == 1 && 
            data.job_done[2] == 1 && 
            data.job_done[3] == 1)
        break;
    }
    
    for (int i = 0; i < 4; i++)
        pthread_join(thread_id[i], NULL);

    return data.array;
}

void free_array(char * arr)
{
    if(arr != NULL)
        free(arr);
}