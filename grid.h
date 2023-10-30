//
// Created by user on 27/10/2023.
//

#include <stdint.h>

#pragma once

#define SIZE 4

enum direction {
    UP=0,
    DOWN=1,
    LEFT=2,
    RIGHT=3
};

const int DIRECTIONS[4] = {UP, DOWN, LEFT, RIGHT};


class grid {
public:
    grid();

    grid(int8_t tiles[SIZE][SIZE], int64_t score);

    grid(const grid &g);

    void show();

    bool up();

    bool down();

    bool left();

    bool right();

    bool move(int direction);

    inline int32_t getScore() const { return score; }
    inline int16_t getEmpty() const { return empty; }
    inline bool isBlocked() const { return blocked; }

private:

    bool add();

    int8_t tiles[SIZE][SIZE]; // tiles on the grid (0 = empty, 2^x = tile with value x)
    int32_t score; // current score
    int16_t empty; // number of empty tiles
    bool blocked; // if the grid is blocked, the game is over

};
