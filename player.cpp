#include <iostream>
#include "main.h"
#include "player.h"

void Player::init(int id){
    _id = id;
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
        if (top.wild) {
            for (int i = 0; i < 4; i++) // do this 4 times
                _hand.put_on_top(deck.get_from_top()); // take a card
            top.wild = false;
            // put back the top card
            discard.put_on_top(top);

            //std::cout << _id << " I took 4 cards" << std::endl;
            return 14;
        } else {
            //std::cout << _id << " I ignored an already used +4" << std::endl;
            top.wild = false;
            // put back the top card
            discard.put_on_top(top);
            // raise self flag
    //        this_turn_wild = true;

            // reset the global flag
            wild_color = wild_color_now;
            wild_color_valid = false;
        }
    } else if (top.color != BLACK && top.value == 12) { // any plus2
        if (top.wild) {
            for (int i = 0; i < 2; i++) // do this 2 times
                _hand.put_on_top(deck.get_from_top()); // take a card
            top.wild = false;
            // put back the top card
            discard.put_on_top(top);

            //std::cout << _id << " I took 2 cards" << std::endl;
            return 12;
        } else {
            //std::cout << _id << " I ignored an already used +2" << std::endl;
        }
    } else if (top.color != BLACK && top.value == 10) { // any skip
        if (top.wild) {
            top.wild = false;
            // put back the top card
            discard.put_on_top(top);

            //std::cout << _id << " I was skipped" << std::endl;
            return 10;
        } else {
            //std::cout << _id << " I ignored an already used skip" << std::endl;
        }
    } else if (top.color != BLACK && top.value == 11) { // any reverse

    } else if (top.color == BLACK && top.value == 13) { // any wild
        top.wild = false;
        // put back the top card
        discard.put_on_top(top);
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
            if (deck.get_cards().size() < 10) { // if we ran out of cards
                deck.generate_deck(); // rebuild deck
                deck.shuffle(); // shuffle deck
            }
            card_t drawn = deck.get_from_top();
            _hand.put_on_top(drawn);
            if (drawn.color == top.color ||
                drawn.value == top.value)
                break;
        }

        found = find_in_hand(top);
        if (found.value < 0) {
            std::cout << "SOMETHING IS VERY WRONG IN WHOOVILLE" << std::endl;
            std::cout << "[" << found.color << " | " << found.value << "]" << std::endl;
            __DP(_hand);
            abort();
        }
    }

    // put back the top card
    discard.put_on_top(top);

    // place ur card on top
    //std::cout << _id << " I played a " << print_card(found) << std::endl;
    discard.put_on_top(found);

    if (found.value == 11) { // if its a reverse
        return 1; // let the game know its time to change direction
    } else if (found.value == 13) { // if it is a wild
        wild_color_now = static_cast<color_t>(rand() % 4); // awful hack for choosing color
        wild_color_valid = true; // raise the flag agian
        return 13; // let game know what happened
    } else if (found.value == 14) { // plus 4
        wild_color_now = static_cast<color_t>(rand() % 4); // awful hack for choosing color
        wild_color_valid = true; // raise the flag agian
        return 14; // let game know what happened
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
                return _hand.get_nth_card(i);
        } else {
            if (cards.at(i).color == BLACK||
                cards.at(i).color == c.color ||
                cards.at(i).value == c.value)
                return _hand.get_nth_card(i);
        }
    }

    // no card was found
    return {-1, BLACK, false};
}
