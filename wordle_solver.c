#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 1000
#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6

// Fill result with feedback: 'G' = correct place, 'Y' = wrong place, 'B' = not in word
void check_letters(const char *guess, const char *target, char *result) {
    int used[WORD_LENGTH] = {0}; // track letters already matched in target
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == target[i]) {
            result[i] = 'G';
            used[i] = 1;
        } else {
            result[i] = 'B';
        }
    }

    // Check for correct letters in wrong positions
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i] == 'B') {
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!used[j] && guess[i] == target[j]) {
                    result[i] = 'Y';
                    used[j] = 1;
                    break;
                }
            }
        }
    }

    result[WORD_LENGTH] = '\0'; // terminate string
}

// Check if a candidate word is consistent with previous guess & result
int is_valid(const char *candidate, const char *guess, const char *result) {
    int used[WORD_LENGTH] = {0};

    // First, check greens
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i] == 'G') {
            if (candidate[i] != guess[i])
                return 0;
            used[i] = 1;
        }
    }

    // Then check yellows
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i] == 'Y') {
            int found = 0;
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!used[j] && candidate[j] == guess[i] && candidate[j] != guess[j]) {
                    found = 1;
                    used[j] = 1;
                    break;
                }
            }
            if (!found) return 0;
        }
    }

    // Finally check blacks
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i] == 'B') {
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (candidate[j] == guess[i]) return 0;
            }
        }
    }

    return 1;
}

int main() {
    char words[MAX_WORDS][WORD_LENGTH + 1];
    int word_count = 0;

    FILE *file = fopen("words.txt", "r");
    if (!file) {
        perror("Failed to open words.txt");
        return 1;
    }

    while (fscanf(file, "%5s", words[word_count]) == 1) {
        word_count++;
        if (word_count >= MAX_WORDS) break;
    }
    fclose(file);

    if (word_count == 0) {
        printf("No words loaded.\n");
        return 1;
    }

    srand(time(NULL));
    char *target = words[rand() % word_count];

    char candidates[MAX_WORDS][WORD_LENGTH + 1];
    int candidate_count = word_count;
    for (int i = 0; i < word_count; i++) {
        strcpy(candidates[i], words[i]);
    }

    printf("Wordle Solver\n");

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        char *guess = candidates[0]; // pick first candidate
        char result[WORD_LENGTH + 1];

        check_letters(guess, target, result);
        printf("Essai %d: %s -> %s\n", attempt, guess, result);

        if (strcmp(guess, target) == 0) {
            printf("Word correct!\n");
            return 0;
        }

        char new_candidates[MAX_WORDS][WORD_LENGTH + 1];
        int new_count = 0;

        for (int i = 0; i < candidate_count; i++) {
            if (is_valid(candidates[i], guess, result)) {
                strcpy(new_candidates[new_count], candidates[i]);
                new_count++;
            }
        }

        candidate_count = new_count;
        for (int i = 0; i < new_count; i++) {
            strcpy(candidates[i], new_candidates[i]);
        }

        if (candidate_count == 0) break; // no candidates left
    }

    printf("The word was: %s\n", target);
    printf("Failed to guess within %d attempts.\n", MAX_ATTEMPTS);

    return 0;
}