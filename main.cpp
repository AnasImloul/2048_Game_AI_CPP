#include <ctime>
#include "iostream"
#include "grid.h"
#include "move.h"

#pragma GCC optimize("O7")

void fastIO() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

int main() {
    // std::srand(std::time(nullptr));
    fastIO();

    grid g;

    int move;
    do {
        move = move::bestMove(g, 12);
        g.move(move);
        g.show();
        std::cout << std::endl;
    } while (move != -1);

}
