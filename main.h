#ifndef MAIN_H
#define MAIN_H

#define __H(x) try { x } catch (std::exception &e) { std::cout << e.what() << std::endl; abort(); }
#define __DP(x) std::cout << x.print() << std::endl;

enum color_t {
    RED, GREEN, YELLOW, BLUE, BLACK
};

struct card_t {
    /*
    0 - 9 : normal value cards
    10    : skip
    11    : reverse
    12    : +2
    13    : wild
    14    : +4
    */
    int value;
    color_t color;
    bool wild;
};

extern color_t wild_color_now;
extern bool wild_color_valid;

#endif // MAIN_H
