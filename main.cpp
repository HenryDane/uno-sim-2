#include <iostream>
#include <vector>
#include "main.h"
#include "deck.h"
#include "player.h"

void deal(Deck &deck, std::vector<Player> players);

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
    std::cout << "11";
    deck.generate_deck();
    std::cout << "12";
    deck.shuffle();
    std::cout << "13";
    std::cout << std::endl << "SIZE" << deck.get_cards().size() << std::endl;
    deal(deck, players);

    std::cout << "1";

    while (!done) {
        for (Player p : players){
            if (p.num_cards() < 1){
                done = false;
                break;
            }

            p.do_turn(deck);

            std::cout << "======================================" << std::endl;
            for (Player q : players)
                std::cout << q.print() << std::endl;
            std::cout << std::endl << std::endl;
        }
    }

    return 0;
}

void deal(Deck &deck, std::vector<Player> players){
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < players.size(); j++){
            std::cout << "A" << std::endl;
            card_t c = deck.get_from_top();
            std::cout << "B" << std::endl;
            players[j]._hand._cards.push_back(c);
        }
    }
}
