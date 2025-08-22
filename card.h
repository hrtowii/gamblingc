#include <stdbool.h>
#include <stddef.h>
#define CARD_BUF_SIZE 100
enum Suit {
    SPADE,
    CLUB,
    DIAMOND,
    HEART
};

struct Card {
    enum Suit suit;
    int rank; // 1-14
    bool flipped;
};
int rank_to_letter(const struct Card card, char* card_buffer, size_t buffer_size);
const char* suit_to_string(const struct Card card);
const char* suit_to_symbol(const struct Card card);
const char *draw_card(struct Card card);
static inline const char *draw_hand(const struct Card *c)
{
    return draw_card(*c);
}