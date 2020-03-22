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
    int success;
    clock_t time1 = clock();
    success = non_parallel();
    clock_t time2 = clock();
    if(success == 1) { printf("Error in non_parallel()\n"); return 0; }
    printf("\ntime for non-parallel variant: %ld\n", (time2 - time1));

    time1 = clock();
    success = parallel();
    time2 = clock();
    if(success == 1) { printf("Error in parallel()\n"); return 0; }
    printf("\ntime for parallel variant: %ld\n", (time2 - time1));

    return 0;
}