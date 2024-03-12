#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int Askint()
{
    while (1)
    {
        int i;
        int error = scanf_s("%d", &i);
        while (getchar() != '\n');
        if (error == 1)
        {
            return i;
        }
        printf("Enter an integer number !: ");
    }
}

char Askchar() 
{
    
    while (1) 
    {
        char c;
        int error = scanf_s("%c", &c, 1);
        while (getchar() != '\n');
        if (error == 1) 
        {
            return c;
        }
        printf("Enter a character !: ");
    }  
}

int main() 
{
    
    while (1) 
    {
        int trylimit;
        int bornemin;
        int bornemax;
        char restart;

        printf("Starting Game !\n");

        printf("Enter the minimum number: ");
        bornemin = Askint();

        printf("Enter the maximum number: ");
        bornemax = Askint();

        printf("Enter a try limit: ");
        trylimit = Askint();

        Play(bornemin, bornemax, trylimit);

        printf("\nRestart game ? (Y/N;y/n): ");
        restart = Askchar();

        if (restart == 'n') 
        {
            break;
        }
    }
}

int Play(int bornemin, int bornemax, int trylimit) 
{
    srand(time(NULL));

    int guess;
    int guesscount = 0;
    int randomnumber = rand() % (bornemax - bornemin + 1) + bornemin;

    while (1)
    {
        printf("\nGuess a number between %d and %d: ", bornemin, bornemax);
        guess = Askint();
        guesscount++;

        if (guesscount == trylimit)
        {
            printf("You loosed :(");
            break;

        }
        else if (guess == randomnumber)
        {
            printf("You found the right number :)");
            break;

        }
        else if (guess > randomnumber)
        {
            printf("Lower\n");
        }
        else
        {
            printf("Upper\n");
        }
    }
}

