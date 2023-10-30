//
// Created by user on 29/10/2023.
//

#pragma once

#include "move.h"
#include "grid.h"

int bestMove(const grid& g, int depth, int &bestScore, int &bestDir, int move=-1);

inline int evaluate(const grid& g);