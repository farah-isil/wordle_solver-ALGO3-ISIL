Wordle Game & Solver in C Description:

This project consists of two C programs:

a Wordle game and a Wordle solver.

• The Wordle game allows a user to guess a random 5-letter word within 6 attempts, providing feedback for each guess with color-coded hints.

• The Wordle solver automatically attempts to guess the word using feedback rules similar to the original game, narrowing down candidates each turn.

The objective is to simulate the popular Wordle experience in C, demonstrating string manipulation, file I/O, and basic game logic.

How to Download, Clone, and Run :

• Clone the repository or download the source files: 

• git clone https://github.com/farah-isil/wordle_solver-ALGO3-ISIL
Compile 

Use gcc or any C compiler:

gcc -o wordle_game wordle_game.c

gcc -o wordle_solver wordle_solver.c 

Run

• To play the Wordle game:

./wordle_game 

• To run the Wordle solver:

./wordle_solver 

Example Usage and Sample Output :

Wordle Game :

Bienvenue dans Wordle!

Vous avez 6 essais pour deviner le mot de 5 lettres.

Essai 1: snake

[ ][ ][Y][ ][Y]  snake

Essai 2: adieu

[Y][Y][ ][Y][ ]  adieu

Essai 3: delay

[G][Y][ ][G][ ]  delay

Essai 4: dream

[G][G][G][G][G]  dream

F├®licitations! Vous avez trouv├® le mot!

Wordle Solver :

Wordle Solver

Essai 1: arise -> BYBBB 

Essai 2: clout -> GBYBB 

Essai 3: count -> GGGGG 

Word correct! 

Screenshots from the terminal :

wordle solver :

![photo_2025-12-19_15-32-08 (3)](https://github.com/user-attachments/assets/dfc5fd4c-e4a7-4bbc-b95f-c4486e450215)

wordle game :

![photo_2025-12-19_15-32-08](https://github.com/user-attachments/assets/13362c46-b769-4ec7-8efa-5f725c7f2ef2)


