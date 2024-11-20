#include <stdio.h> // Engelsk eller Dansk?
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct pref new_rec(void);
struct conpref con_rec(void);
int getdiff(void);

struct pref {
    char genre1[10];
    int genrepref1;
    char genre2[10];
    int genrepref2;
    char genre3[10];
    int genrepref3;
    int min;
    int max;
    int timetowatch;
};

struct conpref {
    char series[50];
    int timetowatch;
};

int main(void){

    char nv;

    do {
        printf("Vil du have en ny anbefaling eller fortsaette med en serie? (n for ny / v for videre): "); // (ny / videre) er placeholders
        scanf(" %c", &nv);
    } while (nv != 'n' && nv != 'v');

    if (nv == 'n'){
        struct pref preference = new_rec();
    } else if (nv == 'v'){
        struct conpref series = con_rec(); // skriv func
    } else {
        printf("Fejl med programmet, stopper");
        exit(EXIT_FAILURE);
    }


    return 0;
}

struct pref new_rec(void){

    int g1 = -1, g2 = -1, g3 = -1;
    char gp1[10] = "?", gp2[10] = "?", gp3[10] = "?"; // 3 genre preferencer
    char genre[16][10] = {"Action", "Adventure", "Animation", "Biography", "Comedy", "Crime", "Drama", "Family",
                          "Fantasy", "History", "Horror", "Mystery", "Romance", "Sci-Fi", "Sport", "Thriller"};

    char ar;

    int min_rating = 0, max_rating = 0;

    printf("Velkommen til vores Movie Recommender! Nu vil vi gerne have noget information fra dig :)\n"); // Skal måske ændres :-)

    do {
        printf("Indtast 3 genre du gerne vil se, sepereret med et komma (,) (Skriv ? for liste af genre): ");
        scanf(" %9s, %9s, %9s", &gp1, &gp2, &gp3);
        for (int i = 0; i > 16; i++){
            if (strcmp(gp1, genre[i]) == 0){
                g1 = i;
            } else if (strcmp(gp2, genre[i]) == 0) {
                g2 = i;
            } else if (strcmp(gp3, genre[i]) == 0) {
                g3 = i;
            }
        }

        if (strcmp(gp1, "?") == 0) {
            printf("\nAction, Adventure, Animation, Biography, Comedy, Crime, Drama, Family, \nFantasy, History, Horror, Mystery, Romance, Sci-Fi, Sport, Thriller\n");
        }

    } while (strcmp(gp1, "?") == 0);

    do {
        printf("Vil du have voksenfilm med i anbefalingerne? (y/n) (18+): ");
        scanf(" %c", &ar);
    } while (ar != 'y' && ar != 'n');

    do {
        printf("Indtast minimum IMDB vurdering (Helt tal mellem 1 og 10): ");
        scanf(" %d", &min_rating);
    } while (min_rating < 0 || min_rating >= 10);

    do {
        printf("Indtast maximum IMDB vurdering (Helt tal mellem 1 og 10): ");
        scanf(" %d", &max_rating);
    } while (max_rating <= min_rating || max_rating > 10);

    int diff = getdiff();

    struct pref preference;

    strcpy(preference.genre1, genre[g1]);
    preference.genrepref1 = g1;
    strcpy(preference.genre2, genre[g2]);
    preference.genrepref2 = g2;
    strcpy(preference.genre3, genre[g3]);
    preference.genrepref3 = g3;
    preference.min = min_rating;
    preference.max = max_rating;
    preference.timetowatch = diff;

    return preference;

}

struct conpref con_rec(void){
    char series[50] = "?";
    do {
        printf("Indtast navnet på serien:");
        scanf(" %49s", &series);

    } while (series == "?");

    int diff = getdiff();

    struct conpref con_series;

    strcpy(con_series.series, series);
    con_series.timetowatch = diff;
}

int getdiff(void){

    time_t time1;
    struct tm stoptimetm;
    int hr, minutes;
    int diff = 0;

    time(&time1);
    struct tm *starttime = localtime(&time1);
    stoptimetm = *starttime;

    printf("Indtast stoptid (Ex. 18:40): ");
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

    return diff;

}