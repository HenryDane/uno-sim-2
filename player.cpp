#include <iostream>
#include "main.h"
#include "player.h"

void Player::init(void){
    return;
}
int Player::num_cards(void){
    return _hand._cards.size();
}
void Player::take_card(card_t c){
    _hand.put_on_top(c);
}
std::string Player::print(void){
    return _hand.print();
}

/*
    function determines basic game mechanics
    returns 1 after playing a reverse
    does not yet stack

    TODO
    -   reflag plus_4 as used
    -   fix drawing of cards
    -   debug
*/
int Player::do_turn(Deck &deck, Deck &discard){
//    bool this_turn_wild = false;
    color_t wild_color = BLACK;

    // execute top of discard
    card_t top = discard.get_from_top();
    if (top.color == BLACK && top.value == 14) { // plus4
        for (int i = 0; i < 4; i++) // do this 4 times
            _hand.put_on_top(deck.get_from_top()); // take a card
        return 14;
    } else if (top.color != BLACK && top.value == 12) { // any plus2
        for (int i = 0; i < 2; i++) // do this 2 times
            _hand.put_on_top(deck.get_from_top()); // take a card
        return 12;
    } else if (top.color != BLACK && top.value == 10) { // any skip
        return 10;
    } else if (top.color != BLACK && top.value == 11) { // any reverse

    } else if (top.color == BLACK && top.value == 13) { // any wild
        // raise self flag
//        this_turn_wild = true;

        // reset the global flag
        wild_color = wild_color_now;
        wild_color_valid = false;
    }

    // card found in hand
    card_t found;
    if (top.value != 13) { // if its not a wild then
        found = find_in_hand(top); // look for card by card
    } else { // but if it was a wild
        found = find_in_hand({1000, wild_color}); // look for card by color only
    }
    if (found.value < 0) { // couldn't find a good card
        while(true){
            card_t drawn = deck.get_from_top();
            _hand.put_on_top(drawn);
            if (deck.get_cards().size() == 0) { // if we ran out of cards
                deck.generate_deck(); // rebuild deck
                deck.shuffle(); // shuffle deck
            }
            if (drawn.color == top.color ||
                drawn.value == top.value)
                break;
        }

        found = find_in_hand(top);
        if (found.value < 0) {
            std::cout << "SOMETHING IS VERY WRONG IN WHOOVILLE" << std::endl;
            abort();
        }
    }

    // put back the top card
    discard.put_on_top(top);

    // place ur card on top
    std::cout << "I played a " << print_card(found) << std::endl;
    discard.put_on_top(found);

    if (found.value == 11) { // if its a reverse
        return 1; // let the game know its time to change direction
    } else if (found.value == 13) { // if it is a wild
        wild_color = static_cast<color_t>(rand() % 4); // awful hack for choosing color
        wild_color_valid = true; // raise the flag agian
        return 13; // let game know what happened
    }

    return 0;
}

/*
    different versions of this are OK -- this is how the player finds their card
*/
card_t Player::find_in_hand(card_t c){
    std::vector<card_t> cards = _hand.get_cards();

    for (unsigned int i = 0; i < cards.size(); i++){
        if (c.value == 1000) {
            if (cards.at(i).color == BLACK||
                cards.at(i).color == c.color)
                return cards.at(i);
        } else {
            if (cards.at(i).color == BLACK||
                cards.at(i).color == c.color ||
                cards.at(i).color == c.value)
                return cards.at(i);
        }
    }

    // no card was found
    return {-1, BLACK, false};
}
