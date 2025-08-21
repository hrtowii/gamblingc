#include "card.h"
#include "deck.h"
#include "blackjack.h"
#include <stdlib.h>
#include <stdio.h>
int main() {
    struct Card **deck = generate_deck();
    if (!deck) return 1;
    deck = randomise_deck(deck);
    menu(deck);

    free(deck);
}
int get_int_input(char* input) {
    char *p, s[100];
    long n;

    while (fgets(s, sizeof(s), stdin)) {
        n = strtol(s, &p, 10);
        if (p == s || *p != '\n') {
            printf("%s\n", input);
        } else break;
    }
    // printf("You entered: %ld\n", n);
}
void menu(struct Card **deck) {
    while (true) {
        // singleplayer / multiplayer
        // blackjack or poker
        printf("singleplayer or multiplayer?");
        int option = get_int_input("1 or 2: ");
        if (option == 1) {
            option = get_int_input("blackjack or poker? 1/2: ");
            if (option == 1) {
                blackjack(deck);
            } else {
                printf("unfinished");
            }
        } else {
            printf("unfinished");
        }
    }
}