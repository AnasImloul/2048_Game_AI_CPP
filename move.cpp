#include "move.h"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

#define max(a, b) ((a) > (b) ? (a) : (b))

namespace move {
    int bestMove(grid& g, int depth) {
        std::vector<std::thread> threads;
        int64_t scores[16];
        for (int i = 0; i < 16; i++) scores[i] = -1;

        for (int first : DIRECTIONS) {
            for (int second : DIRECTIONS) {
                threads.emplace_back([&](int dir) {
                    grid g1(g);
                    if (g1.move(dir / 4)) {
                        grid g2(g1);
                        if (g2.move(dir % 4)) {
                            int64_t score = -1;
                            bestScore(g2, depth - 2, score);
                            scores[dir] = score;
                        } else {
                            int64_t score = evaluate(g1) >> depth;
                            scores[dir] = score;
                        }
                    }
                }, first * 4 + second);
            }
        }

        for (auto& thread : threads) {
            thread.join();
        }

        int bestDir = -1;
        int64_t _bestScore = -1;

        for (int i = 0; i < 16; i++) {
            int64_t score = scores[i];

            if (score > _bestScore) {
                _bestScore = score;
                bestDir = i / 4;
            }
        }

        return bestDir;

    }

    inline int64_t evaluate(grid& g) { return (g.getEmpty() << 16) + g.getScore(); }

    namespace {
        void bestScore(grid& g, int depth, int64_t& currentBestScore) {

            int64_t score = evaluate(g) >> depth;
            currentBestScore = max(currentBestScore, score);

            if (depth == 0)
                return;

            for (int dir : DIRECTIONS) {
                grid g1(g);
                if (g1.move(dir)) {
                    bestScore(g1, depth - 1, currentBestScore);
                }
            }
        }
    }

}