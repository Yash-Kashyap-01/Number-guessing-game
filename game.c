#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clearBuffer() {
    while (getchar() != '\n');
}


int getIntInput(const char *prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) break;
        clearBuffer();
        printf("Invalid input! Please enter a number.\n");
    }
    return value;
}


int getAttemptsByDifficulty(int difficulty) {
    switch (difficulty) {
        case 2: return 10; // Medium
        case 3: return 5;  // Hard
        default: return 9999; // Easy (Unlimited)
    }
}

int main() {
    char choice;
    int best_score = 0; 
    int streak = 0;      

    srand(time(0));

    do {
        int guessed_number, no_of_guesses = 0;
        int min_range, max_range, difficulty, max_attempts;
        int mystery_number;
        
        printf("\n===============================\n");
        printf("       WELCOME TO GUESS GAME    \n");
        printf("===============================\n");

        min_range = getIntInput("\nEnter minimum range: ");
        max_range = getIntInput("Enter maximum range: ");

        if (min_range >= max_range) {
            printf("Invalid range! Defaulting to 1–100.\n");
            min_range = 1; 
            max_range = 100;
        }

        mystery_number = (rand() % (max_range - min_range + 1)) + min_range;

        printf("\nChoose Difficulty:\n");
        printf("1. Easy (Unlimited attempts)\n");
        printf("2. Medium (10 attempts)\n");
        printf("3. Hard (5 attempts)\n");

        difficulty = getIntInput("Enter choice: ");
        max_attempts = getAttemptsByDifficulty(difficulty);

        printf("\nLet's start! Try to guess the number between %d and %d.\n", min_range, max_range);

        time_t start_time = time(NULL); 

        while (1) {
            guessed_number = getIntInput("\nEnter your guess: ");

            if (guessed_number < min_range || guessed_number > max_range) {
                printf("Please enter a number within the chosen range.\n");
                continue;
            }

            no_of_guesses++;

            if (guessed_number < mystery_number) {
                printf("Higher number please.\n");
            } else if (guessed_number > mystery_number) {
                printf("Lower number please.\n");
            } else {
            
                time_t end_time = time(NULL);
                int time_taken = (int)(end_time - start_time);

                printf("\nCongratulations!\n");
                printf("You guessed the number in %d tries.\n", no_of_guesses);
                printf("Time Taken: %d seconds\n", time_taken);

                streak++;
                printf("Current Streak: %d wins in a row!\n", streak);

                if (best_score == 0 || no_of_guesses < best_score) {
                    best_score = no_of_guesses;
                    printf("New Best Score!\n");
                } else {
                    printf("Your Best Score: %d guesses\n", best_score);
                }
                break;
            }

            if (no_of_guesses % 3 == 0) {
                printf("Hint: The number is %s.\n", (mystery_number % 2 == 0) ? "EVEN" : "ODD");
                printf("Hint: The number is between %d and %d.\n",
                       (mystery_number - 5 < min_range) ? min_range : mystery_number - 5,
                       (mystery_number + 5 > max_range) ? max_range : mystery_number + 5);
            }
  
            if (no_of_guesses >= max_attempts) {
                printf("\nGame Over! You've used all attempts.\n");
                printf("The correct number was %d.\n", mystery_number);
                streak = 0; 
                break;
            }
        }

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\nThanks for playing!\n");
    if (best_score > 0) {
        printf("Your Overall Best Score: %d guesses\n", best_score);
    }
    printf("\n===============================\n");
    printf("     Designed by Yash Kashyap  \n");
    printf("===============================\n");

    return 0;
}

