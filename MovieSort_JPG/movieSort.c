#include <stdio.h>
#include <stdlib.h>

#define NAMEMAXLENTGH 50
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
#define ACTORSMAXLENTGH 200


struct movieData
{
    char title[NAMEMAXLENTGH];
    int year;
    int isSeries;
    char ageRating[AGERATINGMAXLENGTH];
    int duration;
    char genre[GENREMAXLENGTH];
    double rating;
    char actors[ACTORSMAXLENTGH];
};
typedef struct movieData movieData;


int main(void)
{
    movieData firstMovie;
    FILE *pFile = fopen("movies.csv", "r");
    fscanf(pFile, "%[^,],%[^,]", &firstMovie.title, &firstMovie.year);
    printf("title: %s, year: %i", firstMovie.title, firstMovie.year);


    return 0;
}