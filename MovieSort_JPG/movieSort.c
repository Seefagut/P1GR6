#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMEMAXLENGTH 50
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
#define MAXDURATION 4
#define MAXAMOUNTOFGENRES 5
#define ACTORSMAXLENGTH 200
#define TIMEMAXLENGTH 3
#define YEARMAXLENGTH 5
#define MULTIPLEGENRESMAXLENGTH 500

typedef struct movieData
{
    char title[NAMEMAXLENGTH];
    int isSeries;
    char ageRating[AGERATINGMAXLENGTH];
    int duration;
    char genre[MAXAMOUNTOFGENRES][GENREMAXLENGTH];
    double rating;
    char actors[ACTORSMAXLENGTH];
} movieData;

int main(void)
{

    char year[YEARMAXLENGTH];
    char genres[MULTIPLEGENRESMAXLENGTH];
    movieData firstMovie;
    FILE *pFile = fopen("movies.csv", "r");
    if (pFile == NULL)
    {
        printf("Error opening file\n");
        return 0;
    }
    fscanf(pFile, "%50[^,], (%10[^)]), %10[^,], %i %*[^|]| %500[^|]", &firstMovie.title, &year, &firstMovie.ageRating, &firstMovie.duration, &genres);

    int amountOfGenres = sscanf(genres, "%100[^,], %100[^,], %100[^,], %100[^,], %100[^|]", &firstMovie.genre[0], &firstMovie.genre[1],
                                &firstMovie.genre[2], &firstMovie.genre[3], &firstMovie.genre[4]);

    char* token = strtok(genres, ",");
    for (int i = 0; i < amountOfGenres; i++)
    {
        strcpy(token, firstMovie.genre[i]);
        token = strtok(NULL, ",");
    }

    printf("title: %s, year: %s, age rating: %s, duration: %i, genre 1: %s, genre 2: %s, genre 3: %s, amount: %i\n", firstMovie.title, year, firstMovie.ageRating, firstMovie.duration,firstMovie.genre[0], firstMovie.genre[1], firstMovie.genre[2], amountOfGenres);

    return 0;
}