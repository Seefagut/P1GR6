#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
    
int main(void){

    time_t time1;
    struct tm stoptimetm;
    int hr, minutes;
    int diff = 0;

    time(&time1);
    struct tm *starttime = localtime(&time1);
    stoptimetm = *starttime;

    printf("Indtast stoptid (Ex. 18:40):\n");
    scanf("%d:%d", &hr, &minutes);

    stoptimetm.tm_hour = hr;
    stoptimetm.tm_min = minutes;
    stoptimetm.tm_sec = 0;

    time_t stoptime = mktime(&stoptimetm);

    if (difftime(stoptime, time1) <= 0){
    diff = difftime(stoptime, time1) + 86400;       
    } else {
    diff = difftime(stoptime, time1);
    }

    printf("Forskellen er %d sekunder", diff);

    return 0;
}