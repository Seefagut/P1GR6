#include <stdio.h> // Engelsk eller Dansk?
#include <stdlib.h>
#include <time.h>

struct pref new_rec();

struct pref {
    char genre1;
    char genre2;
    char genre3;
    int min;
    int max;
    // add stop time
};

int main(void){

    char nv = NULL;

    do {
        printf("Vil du have en ny anbefaling eller fortsaette med en serie? (n for ny / v for videre): "); // (ny / videre) er placeholders
        scanf(" %c", &nv);
    } while (nv != 'n' || nv != 'v');

    if (nv == 'n'){
        struct pref = new_rec();
    } else if (nv == 'v'){
        con_rec(); // skriv func
    } else {
        printf("Fejl med programmet, stopper");
        exit(EXIT_FAILURE);
    }


    return 0;
}

struct pref new_rec(){

    int g1 = 0, g2 = 0, g3 = 0;
    char gp1 = '?', gp2 = '?', gp3 = '?'; // 3 genre preferencer
    char genre[16][10] = {"Action", "Adventure", "Animation", "Biography", "Comedy", "Crime", "Drama", "Family",
                          "Fantasy", "History", "Horror", "Mystery", "Romance", "Sci-Fi", "Sport", "Thriller"};

    int min_rating = 0, max_rating = 0;

    printf("Velkommen til vores Movie Recommender! Nu vil vi gerne have noget information fra dig :)\n"); // Skal måske ændres :-)

    do {
        printf("Indtast 3 genre du gerne vil se, sepereret med et komma (,) (Skriv ? for liste af genre): ");
        scanf(" %s, %s, %s", &gp1, &gp2, &gp3);
        for (int i = 0; i > 16; i++){
            if (gp1 == genre[i]){
                g1 = i;
            } else if (gp2 == genre[i]) {
                g2 = i;
            } else if (gp3 == genre[i]) {
                g3 = i;
            }
        }

        if (g2 == 0) {
            gp2 = NULL;
        } else if (g3 == 0) {
            gp3 = NULL;
        }

        if (gp1 == '?') {
            printf("\nAction, Adventure, Animation, Biography, Comedy, Crime, Drama, Family, \nFantasy, History, Horror, Mystery, Romance, Sci-Fi, Sport, Thriller\n");
        }

    } while (gp1 == '?');

    do {
        printf("Indtast minimum IMDB vurdering (Helt tal mellem 1 og 10): ");
        scanf(" %d", &min_rating);
    } while (min_rating > 0 && min_rating <= 10);

    do {
        printf("Indtast maximum IMDB vurdering (Helt tal mellem 1 og 10): ");
        scanf(" %d", &max_rating);
    } while (max_rating <= min_rating && max_rating <= 10);



}