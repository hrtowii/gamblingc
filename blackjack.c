// #include "card.h"
#include "deck.h"
#include "utils.h"
#include <stdio.h>
struct blackjack_hand {
    struct Card *cards[5];
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
void deal_player_hand(struct Deck *deck, struct blackjack_hand *player_hand) {
    for (int i = 0; i < 2; ++i) {
        struct Card *c = draw_card_from_deck(deck);
        if (!c) {
            printf("Deck exhausted!\n");
            return;
        }
        player_hand->cards[i] = c;
        player_hand->count++;
    }
}
void deal_dealer_hand(struct Deck *deck, struct blackjack_hand *dealer_hand) {
    for (int i = 0; i < 2; ++i) {
        struct Card *c = draw_card_from_deck(deck);
        if (!c) {
            printf("Deck exhausted!\n");
            return;
        }
        dealer_hand->cards[i] = c;
        dealer_hand->count++;
        if (i == 0) {
            dealer_hand->cards[i]->flipped = true;
        }
    }
}
// difference from deal: this is if the hand is below 17
void draw_dealer_hand(struct Deck *deck, struct blackjack_hand *dealer_hand) {
    while (hand_value(dealer_hand) < 17 && dealer_hand->count < 5) {
        struct Card *c = draw_card_from_deck(deck);
        if (!c) {
            printf("Deck exhausted!\n");
            return;
        }
        dealer_hand->cards[dealer_hand->count] = c;
        dealer_hand->count++;
    }
}
void print_player_hand(struct blackjack_hand *player_hand, bool dealer) {
    if (dealer) {
        printf("Dealer hand (%d points):\n", hand_value(player_hand));
    } else {
        printf("Your hand (%d points):\n", hand_value(player_hand));
    }
    for (int i = 0; i < player_hand->count; ++i) {
        printf("%s\n", draw_hand(player_hand->cards[i]));
    }
}
void blackjack(struct Deck deck) {
    // draw stage
    // draw 2 cards from randomised deck, into your own hand
    // dealer gets 2, 1 is card.flipped = true;
    bool won = false;
    while (won == false) {
        printf("drawing...\n");
        struct blackjack_hand player_hand = {.count = 0};
        struct blackjack_hand dealer_hand = {.count = 0};
        deal_player_hand(&deck, &player_hand);
        deal_dealer_hand(&deck, &dealer_hand);

        print_player_hand(&player_hand, 0);

        printf("Dealer hand (?? points):\n");
        for (int i = 0; i < dealer_hand.count; ++i) {
            printf("%s\n", draw_hand(dealer_hand.cards[i]));
        }
        if (hand_value(&player_hand) == 21) {
            printf("blackjack!\n");
            won = true;
        }
        // hit / stand stage
        bool stood = false;
        while (!stood) {
            int choice = get_int_input("hit or stand? 1/2\n");
            if (choice == 1) {
                // check if score isnt 21
                printf("drawing...\n");
                struct Card *c = draw_card_from_deck(&deck);
                if (!c) {
                    printf("Deck exhausted!\n");
                    return;
                }            
                player_hand.cards[player_hand.count] = c;
                player_hand.count++;
                print_player_hand(&player_hand, 0);
                if (hand_value(&player_hand) == 21) {
                    printf("blackjack!\n");
                    won = true;
                }
            } else if (choice == 2) {
                stood = true;
            } else {
                printf("give a proper choice\n");
            }
        }
        // dealer unflips stage
        dealer_hand.cards[0]->flipped = false;
        print_player_hand(&dealer_hand, 1);
        printf("Dealer draws cards...\n");
        draw_dealer_hand(&deck, &dealer_hand);
        print_player_hand(&dealer_hand, 1);

        int dealer_score = hand_value(&dealer_hand);
        int player_score = hand_value(&player_hand);
        if (dealer_score > 21 || player_score > dealer_score) {
            printf("you win!\n");
            won = true;
        } else if (dealer_score > player_score) {
            printf("you lost!\n");
            break;
        } else {
            printf("tie!\n");
        }
        // needed function: print game state
}
}