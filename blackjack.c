// #include "card.h"
#include "deck.h"
#include <stdio.h>
struct blackjack_hand {
    const struct Card *cards[5];
    int count;
};

// calculating hands will return either a = 11 or a = 1, for now treat ace as 11
static int card_value(struct Card card) {
    // face cards
    if (card.rank >= 11 && card.rank <= 13) { 
        return 10;
    }
    if (card.rank == 14) {
        return 11; // aces
    }
    return card.rank; // regular card
    
}

static int hand_value(struct blackjack_hand *hand) {
    int sum = 0;
    int aces = 0;
    for (int i = 0; i < hand->count; i++) {
        int value = card_value(*(hand->cards[i]));
        sum += value;
        if (value == 11) { 
            aces++;
        }
    }
    // if too high, reduce ace to 1
    while (sum > 21 && aces > 0) {
        aces -= 1;
        sum -= 10;
    }
    return sum;
}

void blackjack(struct Deck deck) {
    // draw stage
    // draw 2 cards from randomised deck, into your own hand
    // dealer gets 2, 1 is card.flipped = true;
    printf("drawing...");
    struct blackjack_hand player_hand = {.count = 0};
    struct blackjack_hand dealer_hand = {.count = 0};
    for (int i = 0; i < 2; ++i) {
        struct Card *c = draw_card_from_deck(&deck);
        if (!c) {
            printf("Deck exhausted!\n");
            return;
        }
        player_hand.cards[i] = c;
        player_hand.count++;
    }

    printf("Your hand (%d points):\n", hand_value(&player_hand));
    for (int i = 0; i < player_hand.count; ++i) {
        printf("%s\n", draw_hand(player_hand.cards[i]));
    }
    // hit / stand stage

    // dealer unflips stage

    // needed function: print game state
}