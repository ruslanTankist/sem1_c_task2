/* Условие ИЗ №2:
Сравните и выведите в консоль время работы последовательного и параллельного 
с использованием нескольких потоков алгоритмов, каждый из которых выделяет в 
динамической памяти числовой массив размером 100 Мб и инициализирует его значениями 
по следующему шаблону: 0, 1, 2, 3, 0, 1, 2, 3, …
*/

#include <stdio.h>
#include <time.h>
#include "functionality.h"

int main()
{   
    int * array;
    clock_t time1 = clock();
    array = non_parallel();
    clock_t time2 = clock();
    if(array == NULL) { 
        printf("Error in non_parallel()\n"); 
        return 0; 
    }
    printf("\ntime for non-parallel variant: %ld\n", (time2 - time1));
    for(int i = 50; i < 60; i++)
        printf("%d\n", array[i]);
    free_array(array);

    time1 = clock();
    array = parallel();
    time2 = clock();
    if(array == NULL) { 
        printf("Error in parallel()\n"); 
        return 0; 
    }
    printf("\ntime for parallel variant: %ld\n", (time2 - time1));
    for(int i = 50; i < 60; i++)
        printf("%d\n", array[i]);
    free_array(array);

    return 0;
}