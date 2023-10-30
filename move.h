//
// Created by user on 29/10/2023.
//

#pragma once

#include "move.h"
#include "grid.h"

namespace move {
    int bestMove(const grid &g, int depth);

    inline int evaluate(const grid &g);

    namespace {
        int bestMoveHelper(const grid& g, int depth, int &bestScore, int &bestDir, int move);
    }

}