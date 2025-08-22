#include "card.h"
struct Deck {
    struct Card  *cards[52];
    int           next;            /* index of the next card to draw    */
};
struct Deck *generate_deck();
struct Deck *randomise_deck(struct Deck *cards);

static inline struct Card *draw_card_from_deck(struct Deck *deck)
{
    if (!deck || deck->next >= 52) return NULL;
    return deck->cards[deck->next++];
}