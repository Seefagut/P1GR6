#include <stdio.h>
#include <stdlib.h>

#define NAMEMAXLENTGH 50
#define YEARMAXLENTGH 10
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
#define MAXDURATION 4
#define MAXAMOUNTOFGENRES 5
#define ACTORSMAXLENTGH 200


struct movieData
{
    char title[NAMEMAXLENTGH];
    char year[YEARMAXLENTGH];
    int isSeries;
    char ageRating[AGERATINGMAXLENGTH];
    char duration[MAXDURATION];
    char genre[GENREMAXLENGTH][MAXAMOUNTOFGENRES];
    double rating;
    char actors[ACTORSMAXLENTGH];
};
typedef struct movieData movieData;


int main(void)
{
    movieData firstMovie;
    FILE *pFile = fopen("movies.csv", "r");
    fscanf(pFile, "%[^,],%[^,], %[^,], %[^ ], min, ", &firstMovie.title, &firstMovie.year, &firstMovie.ageRating, &firstMovie.duration);
    printf("title: %s, year: %s, agerating: %s, duration: %s", firstMovie.title, firstMovie.year, firstMovie.ageRating, firstMovie.duration);


    return 0;
}