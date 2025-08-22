#include "deck.h"
#include <stdlib.h>
#include <time.h>
// decks contain 13 x 4 cards, and each player receives 2 cards while the dealer has 1 face up and face down

// generate deck -> contains next, pointers to an array of Cards
struct Deck *generate_deck(void) {
    struct Deck *d = malloc(sizeof(struct Deck));
    if (!d) return 0;

    struct Card *cards = calloc(52, sizeof(struct Card));
    if (!cards) { free(d); return 0; }

    int i = 0;
    for (int s = SPADE; s <= HEART; ++s) {
        for (int r = 2; r <= 14; ++r) {
            cards[i].suit    = (enum Suit)s;
            cards[i].rank    = r;
            cards[i].flipped = false;
            d->cards[i]      = &cards[i];
            ++i;
        }
    }

    d->next = 0;                         /* top of the deck = first element */
    randomise_deck(d);                   /* shuffle right away */
    return d;
}
// randomise deck, assumes number is 52, pointers to array of Cards
struct Deck *randomise_deck(struct Deck *deck) {
    if (!deck || !deck->cards) {
        return NULL;
    }
    srand(time(0));
    for (int i = 52 - 1; i > 0; i--) {
        int j = rand() % (i + 1); // random index from 0..i
        // swap pointers cards[i] and cards[j]
        struct Card *tmp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = tmp;
    }
    return deck;
}
