#include "deck.h"
#include "blackjack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
void menu(struct Deck *deck);
int main() {
    struct Deck *deck = generate_deck();
    if (!deck) return 1;
    deck = randomise_deck(deck);
    menu(deck);
    free(deck);
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