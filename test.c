#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
    
int main(void){

    time_t time1, time2;

    time(&time1);
    Sleep(1000);
    time(&time2);
    printf ("%.2f", difftime(time2, time1));    
    return 0;
}