#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "deck.h"

class Player {
public:
    Deck _hand;
    card_t find_in_hand(card_t c);
public:
    void init(void);
    int do_turn(Deck &deck);
    int num_cards(void);
    void take_card(card_t c);
    std::string print(void);
};

#endif // PLAYER_H
