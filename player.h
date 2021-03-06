#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "deck.h"

class Player {
public:
    Deck _hand;
    card_t find_in_hand(card_t c);
    int _id;
public:
    Player(){
        // do nothing
    }

    void init(int id);
    int do_turn(Deck &deck, Deck &discard, bool debug = false);
    int num_cards(void);
    void take_card(card_t c);
    std::string print(void);
};

#endif // PLAYER_H
