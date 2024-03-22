#pragma once
#include <iostream>

typedef uint64_t U64;

enum Color
{
    Black = 0,
    White = 1
};


void printBoard();

void loadBoard(std::string fen);