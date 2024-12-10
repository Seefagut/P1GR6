#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMEMAXLENGTH 50
#define GENREMAXLENGTH 100
#define AGERATINGMAXLENGTH 10
// #define MAXDURATION 4
// #define MAXAMOUNTOFGENRES 5
#define ACTORSMAXLENGTH 200

typedef struct movieData
{
  char title[NAMEMAXLENGTH];
  char ageRating[AGERATINGMAXLENGTH];
  int duration;
  char genre[GENREMAXLENGTH];
  double rating;
  char actor[ACTORSMAXLENGTH];
  int score;
} movieData;

typedef struct pref
{
  char genre1[GENREMAXLENGTH];
  int genrepref1;
  char genre2[GENREMAXLENGTH];
  int genrepref2;
  char genre3[GENREMAXLENGTH];
  int genrepref3;
  char actor1[ACTORSMAXLENGTH];
  char actor2[ACTORSMAXLENGTH];
  char actor3[ACTORSMAXLENGTH];
  int timetowatch;
  char ageRating;
} pref;

// Prototypes
void give_points(movieData movieArray[], pref userpref, int size);

int main(void)

{
  pref userpref;

  printf("Input genre: \n");
  scanf(" %s", userpref.genre1);

  printf("Input actor: \n");
  scanf(" %[^\n]s", userpref.actor1);

  printf("Input time watch: \n");
  scanf(" %d", &userpref.timetowatch);
  userpref.timetowatch *= 60;

  

  movieData movieArray[3] =
      {
          {"star wars", "16", 8400, "Adventure", 9.9, "Ewan McGregor", 0},
          {"wall-e", "6", 5100, "Adventure", 9.2, "Elissa Knight", 0},
          {"scary movie", "18", 5400, "Horror", 8.7, "Anna Faris", 0}};

int size = sizeof(movieArray) / sizeof(movieArray[0]);
give_points(movieArray, userpref, size);

printf("These are the recommendations: \n");
printf("%-16s%-16s%-16s%-16s%-16s%-16s\n", "Title:", "Genre:", "Actor:", "Duration:", "IMDB:", "TEST-SCORE");
printf("-------------------------------------------------------------------------------------------\n");
for (int i = 0; i < size; i++)
{
  printf("%-16s%-16s%-16s%-16d%-16.1lf%-16d\n", movieArray[i].title, movieArray[i].genre, movieArray[i].actor, movieArray[i].duration / 60, movieArray[i].rating, movieArray[i].score);
}
  return 0;
}

void give_points(movieData *movieArray, pref userpref, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (strcmp(movieArray[i].actor, userpref.actor1) == 0)
    {
      movieArray[i].score += 1;
    }
    if (strcmp(movieArray[i].genre, userpref.genre1)== 0)
    {
      movieArray[i].score += 1;
    }
    //points according to time-to-watch
    int timeDiff = userpref.timetowatch - movieArray[i].duration;
    if (timeDiff<= 300)
    {
      movieArray[i].score += 3;
    }
    else if (timeDiff <= 600)
    {
      movieArray[i].score += 2;
    }
    else if (timeDiff <= 900)
    {
      movieArray[i].score += 1;
    }
  }
}