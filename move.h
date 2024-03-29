//
// Created by user on 29/10/2023.
//

#pragma once

#include "move.h"
#include "grid.h"

namespace move {
    int bestMove(grid &g, int depth);

    inline int64_t evaluate(grid &g);

    namespace {
        void bestScore(grid& g, int depth, int64_t& currentBestScore);
    }

}