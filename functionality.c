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

#define THREAD_NUMBER 4

//----------just one thread/one process work with array
char * non_parallel()
{
    char * array = malloc(REQUIRED_SIZE);
    if( array == NULL ) { 
        return NULL;
    }

    for(int i = 0; i < REQUIRED_SIZE; i++)
    {
        array[i] = i % 4;
    }
    return array;
}

//----------
typedef struct {
    char * array;
    int thread_num;
} data_struct;

void * filling_thread(void *arg)
{
    data_struct data = *(data_struct *)arg;
    for(int i = data.thread_num; i < REQUIRED_SIZE; i += THREAD_NUMBER)
    {
        data.array[i] = i % 4;
    }
    return NULL;
}

char * parallel()
{
    char * arr = malloc(REQUIRED_SIZE);
    if( arr == 0 ) { 
        return NULL; 
    }

    data_struct data[THREAD_NUMBER];
    
    pthread_t thread_id[THREAD_NUMBER];

    for (int i = 0; i < THREAD_NUMBER; i++)
    {   
        data[i].array = arr;
        data[i].thread_num = i;
        
        pthread_create(&thread_id[i], NULL, filling_thread, &data[i]);
    }

    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
    return arr;
}

void free_array(char * arr)
{
    free(arr);
}