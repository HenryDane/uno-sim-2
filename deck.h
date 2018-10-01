#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
#include "main.h"

class Deck {
public:
    int _plus_value;
    std::vector<card_t> _cards;

    int _n_wild = 4;
    int _n_plus4 = 4;
    int _n_deck = 1;
public:
    card_t get_from_top( void );
    void put_on_top( card_t c );

    int get_value_of_top( void );
    color_t get_color_of_top( void );
    int get_num_color (color_t c);

    void generate_deck( void );
    void shuffle( void );

    std::vector<card_t> get_cards(void);
    card_t get_nth_card(int n);

    std::string print(void);
};


#endif // DECK_H
