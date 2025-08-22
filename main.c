#include "deck.h"
#include "blackjack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
void menu(struct Deck *deck);
int main() {
    struct Deck *deck = generate_deck();
    if (!deck) return 1;
    deck = randomise_deck(deck);
    menu(deck);
    free(deck);
}
int get_int_input(char* input) {
    char *p, s[100];
    long n;
    printf("%s\n", input);

    while (fgets(s, sizeof(s), stdin)) {
        n = strtol(s, &p, 10);
        if (p == s || *p != '\n') {
            printf("Please enter an integer: \n");
        } else break;
    }
    return (int)n;
    // printf("You entered: %ld\n", n);
}
void menu(struct Deck *deck) {
    while (true) {
        // singleplayer / multiplayer
        // blackjack or poker
        int option = get_int_input("singleplayer or multiplayer? 1 or 2: ");
        if (option == 1) {
            option = get_int_input("blackjack or poker? 1/2: ");
            if (option == 1) {
                blackjack(*deck);
                break;
            } else {
                printf("unfinished");
            }
        } else {
            printf("unfinished");
        }
    }
}