//
// Created by user on 27/10/2023.
//

#include "grid.h"
#include "cstring"
#include "iostream"

#define max(a, b) ((a) > (b) ? (a) : (b))

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
}

grid::grid(int8_t tiles[SIZE * SIZE], int64_t score) {
    memcpy(this->tiles, tiles, sizeof(this->tiles));
    this->score = score;
    empty = 0;
    for (int i = 0; i < SIZE * SIZE; i++) {
        if (tiles[i] == 0) empty++;
    }
}

inline int length(long long n) {
    int count = 1;
    while (n >= 10) {
        count++;
        n /= 10;
    }
    return count;
}

inline int maxLength(int8_t tiles[SIZE * SIZE]) {
    int result = 0;
    for (int i = 0; i < SIZE * SIZE; i++) {
        result = max(result, length(1 << tiles[i]));
    }
    return result;
}

void grid::show() {
    int maxLength1 = maxLength(tiles);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            long long value = (tiles[i * SIZE + j] != 0 ? (1 << tiles[i * SIZE + j]) : 0);
            std::cout << value << std::string(maxLength1 - length(value), ' ') << " ";
        }
        if (i + 1 == SIZE) {
            std::cout << std::endl;
        } else {
            for (int i = 0; i < 1 + maxLength1 / 3; i++)
                std::cout << std::endl;
        }
    }
    std::cout << "Score: " << score << std::endl;


}

bool grid::up() {
    bool blocked = true; // if the grid is blocked, the game is over

    for (int col = 0; col < SIZE; col++) {

        int last = -1;
        bool merged = false;
        for (int row = 0; row < SIZE; row++) {
            // if the tile is empty, skip it
            if (tiles[row * SIZE + col] == 0) {
                continue;
            }

            // if this is the first tile, move it to the first row
            if (last == -1) {
                last = 0; // set the tile to the first one
                if (row != 0) {
                    tiles[last * SIZE + col] = tiles[row * SIZE + col];
                    tiles[row * SIZE + col] = 0;
                    blocked = false;
                }
                continue;
            }

            // if the tile is the same as the last one, merge them
            if (tiles[last * SIZE + col] == tiles[row * SIZE + col] && !merged) {
                tiles[last * SIZE + col]++;
                tiles[row * SIZE + col] = 0;
                score += (1 << tiles[last * SIZE + col]);
                empty++;
                blocked = false;
                merged = true;
                continue;
            }

            // if the tile is different from the last one, move it
            if (last + 1 != row) {
                tiles[++last * SIZE + col] = tiles[row * SIZE + col];
                tiles[row * SIZE + col] = 0;
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
    bool blocked = true; // if the grid is blocked, the game is over

    for (int col = 0; col < SIZE; col++) {

        int last = -1;
        bool merged = false;
        for (int row = SIZE - 1; row >= 0; row--) {
            // if the tile is empty, skip it
            if (tiles[row * SIZE + col] == 0) {
                continue;
            }

            // if this is the first tile, move it to the first row
            if (last == -1) {
                last = SIZE - 1; // set the tile to the first one
                if (row != SIZE - 1) {
                    tiles[last * SIZE + col] = tiles[row * SIZE + col];
                    tiles[row * SIZE + col] = 0;
                    blocked = false;
                }
                continue;
            }

            // if the tile is the same as the last one, merge them
            if (tiles[last * SIZE + col] == tiles[row * SIZE + col] && !merged) {
                tiles[last * SIZE + col]++;
                tiles[row * SIZE + col] = 0;
                score += (1 << tiles[last * SIZE + col]);
                empty++;
                blocked = false;
                merged = true;
                continue;
            }

            // if the tile is different from the last one, move it
            if (last - 1 != row) {
                tiles[--last * SIZE + col] = tiles[row * SIZE + col];
                tiles[row * SIZE + col] = 0;
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
    bool blocked = true; // if the grid is blocked, the game is over

    for (int row = 0; row < SIZE; row++) {

        int last = -1;
        bool merged = false;
        for (int col = 0; col < SIZE; col++) {
            // if the tile is empty, skip it
            if (tiles[row * SIZE + col] == 0) {
                continue;
            }

            // if this is the first tile, move it to the first row
            if (last == -1) {
                last = 0; // set the tile to the first one
                if (col != 0) {
                    tiles[row * SIZE + last] = tiles[row * SIZE + col];
                    tiles[row * SIZE + col] = 0;
                    blocked = false;
                }
                continue;
            }

            // if the tile is the same as the last one, merge them
            if (tiles[row * SIZE + last] == tiles[row * SIZE + col] && !merged) {
                tiles[row * SIZE + last]++;
                tiles[row * SIZE + col] = 0;
                score += (1 << tiles[row * SIZE + last]);
                empty++;
                blocked = false;
                merged = true;
                continue;
            }

            // if the tile is different from the last one, move it
            if (last + 1 != col) {
                tiles[row * SIZE + ++last] = tiles[row * SIZE + col];
                tiles[row * SIZE + col] = 0;
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
    bool blocked = true; // if the grid is blocked, the game is over

    for (int row = 0; row < SIZE; row++) {

        int last = -1;
        bool merged = false;
        for (int col = SIZE - 1; col >= 0; col--) {
            // if the tile is empty, skip it
            if (tiles[row * SIZE + col] == 0) {
                continue;
            }

            // if this is the first tile, move it to the first row
            if (last == -1) {
                last = SIZE - 1; // set the tile to the first one
                if (col != SIZE - 1) {
                    tiles[row * SIZE + last] = tiles[row * SIZE + col];
                    tiles[row * SIZE + col] = 0;
                    blocked = false;
                }
                continue;
            }

            // if the tile is the same as the last one, merge them
            if (tiles[row * SIZE + last] == tiles[row * SIZE + col] && !merged) {
                tiles[row * SIZE + last]++;
                tiles[row * SIZE + col] = 0;
                score += (1 << tiles[row * SIZE + last]);
                empty++;
                blocked = false;
                merged = true;
                continue;
            }

            // if the tile is different from the last one, move it
            if (last - 1 != col) {
                tiles[row * SIZE + --last] = tiles[row * SIZE + col];
                tiles[row * SIZE + col] = 0;
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
    int8_t value = (int8_t)((rand() % 10 < 9) ? 1 : 2);

    for (int i = 0; i < SIZE * SIZE; i++) {
        if (tiles[index] == 0) {
            tiles[index] = value;
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
