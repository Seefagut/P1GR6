#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
    
int main(void){

    time_t time1, time2;

    time(&time1);
    int time = time1 - (time1 % 31556926);
    printf ("%d", time);
    return 0;
}