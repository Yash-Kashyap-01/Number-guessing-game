#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to clear input buffer
void clearBuffer() {
    while (getchar() != '\n');
}

// Function to print colored text
void printColor(const char *text, const char *color) {
    printf("%s%s\033[0m", color, text);
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

        // Game banner
        printf("\n\033[1;36m===============================\033[0m\n");
        printf("   🎮 WELCOME TO GUESS GAME 🎮  \n");
        printf("\033[1;36m===============================\033[0m\n");

        // Custom range
        printf("\nChoose range for the mystery number.\n");
        printf("Enter minimum: ");
        scanf("%d", &min_range);
        printf("Enter maximum: ");
        scanf("%d", &max_range);

        if (min_range >= max_range) {
            printf("Invalid range! Defaulting to 1–100.\n");
            min_range = 1; max_range = 100;
        }

        mystery_number = (rand() % (max_range - min_range + 1)) + min_range;

        // Difficulty
        printf("\nChoose Difficulty:\n");
        printf("1. Easy (Unlimited attempts)\n");
        printf("2. Medium (10 attempts)\n");
        printf("3. Hard (5 attempts)\n");
        printf("Enter choice: ");
        if (scanf("%d", &difficulty) != 1) {
            clearBuffer();
            difficulty = 1;
        }

        if (difficulty == 3) max_attempts = 5;
        else if (difficulty == 2) max_attempts = 10;
        else max_attempts = 9999;

        printf("\nLet's start! Try to guess the number between %d and %d.\n", min_range, max_range);

        time_t start_time = time(NULL); // Timer start

        do {
            printf("\nEnter your guess: ");
            if (scanf("%d", &guessed_number) != 1) {
                clearBuffer();
                printColor("Invalid input! Enter a number.\n", "\033[1;31m");
                continue;
            }

            if (guessed_number < min_range || guessed_number > max_range) {
                printColor("Please enter a number within the chosen range.\n", "\033[1;33m");
                continue;
            }

            no_of_guesses++;

            if (guessed_number < mystery_number) {
                printColor("HIGHER NUMBER PLEASE 🔼\n", "\033[1;33m");
            } else if (guessed_number > mystery_number) {
                printColor("LOWER NUMBER PLEASE 🔽\n", "\033[1;33m");
            }

            // Hints after every 3 wrong tries
            if (no_of_guesses % 3 == 0 && guessed_number != mystery_number) {
                if (mystery_number % 2 == 0)
                    printf("💡 Hint: The number is EVEN.\n");
                else
                    printf("💡 Hint: The number is ODD.\n");

                printf("💡 Another Hint: The number is between %d and %d.\n",
                       mystery_number - 5 < min_range ? min_range : mystery_number - 5,
                       mystery_number + 5 > max_range ? max_range : mystery_number + 5);
            }

            if (no_of_guesses >= max_attempts && guessed_number != mystery_number) {
                printColor("\n💀 Game Over! You've used all attempts.\n", "\033[1;31m");
                printf("The correct number was %d.\n", mystery_number);
                streak = 0; // reset streak
                break;
            }

        } while (guessed_number != mystery_number);

        if (guessed_number == mystery_number) {
            time_t end_time = time(NULL);
            int time_taken = (int)(end_time - start_time);

            printColor("\n🎉 Congratulations! 🎉\n", "\033[1;32m");
            printf("You guessed the number in %d tries.\n", no_of_guesses);
            printf("⏱️ Time Taken: %d seconds\n", time_taken);

            // Streak
            streak++;
            printf("🔥 Current Streak: %d wins in a row!\n", streak);

            // Best score update
            if (best_score == 0 || no_of_guesses < best_score) {
                best_score = no_of_guesses;
                printColor("🏆 New Best Score! 🏆\n", "\033[1;35m");
            } else {
                printf("Your Best Score: %d guesses\n", best_score);
            }
        }

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\nThanks for playing! \n");
    if (best_score > 0) {
        printf("🎯 Your Overall Best Score: %d guesses\n", best_score);
    }
    printf("\n\033[1;36m===============================\033[0m\n");
    printf("     Designed by Yash Kashyap  \n");
    printf("\033[1;36m===============================\033[0m\n");

    return 0;
}
