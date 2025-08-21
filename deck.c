#include "card.h"
#include <stdlib.h>
#include <time.h>
// decks contain 13 x 4 cards, and each player receives 2 cards while the dealer has 1 face up and face down

// generate deck, pointers to an array of Cards
struct Card **generate_deck() {
    struct Card *deck = malloc(52 * sizeof(struct Card));
    struct Card **deck_ptrs = malloc(52 * sizeof(struct Card *));
    if (!deck || !deck_ptrs) {
        free(deck);
        free(deck_ptrs);
        return 0;
    }
    int i = 0;
    for (int s = SPADE; s <= HEART; s++) {
        for (int r = 1; r <= 13; r++) {
            deck[i].suit = (enum Suit)s;
            deck[i].rank = r;
            deck[i].flipped = 0;
            deck_ptrs[i] = &deck[i];
            i++;
        }
    }
    return deck_ptrs;
}
// randomise deck, assumes number is 52, pointers to array of Cards
struct Card **randomise_deck(struct Card** cards) {
    if (cards == 0) {
        return 0;
    }
    srand(time(0));
    for (int i = 52 - 1; i > 0; i--) {
        int j = rand() % (i + 1); // random index from 0..i
        // swap pointers cards[i] and cards[j]
        struct Card *tmp = cards[i];
        cards[i] = cards[j];
        cards[j] = tmp;
    }
    return cards;
}
