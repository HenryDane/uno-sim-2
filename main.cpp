#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "deck.h"
#include "player.h"

void deal(Deck &deck, std::vector<Player> &players);
int simulate_game(int n_players);

color_t wild_color_now = BLACK;
bool wild_color_valid = false;

int main() {
    srand (time(NULL));

    std::cout << "Uno Simulator 2" << std::endl;

    int p1, p2, p3, p4;
    p1 = p2 = p3 = p4 = 0;
    for (int i = 0; i < 1000; i++){
        int a = simulate_game(2);
        switch (a) {
            case 0: p1++; break;
            case 1: p2++; break;
            case 2: p3++; break;
            case 3: p4++; break;
            default:
                std::cout << "A: " << a << std::endl;
        }
    }
    std::cout << p1 << " " << p2 << " " << p3 << " " << p4 << std::endl;

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

int simulate_game(int n_players) {
    std::cout << "-----------------New Game-----------------" << std::endl;
    bool done = false;
    std::vector<Player> players;
    for (int i = 0; i < n_players; i++) {
        Player p;
        p.init(i);
        players.push_back(p);
    }

    Deck deck;
    Deck discard;

    deck.generate_deck();
    deck.shuffle();
    //__DP(deck);
    deal(deck, players);

    for(unsigned int i = 0; i < players.size(); i++) {
        //std::cout << "========== [PLAYER " << i << "] ==========" << std::endl;
        //std::cout << players.at(i).print() << std::endl;
    }

    int turns = 0;
    int cycle = 0;
    while (!done) {
        bool reversed = false;
        //for (unsigned int i = 0; i < players.size(); i += ((reversed == false) ? 1 : -1)){
        unsigned int i = 0;
        for /* ever */ ( ; ; cycle += ((reversed == false) ? 1 : -1)){
            // FIX THIS ASAP
            if (cycle >= 0) {
                i = cycle % n_players;
            } else {
                i = ((n_players - abs(cycle % n_players)) >= n_players) ? 0 : n_players - abs(cycle % n_players);
            }
            //std::cout << cycle << " [" << i << "] ";
            if (players[i].do_turn(deck, discard) == 1) reversed = !reversed;

            //std::cout << std::endl;
            //std::cout << "========== [TURN: " << turns << "] =========" << std::endl;
            //std::cout << "TOP DECK:" << print_card(deck.view_top()) << " TOP DISCARD:" << print_card(discard.view_top()) << std::endl;
            //std::cout << "SIZE DECK:" << deck.num_cards() << " SIZE DISCARD:" << discard.num_cards() << std::endl;
            for(unsigned int i = 0; i < players.size(); i++) {
                //std::cout << "========== [PLAYER " << i << "] ==========" << std::endl;
                //std::cout << players.at(i).print() << std::endl;
            }

            turns++;
            for (int i = 0; i < players.size(); i++)
                if (players[i].num_cards() == 0) return i;
            //if (turns > 50) return 5;

            if (deck.num_cards() < 10){
                deck.generate_deck();
                deck.shuffle();
            }
        }

        std::cout << "Got out of loop???" << std::endl;
    }

    return 1000;
}
