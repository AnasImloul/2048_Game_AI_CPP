#include <ctime>
#include "iostream"
#include "grid.h"
#include "move.h"

void fastIO() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

int main() {
    std::srand(std::time(nullptr));
    fastIO();

    grid g;

    int move;
    do {
        int a = 0;
        move = move::bestMove(g, 6);
        g.move(move);
        g.show();
        std::cout << "Score: " << g.getScore() << std::endl;
    } while (move != -1);

}
