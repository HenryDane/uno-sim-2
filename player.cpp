#include <iostream>
#include "main.h"
#include "player.h"

/*
    TODO:
    -   ADD CARD SELECTION ALGORITHM
    -   ADD STACKING OF EFFECTS
    -   ADD WILD CARD MECHANICS
    -   WHAT IF NO GOOD CARDS
    -   TEST
*/

void Player::init(void){
    return;
}
int Player::num_cards(void){
    return _hand.get_cards().size();
}
void Player::take_card(card_t c){
    _hand.put_on_top(c);
}
std::string Player::print(void){
    return _hand.print();
}

/*
    function determines basic game mechanics
*/
int Player::do_turn(Deck &deck){
    std::cout << "2";
    switch (deck.get_value_of_top()){
        case 13: // wild
            {
                std::cout << "3";
                card_t d = find_in_hand({-1, deck.get_color_of_top(), false});
                std::cout << "4";
                while (d.value < 0) {
                    d = deck.get_from_top();
                    _hand.put_on_top(d);
                }
                deck.put_on_top(d); // handles modifier bonuses
            }
            break;
        case 14: // plus4
            {
                for (int i = 0; i < 4; i++)
                    _hand.put_on_top(deck.get_from_top()); // add 4 cards
            }
            break;
        case 12: // plus2
            {
                for (int i = 0; i < 2; i++)
                    _hand.put_on_top(deck.get_from_top()); // add 2 cards
            }
            break;
        case 10: // skip
            return 10;
        case 11: // reverse does nothing rn
            return 11;
        default:
            std::cout << "5";
            card_t d = find_in_hand({deck.get_value_of_top(), deck.get_color_of_top(), false});
            std::cout << "6";
            while (d.value < 0) {
                d = deck.get_from_top();
                _hand.put_on_top(d);
            }
            std::cout << "7";
            deck.put_on_top(d); // handles modifier bonuses
            break;
    }

    return 0;
}

/*
    different versions of this are OK -- this is how the player finds their card
*/
card_t Player::find_in_hand(card_t c){
    std::cout << "9";
    std::vector<card_t> cards = _hand.get_cards();

    //              R  G  B  Y  *
//    int cards[5] = {0, 0, 0, 0, 0}; // keep track of number of cards of each color
    std::cout << "8";
    int i = 0;
    bool found = false;
    for ( ; i < cards.size(); i++){
        if (c.value > 0) {
            if (cards[i].color == c.color ||
                cards[i].color == BLACK ||
                cards[i].value == c.value) {
                found = true;
                break;
            }
        } else {
            if (cards[i].color == c.color ||
                cards[i].color == BLACK) {
                found = true;
                break;
            }
        }
    }

    std::cout << "10";

    if (found) {
        return _hand.get_nth_card(i);
    } else {
        return {-1, BLACK, false};
    }
}
