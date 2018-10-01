#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include "deck.h"
#include "main.h"
#include "patch.h"

card_t Deck::get_from_top( void ){
    std::cout << std::endl << "{S:" << _cards.size() << "}" << std::endl;
    card_t c;
    __H(c = _cards.back(););
    std::cout << "C";
    _cards.erase(_cards.begin() + _cards.size() - 1);
    return c;
}
void Deck::put_on_top( card_t c ){
    _cards.push_back(c);

    if (c.value == 14) {
        // plus 4
        _plus_value += 4;
    } else if (c.value == 12) {
        // plus 2
        _plus_value += 2;
    }
}

int Deck::get_value_of_top( void ){
    return _cards.back().value;
}
color_t Deck::get_color_of_top( void ){
    return _cards.back().color;
}
int Deck::get_num_color (color_t c){
    int a = 0;
    for (int i = 0; i < _cards.size(); i++){
        if (_cards[i].color == c) a++;
    }
    return a;
}

void Deck::generate_deck( void ){
    _cards.clear();

    for (int i = 0; i < 4; i++){ // color loop
        for (int j = 0; j < 13; j++){
            card_t c = {j, (color_t) i};

            _cards.push_back(c);

            if ( j > 0){
                _cards.push_back(c);
            }
        }
    }

    for (int i = 0; i < _n_wild; i++)
        _cards.push_back({13, BLACK, true});

    for (int i = 0; i < _n_plus4; i++)
        _cards.push_back({14, BLACK, true});
}
void Deck::shuffle( void ){
    std::vector<card_t> n;
    for (int i = 0; i < _cards.size(); i++){
        int addr = rand() % _cards.size();
        while (_cards[addr].value < 0) addr = rand() % _cards.size(); // reroll as needed

        n.push_back(_cards[addr]);
    }

    _cards = n;
}

std::vector<card_t> Deck::get_cards(void){
    return _cards;
}
card_t Deck::get_nth_card(int n){
    card_t c = _cards[n];
    _cards.erase(_cards.begin() + n);
    return c;
}

std::string Deck::print(void){
    std::string s = "DECK : ";
    for (card_t card : _cards){
        std::string c = "!!!";

        switch (card.color){
        case RED:
            c = "R"; break;
        case GREEN:
            c = "G"; break;
        case BLUE:
            c = "B"; break;
        case YELLOW:
            c = "Y"; break;
        case BLACK:
            c = "BLK"; break;
        }

        switch (card.value) {
        case 12:
            c += "+"; break;
        case 13:
            c += "WILD"; break;
        case 14:
            c += "PLS4"; break;
        case 11:
            c += "R"; break;
        case 10:
            c += "S"; break;
        default:
            c += patch::to_string(card.value);
            break;
        }
        s += c + " ";
    }

    return s;
}
