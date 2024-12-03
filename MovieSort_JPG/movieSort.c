#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMEMAXLENGTH 50
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
#define MAXDURATION 4
#define MAXAMOUNTOFGENRES 5
#define ACTORSMAXLENGTH 200
#define TIMEMAXLENGTH 4
#define YEARMAXLENGTH 11
#define MULTIPLEGENRESMAXLENGTH 500
#define DURATIONMAXLENGTH 10

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
    // To determine if a movie is a series or not, we will look at if its release date has a "-" in the name after the number
    // This would suggest that a movie is released over the course of more of a year, which is only possible for tv-series
    // We therefore save the year information in a string, which we will later use to determine if a movie is a series or not
    char year[YEARMAXLENGTH];
    // We save all genres in one string to begin with, as the amount of genres varies between the data
    char genres[MULTIPLEGENRESMAXLENGTH];
    char duration[DURATIONMAXLENGTH] = "0";
    movieData firstMovie;
    FILE *pFile = fopen("movies.csv", "r");
    if (pFile == NULL)
    {
        printf("Error opening file\n");
        return 0;
    }
    // %*[^\n]
    fscanf(pFile, "%49[^,], %10[^,], %9[^,], %9[^,],", firstMovie.title, year, firstMovie.ageRating,
           duration);
    // We check if a movie is a series
    firstMovie.isSeries = (year[5] == '-');

    // If there is a valid duration, aka if it not left empty in the dataset, it will be saved
    if (duration[0] != '0')
    {
        sscanf(duration, "%i", &firstMovie.duration);
    }

    // Before we continue saving data we need to determine if there are multiple genres or not
    // If there are more than one, the genres will be listed within this "|" symbol
    // If there is just one, the genre data will just be between comma like the rest of the data
    char multipleGenreCheck[GENREMAXLENGTH];
    fscanf(pFile, "%c", multipleGenreCheck);
    if (multipleGenreCheck[0] == '|')
    {
        fscanf(pFile, "%499[^|]|,", genres);
        // Since we save all the genres in one string, we have to split each genre up into its own string
        // First we determine the amount of genres, which sscanf will return
        int amountOfGenres = sscanf(genres, "%100[^,], %100[^,], %100[^,], %100[^,], %100[^|]", firstMovie.genre[0],
                                    firstMovie.genre[1], firstMovie.genre[2], firstMovie.genre[3], firstMovie.genre[4]);
        // strtok will "tokenize" the genres string via the comma operator, meaning it will read up to comma, which is
        // when a genre ends in the string
        char *token = strtok(genres, ",");
        for (int i = 0; i < amountOfGenres; i++)
        {
            strcpy(token, firstMovie.genre[i]);
            firstMovie.genre[i][GENREMAXLENGTH - 1] = '\0';
            token = strtok(NULL, ",");
        }
    }
    else
    {
        fscanf(pFile, "%99[^,],", firstMovie.genre[0]);
        strcat(multipleGenreCheck, firstMovie.genre[0]);
        strcpy(firstMovie.genre[0], multipleGenreCheck);
    }

    fscanf(pFile, "%lf,|%*[^|]|", &firstMovie.rating);

    printf("title: %s, year: %s, age rating: %s, duration: %i, genre 1: %s, genre 2: %s, genre 3: %s, genre 4: %s, genre 5: %s, isSeries: %i, rating: %.1lf\n", firstMovie.title,
           year, firstMovie.ageRating, firstMovie.duration, firstMovie.genre[0], firstMovie.genre[1], firstMovie.genre[2], firstMovie.genre[3], firstMovie.genre[4], firstMovie.isSeries, firstMovie.rating);

    return 0;
}