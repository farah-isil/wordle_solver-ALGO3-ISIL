#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 1000  
#define WORD_LENGTH 5   
#define MAX_ATTEMPTS 6 


void print_feedback(char *guess, char *target) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == target[i])
            printf("[G]");
        else if (strchr(target, guess[i]))
            printf("[Y]");
        else
            printf("[ ]");
    }
    printf("  %s\n", guess);
}

int main() {
    char words[MAX_WORDS][WORD_LENGTH + 1];
    int word_count = 0;


    FILE *file = fopen("words.txt", "r");
    if (!file) {
        printf("Erreur: impossible d'ouvrir words.txt\n");
        return 1;
    }

    
    while (fscanf(file, "%5s", words[word_count]) == 1 && word_count < MAX_WORDS) {
        word_count++;
    }
    fclose(file);

    if (word_count == 0) {
        printf("Le dictionnaire est vide.\n");
        return 1;
    }

    
    srand(time(NULL));
    char *target = words[rand() % word_count];

    printf("Bienvenue dans Wordle!\nVous avez %d essais pour deviner le mot de 5 lettres.\n", MAX_ATTEMPTS);

    
    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        char guess[WORD_LENGTH + 1];
        printf("Essai %d: ", attempt);
        scanf("%5s", guess);




        if (strlen(guess) != WORD_LENGTH) {
            printf("Veuillez entrer un mot de 5 lettres.\n");
            attempt--;
            continue;
        }

        print_feedback(guess, target);

        
        if (strcmp(guess, target) == 0) {
            printf("Félicitations! Vous avez trouvé le mot!\n");
            return 0;
        }
    }

    printf("Dommage! Le mot était: %s\n", target);
    return 0;
} 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 1000
#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6

 
void check_letters(char *guess, char *target, char result[]) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == target[i])
             result[i] = 'G';   // Green
        else if (strchr(target, guess[i]))
             result[i] = 'Y';   // Yellow
        else
         result[i] = '_';   // Gray
    }
     result[WORD_LENGTH] = '\0';
}


int is_valid(char *word, char *guess, char  result[]) {
    char temp_feedback[WORD_LENGTH + 1];
    check_letters(guess, word, temp_feedback);
    return strcmp(temp_feedback,  result) == 0;
}