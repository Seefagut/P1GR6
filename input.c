#include <stdio.h> // Engelsk eller Dansk?

int main(void){

    char genrepref1 = '?', genrepref2 = '?', genrepref3 = '?'; // 3 genre preferencer
    char genre[16][9] = {"Action", "Adventure", "Animation", "Biography", "Comedy", "Crime", "Drama", "Family",
                          "Fantasy", "History", "Horror", "Mystery", "Romance", "Sci-Fi", "Sport", "Thriller"};

    printf("Velkommen til vores Movie Recommender! Nu vil vi gerne have noget information fra dig :)\n"); // Skal måske ændres :-)

    do {
    printf("Indtast 3 genre du gerne vil se, sepereret med et komma (,) (Skriv ? for liste af genre): ");
    scanf(" %s, %s, %s", &genrepref1, &genrepref2, &genrepref3);
    for (int i = 0; i > 16; i++){
        // Lav liste over alle genre
    }

    if (genrepref1 == '?') {
        printf("\nAction, Adventure, Animation, Biography, Comedy, Crime, Drama, Family, \nFantasy, History, Horror, Mystery, Romance, Sci-Fi, Sport, Thriller\n");
    }

    } while (genrepref1 == '?');


    return 0;
}