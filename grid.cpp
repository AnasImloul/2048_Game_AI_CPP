//
// Created by user on 27/10/2023.
//

#include "grid.h"
#include "cstring"
#include "iostream"


grid::grid() {
    memset(tiles, 0, sizeof(tiles));
    score = 0;
    empty = SIZE * SIZE;
    add();
    add();
}

grid::grid(const grid &g) {
    memcpy(tiles, g.tiles, sizeof(tiles));
    score = g.score;
    empty = g.empty;
    blocked = g.blocked;
}

grid::grid(int8_t tiles[SIZE][SIZE], int64_t score) {
    memcpy(this->tiles, tiles, sizeof(this->tiles));
    this->score = score;
    empty = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j : tiles[i]) {
            if (j == 0) empty++;
        }
    }
    blocked = false;

}

void grid::show() {
    for (auto & tile : tiles) {
        for (int j : tile) {
            std::cout << (j != 0 ? 1 << j : 0) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool grid::up() {
    blocked = true; // if the grid is blocked, the game is over

    for (int col = 0; col < SIZE; col++) {

        int last = -1;
        bool merged = false;
        for (int row = 0; row < SIZE; row++) {
            // if the tile is empty, skip it
            if (tiles[row][col] == 0) {
                blocked = false;
                continue;
            }

            // if this is the first tile, move it to the first row
            if (last == -1) {
                last = 0; // set the tile to the first one
                if (row != 0) {
                    tiles[last][col] = tiles[row][col];
                    tiles[row][col] = 0;
                    blocked = false;
                }
                continue;
            }

            // if the tile is the same as the last one, merge them
            if (tiles[last][col] == tiles[row][col] && !merged) {
                tiles[last][col]++;
                tiles[row][col] = 0;
                score += (1 << tiles[last][col]);
                empty++;
                blocked = false;
                merged = true;
                continue;
            }

            // if the tile is different from the last one, move it
            if (last + 1 != row) {
                tiles[++last][col] = tiles[row][col];
                tiles[row][col] = 0;
                blocked = false;
                merged = false;
                continue;
            }

            last = row;
        }
    }
    return !blocked;
}

bool grid::down() {
    blocked = true; // if the grid is blocked, the game is over

    for (int col = 0; col < SIZE; col++) {

        int last = -1;
        bool merged = false;
        for (int row = SIZE - 1; row >= 0; row--) {
            // if the tile is empty, skip it
            if (tiles[row][col] == 0) {
                blocked = false;
                continue;
            }

            // if this is the first tile, move it to the first row
            if (last == -1) {
                last = SIZE - 1; // set the tile to the first one
                if (row != SIZE - 1) {
                    tiles[last][col] = tiles[row][col];
                    tiles[row][col] = 0;
                    blocked = false;
                }
                continue;
            }

            // if the tile is the same as the last one, merge them
            if (tiles[last][col] == tiles[row][col] && !merged) {
                tiles[last][col]++;
                tiles[row][col] = 0;
                score += (1 << tiles[last][col]);
                empty++;
                blocked = false;
                merged = true;
                continue;
            }

            // if the tile is different from the last one, move it
            if (last - 1 != row) {
                tiles[--last][col] = tiles[row][col];
                tiles[row][col] = 0;
                blocked = false;
                merged = false;
                continue;
            }

            last = row;
        }
    }
    return !blocked;
}

bool grid::left() {
    blocked = true; // if the grid is blocked, the game is over

    for (int row = 0; row < SIZE; row++) {

        int last = -1;
        bool merged = false;
        for (int col = 0; col < SIZE; col++) {
            // if the tile is empty, skip it
            if (tiles[row][col] == 0) {
                blocked = false;
                continue;
            }

            // if this is the first tile, move it to the first row
            if (last == -1) {
                last = 0; // set the tile to the first one
                if (col != 0) {
                    tiles[row][last] = tiles[row][col];
                    tiles[row][col] = 0;
                    blocked = false;
                }
                continue;
            }

            // if the tile is the same as the last one, merge them
            if (tiles[row][last] == tiles[row][col] && !merged) {
                tiles[row][last]++;
                tiles[row][col] = 0;
                score += (1 << tiles[last][col]);
                empty++;
                blocked = false;
                merged = true;
                continue;
            }

            // if the tile is different from the last one, move it
            if (last + 1 != col) {
                tiles[row][++last] = tiles[row][col];
                tiles[row][col] = 0;
                blocked = false;
                merged = false;
                continue;
            }

            last = col;
        }
    }
    return !blocked;
}

bool grid::right() {
    blocked = true; // if the grid is blocked, the game is over

    for (int row = 0; row < SIZE; row++) {

        int last = -1;
        bool merged = false;
        for (int col = SIZE - 1; col >= 0; col--) {
            // if the tile is empty, skip it
            if (tiles[row][col] == 0) {
                blocked = false;
                continue;
            }

            // if this is the first tile, move it to the first row
            if (last == -1) {
                last = SIZE - 1; // set the tile to the first one
                if (col != SIZE - 1) {
                    tiles[row][last] = tiles[row][col];
                    tiles[row][col] = 0;
                    blocked = false;
                }
                continue;
            }

            // if the tile is the same as the last one, merge them
            if (tiles[row][last] == tiles[row][col] && !merged) {
                tiles[row][last]++;
                tiles[row][col] = 0;
                score += (1 << tiles[last][col]);
                empty++;
                blocked = false;
                merged = true;
                continue;
            }

            // if the tile is different from the last one, move it
            if (last - 1 != col) {
                tiles[row][--last] = tiles[row][col];
                tiles[row][col] = 0;
                blocked = false;
                merged = false;
                continue;
            }

            last = col;
        }
    }
    return !blocked;
}

bool grid::add() {

    if (empty == 0) return false;

    int index = rand() % (SIZE * SIZE), row, col;

    for (int i = 0; i < SIZE * SIZE; i++) {
        row = index / SIZE;
        col = index % SIZE;

        if (tiles[row][col] == 0) {
            tiles[row][col] = 1;
            empty--;
            return true;
        }
        index = (index + 1) % (SIZE * SIZE);
    }

    return false;

}

bool grid::move(int direction) {
    bool moved = false;

    if (direction == UP) moved = up();
    else if (direction == DOWN) moved = down();
    else if (direction == LEFT) moved = left();
    else if (direction == RIGHT) moved = right();

    if (moved) add();
    return moved;
}
