#include <iostream>
#include <vector>
#include "main.h"
#include "deck.h"
#include "player.h"

void deal(Deck &deck, std::vector<Player> &players);

color_t wild_color_now = BLACK;
bool wild_color_valid = false;

int main() {
    bool done = false;
    std::cout << "Uno Simulator 2" << std::endl;

    std::vector<Player> players;
    for (int i = 0; i < 4; i++) {
        Player p;
        p.init();
        players.push_back(p);
    }

    Deck deck;
    Deck discard;

    deck.generate_deck();
    deck.shuffle();
    __DP(deck);
    deal(deck, players);

    for(unsigned int i = 0; i < players.size(); i++) {
        std::cout << "========== [PLAYER " << i << "] ==========" << std::endl;
        std::cout << players.at(i).print() << std::endl;
    }

    int turns = 0;
    while (!done) {
        bool reversed = false;
        for (unsigned int i = 0; i < players.size(); i += ((reversed == false) ? 1 : -1)){
            if (players[i].do_turn(deck, discard) == 1) reversed = !reversed;

            std::cout << std::endl << "========== [TURN: " << turns << "] =========" << std::endl;
            std::cout << "TOP DECK:" << print_card(deck.view_top()) << " TOP DISCARD:" << print_card(discard.view_top()) << std::endl;
            for(unsigned int i = 0; i < players.size(); i++) {
                std::cout << "========== [PLAYER " << i << "] ==========" << std::endl;
                std::cout << players.at(i).print() << std::endl;
            }

            turns++;
            if (turns > 50) return 5;
        }
    }

    return 0;
}

void deal(Deck &deck, std::vector<Player> &players){
    for (int i = 0; i < 7; i++){
        for (unsigned int j = 0; j < players.size(); j++){
            //std::cout << "A" << std::endl;
            card_t c = deck.get_from_top();
            //std::cout << "B" << std::endl;
            players[j]._hand._cards.push_back(c);
        }
    }
}
