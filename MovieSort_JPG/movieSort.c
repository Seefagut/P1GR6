#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMEMAXLENGTH 100
#define GENREMAXLENGTH 12
#define AGERATINGMAXLENGTH 10
#define MAXDURATION 4
#define MAXAMOUNTOFGENRES 5
#define ACTORSMAXLENGTH 200
#define MOVIESTOTAL 9957
#define TIMEMAXLENGTH 4
#define YEARMAXLENGTH 13
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

typedef struct pref
{
    char genre1[GENREMAXLENGTH];
    int genrepref1;
    char genre2[GENREMAXLENGTH];
    int genrepref2;
    char genre3[GENREMAXLENGTH];
    int genrepref3;
    int min;
    int max;
    int timetowatch;
} pref;

typedef struct conpref
{
    char seriesName[NAMEMAXLENGTH];
    int timetowatch;
} conpref;

// Prototypes
void saveMovieData(movieData *moviesPreSort);
void discard(movieData *movieToDiscard);
void sortMovies(movieData *moviesPreSort, movieData *movies, movieData *series, char nc, pref newMovie, char *conWatch, movieData *conWatchData);

int main(void)
{
    // temp input
    char nc = 'n';
    pref newMovie = {"Adventure", 2, "yo", 1, "", 3, 2, 8, 10000};
    conpref conWatch = {"Attack on Titan", 10000};
    movieData conWatchData;

    // As a lot of data has to be stored, we will save it using dynamic memory allocation
    movieData *moviesPreSort = malloc(MOVIESTOTAL * sizeof(movieData));

    movieData *movies = malloc(MOVIESTOTAL * sizeof(movieData));
    movieData *series = malloc(MOVIESTOTAL * sizeof(movieData));

    saveMovieData(moviesPreSort);
    sortMovies(moviesPreSort, movies, series, nc, newMovie, conWatch.seriesName, &conWatchData);
    if (nc == 'c' && (strcmp(conWatchData.title, conWatch.seriesName) == 0))
    {
        printf("Name: %s, isSeries: %i, ageRating: %s, duration: %i, g1: %s, g2: %s, g3: %s, g4: %s, g5: %s, rating: %lf\n", conWatchData.title, conWatchData.isSeries, conWatchData.ageRating, conWatchData.duration, conWatchData.genre[0], conWatchData.genre[1], conWatchData.genre[2], conWatchData.genre[3], conWatchData.genre[4], conWatchData.rating);
    }
    else if (nc == 'c')
    {
        printf("Movie/series not found.\n");
    }

    free(moviesPreSort);
    free(movies);
    free(series);

    return 0;
}

void saveMovieData(movieData *moviesPreSort)
{
    // To determine if a movie is a series or not, we will look at if its release date has a "-" in the name after the number
    // This would suggest that a movie is released over the course of more than a year, which is only possible for tv-series
    // We therefore save the year information in a string, which we will later use to determine if a movie is a series or not
    char year[YEARMAXLENGTH];
    // We save all genres in one string to begin with, as the amount of genres varies between the data
    char genres[MULTIPLEGENRESMAXLENGTH];
    FILE *pFile = fopen("movies.csv", "r");

    if (pFile == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < MOVIESTOTAL; i++)
    {
        char stringduration[DURATIONMAXLENGTH] = "0";
        // As all data is split up via comma, any movie with a comma in its name has the name in between "|"
        // We therefore check for this so that those movies' data do not become invalid
        char commaInNameCheck[NAMEMAXLENGTH] = "0";
        fscanf(pFile, " %c", commaInNameCheck);
        if (commaInNameCheck[0] == '|')
        {
            fscanf(pFile, " %99[^|]|,", moviesPreSort[i].title);
        }
        else
        {
            fscanf(pFile, " %99[^,],", moviesPreSort[i].title);
            strcat(commaInNameCheck, moviesPreSort[i].title);
            strcpy(moviesPreSort[i].title, commaInNameCheck);
        }

        fscanf(pFile, " %12[^,], %9[^,], %9[^,],", year, moviesPreSort[i].ageRating,
               stringduration);
        // We check if a movie is a series
        moviesPreSort[i].isSeries = (year[5] == '-');

        // If there is a valid duration we save the data, if not we discard the movie
        if (stringduration[0] != '0')
        {
            sscanf(stringduration, "%i", &moviesPreSort[i].duration);
        }
        else
        {
            fscanf(pFile, " %*[^\n]");
            discard(&moviesPreSort[i]);
            continue;
        }
        // Before we continue saving data we need to determine if there are multiple genres or not
        // If there are more than one, the genres will be listed within this "|" symbol
        // If there is just one, the genre data will just be between comma like the rest of the data
        char multipleGenreCheck[GENREMAXLENGTH] = "0";
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
            sscanf(genres, " %19[^,], %19[^,], %19[^,], %19[^,], %19[^|]", moviesPreSort[i].genre[0],
                   moviesPreSort[i].genre[1], moviesPreSort[i].genre[2], moviesPreSort[i].genre[3], moviesPreSort[i].genre[4]);
        }
        else if (multipleGenreCheck[0] != ',')
        {
            fscanf(pFile, "%99[^,],", moviesPreSort[i].genre[0]);
            strcat(multipleGenreCheck, moviesPreSort[i].genre[0]);
            strcpy(moviesPreSort[i].genre[0], multipleGenreCheck);
        }

        // In the same way we check if there are multiple genres, we will check if a rating is listed
        // If there is no rating, the movie will be discarded, as rating is a criteria we use when recommending later
        char ratingCheck[4];
        fscanf(pFile, " %c", ratingCheck);
        if (ratingCheck[0] == ',')
        {
            fscanf(pFile, " %*[^\n]");
            discard(&moviesPreSort[i]);
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

void discard(movieData *movieToDiscard)
{
    // By setting the title of a movie to "0" we can deem it as discarded and ignore it later when recommending movies
    strcpy(movieToDiscard->title, "0");
}

void sortMovies(movieData *moviesPreSort, movieData *movies, movieData *series, char nc, pref newMovie, char *conWatch, movieData *conWatchData)
{
    if (nc == 'n')
    {
        for (int i = 0; i < MOVIESTOTAL; i++)
        {
            // Check for search criteria here
        }
    }
    else if (nc == 'c') // If user continues watching the movie name will be searched for
    {
        for (int i = 0; i < MOVIESTOTAL; i++)
        {
            if (strcmp(moviesPreSort[i].title, conWatch) == 0)
            {
                // If movie/series is found, all information is saved in conWatchData
                strcpy(conWatchData->title, conWatch);
                conWatchData->isSeries = moviesPreSort[i].isSeries;
                strcpy(conWatchData->ageRating, moviesPreSort[i].ageRating);
                conWatchData->duration = moviesPreSort[i].duration;
                strcpy(conWatchData->genre[0], moviesPreSort[i].genre[0]);
                strcpy(conWatchData->genre[1], moviesPreSort[i].genre[1]);
                strcpy(conWatchData->genre[2], moviesPreSort[i].genre[2]);
                strcpy(conWatchData->genre[3], moviesPreSort[i].genre[3]);
                strcpy(conWatchData->genre[4], moviesPreSort[i].genre[4]);
                conWatchData->rating = moviesPreSort[i].rating;
                break;
            }
        }
    }
    else
    {
        printf("Error: No command was found");
        exit(EXIT_FAILURE);
    }

    return;
}