#include "card.h"
#include <stdio.h>
#include <string.h>

// buffer must be size 3 at least, 10+\0
int rank_to_letter(const struct Card card, char* card_buffer, size_t buffer_size) { 
    const char* letters[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    if (card.rank < 2 || card.rank > 14 || buffer_size < 3) {
        if (buffer_size > 0) {
            card_buffer[0] = '\0';
        }
        return -1;
    }
    strncpy(card_buffer, letters[card.rank - 2], buffer_size - 1);
    card_buffer[buffer_size - 1] = '\0';
    return 0;
}

const char* suit_to_string(const struct Card card) {
    // switch (card.suit) {
    //     case SPADE:
    //         return "Spades";
    //     case CLUB:
    //         return "Clubs";
    //     case DIAMOND:
    //         return "Diamonds";
    //     case HEART:
    //         return "Hearts";
    // }
    // https://chatgpt.com/share/68a734a0-dfc0-8005-a04a-3b246ad535db
    static const char* table[] = {"Spades","Clubs","Diamonds","Hearts"};
    return table[card.suit];
}

const char* suit_to_symbol(const struct Card card) {
    // switch (card.suit) {
    //     case SPADE:
    //         return "S";
    //     case CLUB:
    //         return "C";
    //     case DIAMOND:
    //         return "D";
    //     case HEART:
    //         return "H";
    // }
    // https://chatgpt.com/share/68a734a0-dfc0-8005-a04a-3b246ad535db
    static const char* table[] = {"\xE2\x99\xA0","\xE2\x99\xA3","\xE2\x99\xA6","\xE2\x99\xA5"};
    return table[card.suit];
}

static char card_picture[CARD_BUF_SIZE];
const char *draw_card(struct Card card) {
    char rank_buf[3] = "";                /* "2" … "10" or "J","Q","K","A" */
    rank_to_letter(card, rank_buf, sizeof(rank_buf));

    const char *suit_sym = suit_to_symbol(card);

    memset(card_picture, 0, sizeof(card_picture));
    if (!card.flipped) {
        snprintf(card_picture, CARD_BUF_SIZE,
            "┌───────┐\n"
            "│%-2s     │\n"
            "│   %s   │\n"
            "│     %-2s│\n"
            "└───────┘\n",
        rank_buf,           /* left‑top rank */
        suit_sym,           /* centre suit */
        rank_buf);          /* right‑bottom rank (mirrored) */
    } else {
        snprintf(card_picture, CARD_BUF_SIZE,
            "┌───────┐\n"
            "│       │\n"
            "│       │\n"
            "│       │\n"
            "└───────┘\n"
        );          
    }
    return card_picture;
}

