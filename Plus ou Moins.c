#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int AskInt()
{
    int i;
    scanf_s("%d", &i);
    while (getchar() != '\n');

    return i;

}

void Play(int randomnumber, int bornemin, int bornemax) {
    int numberplayer;
    int round = 0;

    while (1) {
        printf("%d\n", randomnumber);
        printf("Tappez un nombre entre %d et %d : \n", bornemin, bornemax);
        numberplayer = AskInt();

        if (numberplayer == randomnumber) {
            printf("Bravo ! Vous avez gagné !\n");
            break;
        }
        else if (numberplayer < randomnumber) {
            printf("Plus !\n");
        }
        else {
            printf("Moins !\n");
        }

        round++;
        if (round == 5) {
            printf("Vous avez dépassez le nombre de tour !\n");
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    int randomnumber;
    int bornemin;
    int bornemax;
    char rejouer = 'y';

    while (1) {
        printf("Choisissez une borne minimum: \n");
        bornemin = AskInt();

        printf("Choisissez une borne maximum: \n");
        bornemax = AskInt();

        randomnumber = rand() % (bornemax - bornemin + 1) + bornemin;

        Play(randomnumber, bornemin, bornemax);

        printf("Voulez-vous rejouer ? y/n \n");
        scanf_s("%c", &rejouer, 1);
        while (getchar() != '\n');

        if (rejouer == 'n') {
            break;
        }
    }

    return 0;
}
