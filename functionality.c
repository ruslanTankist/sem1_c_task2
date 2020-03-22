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
#include "functionality.h"

int non_parallel()
{
    int * array = malloc(REQUIRED_SIZE);
    if( array == 0 ) { printf("malloc() failed\n"); return 1; }
    int array_size = REQUIRED_SIZE / sizeof(int);
    for(int i = 0; i < array_size; i++)
    {
        array[i] = i % 4;
    }
    free(array);
    return 0;
}

int parallel()
{
    int * array = malloc(REQUIRED_SIZE);
    if( array == 0 ) { printf("malloc() failed\n"); return 1; }
    int array_size = REQUIRED_SIZE / sizeof(int);
    int bit_one = 0, bit_two = 0;

    int pid = fork();
    if( pid == -1 ) { printf("fork() failed\n"); return 1; }
    if( pid == 0 )
        bit_one = 1;
    pid = fork();
    if( pid == 0 )
        bit_two = 1;
    
    if(bit_one == 0)
    {
        if(bit_two == 0)
        {
            for(int i = 0; i < array_size; i += 4)
                array[i] = 0;
        }
        else
        {
            for(int i = 1; i < array_size; i += 4)
                array[i] = 1;
            exit(0);
        }   
    }   
    else
    {
        if(bit_two == 0)
        {
            for(int i = 2; i < array_size; i += 4)
                array[i] = 2;
            exit(0);
        }    
        else
        {
            for (int i = 3; i < array_size; i += 4)
                array[i] = 3;
            exit(0);
        }     
    }  
    wait(0);

    free(array);
    return 0;
}