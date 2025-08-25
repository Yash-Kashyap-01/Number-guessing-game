#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    char choice;

    printf("DESCRIPTION OF THE GAME:\n");
    printf("This game is designed to guess the number between 1 to 100.\n");
    printf("The program will generate a random number and you have to guess it using hints.\n\n");

    srand(time(0));

    do {
        int guessed_number;
        int no_of_guesses = 0;
        int mystery_number = (rand() % 100) + 1;

        printf("Let's start! Try to guess the number.\n");

        do {
            printf("Enter your guess: ");
            scanf("%d", &guessed_number);

            if (guessed_number < mystery_number) {
                printf("HIGHER NUMBER PLEASE\n");
            } else if (guessed_number > mystery_number) {
                printf("LOWER NUMBER PLEASE\n");
            }
            no_of_guesses++;

        } while (guessed_number != mystery_number);

        printf("\n Congooo !!\n");
        printf("You guessed the number in %d guesses\n", no_of_guesses);

        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &choice); 

    } while (choice == 'y' || choice == 'Y');

    printf("\nThanks for playing! \n");
    printf("\n===============================\n");
    printf("     Designed by Yash Kashyap  \n");
    printf("===============================\n");


    return 0;
}
