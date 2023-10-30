//
// Created by user on 29/10/2023.
//

#include "move.h"
#include <iostream>

#define max(a, b) ((a) > (b) ? (a) : (b))

namespace move {
    int bestMove(const grid& g, int depth) {
        int bestScore = 0, bestDir = -1;
        bestMoveHelper(g, depth, bestScore, bestDir, -1);
        return bestDir;
    }

    inline int evaluate(const grid& g) {
        return (g.getEmpty() << 16) + g.getScore();
    }

    namespace {
        int bestMoveHelper(const grid& g, int depth, int &bestScore, int &bestDir, int move) {
            if (depth == 0 || g.isBlocked()) {
                return evaluate(g);
            }

            if (move == -1) {
                // if the move is -1, we are at the root of the tree
                // we will have dynamic depth based on the number of empty tiles
                // the less empty tiles, the more depth
                depth = max(depth * (SIZE - g.getEmpty() / SIZE) / SIZE, 4);
            }

            for (int dir : DIRECTIONS) {
                grid g1(g);
                g1.move(dir);
                int score = bestMoveHelper(g1, depth - 1, bestScore, bestDir, (move == -1 ? dir : move));
                if (score > bestScore) {
                    bestScore = score;
                    bestDir = move;
                }
            }

            return bestScore;
        }
    }

}