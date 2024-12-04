#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMEMAXLENGTH 50
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
#define MAXDURATION 4
#define MAXAMOUNTOFGENRES 5
#define ACTORSMAXLENGTH 200
#define MOVIESTOTAL 20
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

// Prototypes
void saveMovieData();

int main(void)
{
    printf("Not overflow!\n");
    movieData movies[MOVIESTOTAL];
    movieData series[MOVIESTOTAL];

    saveMovieData();

    return 0;
}

void saveMovieData()
{
    movieData moviesPreSort[MOVIESTOTAL];

    // To determine if a movie is a series or not, we will look at if its release date has a "-" in the name after the number
    // This would suggest that a movie is released over the course of more than a year, which is only possible for tv-series
    // We therefore save the year information in a string, which we will later use to determine if a movie is a series or not
    char year[YEARMAXLENGTH];
    // We save all genres in one string to begin with, as the amount of genres varies between the data
    char genres[MULTIPLEGENRESMAXLENGTH];
    char duration[DURATIONMAXLENGTH] = "0";
    FILE *pFile = fopen("movies.csv", "r");

    if (pFile == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < MOVIESTOTAL; i++)
    {
        fscanf(pFile, " %49[^,], %10[^,], %9[^,], %9[^,],", moviesPreSort[i].title, year, moviesPreSort[i].ageRating,
               duration);
        // We check if a movie is a series
        moviesPreSort[i].isSeries = (year[5] == '-');

        // If there is a valid duration, aka if it not left empty in the dataset, it will be saved
        if (duration[0] != '0')
        {
            sscanf(duration, "%i", &moviesPreSort[i].duration);
        }

        // Before we continue saving data we need to determine if there are multiple genres or not
        // If there are more than one, the genres will be listed within this "|" symbol
        // If there is just one, the genre data will just be between comma like the rest of the data
        char multipleGenreCheck[GENREMAXLENGTH];
        fscanf(pFile, " %c", multipleGenreCheck);
        // As we need to save a value on all 5 genre variables of the struct, we will start by manually saving a value
        // indicating that it is empty
        for (int l = 0; l < MAXAMOUNTOFGENRES; l++)
        {
            strcpy(moviesPreSort[i].genre[l], "0");
        }

        if (multipleGenreCheck[0] == '|')
        {
            fscanf(pFile, " %499[^|]|,", genres);
            // We save each genre
            sscanf(genres, " %100[^,], %100[^,], %100[^,], %100[^,], %100[^|]", moviesPreSort[i].genre[0],
                                        moviesPreSort[i].genre[1], moviesPreSort[i].genre[2], moviesPreSort[i].genre[3], moviesPreSort[i].genre[4]);
        }
        else
        {
            fscanf(pFile, " %99[^,],", moviesPreSort[i].genre[0]);
            strcat(multipleGenreCheck, moviesPreSort[i].genre[0]);
            strcpy(moviesPreSort[i].genre[0], multipleGenreCheck);
        }

        // In the same way we check if there are multiple genres, we will check if a rating is listed
        // If there is no rating, the movie will be discarded, as rating is a criteria we use when recommending later
        char ratingCheck[4];
        fscanf(pFile, " %c", ratingCheck);
        if (ratingCheck[0] == ',')
        {
            continue;
        }
        fscanf(pFile, " %2[^,]", &ratingCheck[1]);
        sscanf(ratingCheck, "%lf", &moviesPreSort[i].rating);

        // The last data we need to scan from the dataset is actors
        // fscanf(pFile, "%*[^[]")

        printf("title %i: %s, age: %s, dur: %i, g1: %s, g2: %s, g3: %s, g4: %s, g5: %s, isSer: %i, rati: %.1lf\n", i, moviesPreSort[i].title,
               moviesPreSort[i].ageRating, moviesPreSort[i].duration, moviesPreSort[i].genre[0], moviesPreSort[i].genre[1], moviesPreSort[i].genre[2], moviesPreSort[i].genre[3], moviesPreSort[i].genre[4], moviesPreSort[i].isSeries, moviesPreSort[i].rating);

        fscanf(pFile, " %*[^\n]");
    }
    fclose(pFile);

    return;
}