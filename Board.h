#pragma once
#include <iostream>
#include <vector>

typedef uint64_t U64;

enum class Color
{
    BLACK = 0,
    WHITE = 1
};

enum class MoveType {
    MOVE,           //default
    PAWN_LONG,
    CAPTURE,
    PROMOTION,
    CASTLE
};


class Move {
public:
    U64 from;
    U64 to;
    MoveType moveType;

    Move(U64 from, U64 to, MoveType moveType) : from(from), to(to), moveType(moveType) {}
};


class Board {
public:
    //GAME STATE VARIABLES:
    Color activeColor;

    bool castlingWhiteKingside = true;
    bool castlingWhiteQueenside = true;
    bool castlingBlackKingside = true;
    bool castlingBlackQueenside = true;

    U64 enPassant = 0x0;

    int halfMoves = 0;
    int moves = 0;

    //BITBOARDS:
    U64 blackBB     = 0;
    U64 whiteBB     = 0;
    U64 pawnBB      = 0;
    U64 knightBB    = 0;
    U64 bishopBB    = 0;
    U64 rookBB      = 0;
    U64 queenBB     = 0;
    U64 kingBB      = 0;


    //FUNCTIONS:
    void printBoard();
    void debugPrintBB(U64 BB);
    void loadBoard(std::string fen);
    std::vector<Move> getMoves(U64 piecePositionBB);
};


void printBoard();

void loadBoard(std::string fen);

U64 getPossibleMoves(U64 piecePositionBB);