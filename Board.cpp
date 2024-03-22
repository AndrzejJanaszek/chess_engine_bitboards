#include "Board.h"

//GMAME STATE VARIABLES:
Color activeColor = Color::White;

//castling [bool]
bool castlingWhiteKingside = true;
bool castlingWhiteQueenside = true;
bool castlingBlackKingside = true;
bool castlingBlackQueenside = true;

U64 enPassant = 0x0;

int halfMoves = 0;
int moves = 0;

//constants
const U64 rank8_BB = 0x00000000000000FF;
const U64 rank7_BB = 0x000000000000FF00;
const U64 rank6_BB = 0x0000000000FF0000;
const U64 rank5_BB = 0x00000000FF000000;
const U64 rank4_BB = 0x000000FF00000000;
const U64 rank3_BB = 0x0000FF0000000000;
const U64 rank2_BB = 0x00FF000000000000;
const U64 rank1_BB = 0xFF00000000000000;

const U64 fileA_BB = 0b0000000100000001000000010000000100000001000000010000000100000001;
const U64 fileB_BB = 0b0000001000000010000000100000001000000010000000100000001000000010;
const U64 fileC_BB = 0b0000010000000100000001000000010000000100000001000000010000000100;
const U64 fileD_BB = 0b0000100000001000000010000000100000001000000010000000100000001000;
const U64 fileE_BB = 0b0001000000010000000100000001000000010000000100000001000000010000;
const U64 fileF_BB = 0b0010000000100000001000000010000000100000001000000010000000100000;
const U64 fileG_BB = 0b0100000001000000010000000100000001000000010000000100000001000000;
const U64 fileH_BB = 0b1000000010000000100000001000000010000000100000001000000010000000;

//bitboards
U64 blackBB = 0x0000000000000000;
U64 whiteBB = 0x0000000000000000;
U64 pawnBB = 0x0000000000000000;
U64 knightBB = 0x0000000000000000;
U64 bishopBB = 0x0000000000000000;
U64 rookBB = 0x0000000000000000;
U64 queenBB = 0x0000000000000000;
U64 kingBB = 0x0000000000000000;

//TERMINAL COLOR CONSTANTS
#define BLACK_FOREGROUND "\x1b[30m"
#define WHITE_FOREGROUND "\x1b[37m"
#define WHITE_BACKGROUND "\x1b[47m"
#define BLACK_BACKGROUND "\x1b[40m"
#define RESET_BACKGROUND "\x1b[49m"
#define RESET_FOREGROUND "\x1b[39m"

void printBoard() {
    //ranks

    U64 bothBB = blackBB | whiteBB;
    printf("    a  b  c  d  e  f  g  h  \n\n");
    for (int rank = 0; rank < 8; rank++) {
        printf("%d  ", 8 - rank);
        //files
        for (int file = 0; file < 8; file++) {
            //_____________________________________________________
            if ((file + rank) % 2 == 0) {
                std::cout << BLACK_FOREGROUND;
                std::cout << WHITE_BACKGROUND;
            }
            else{
                std::cout << WHITE_FOREGROUND;
                std::cout << BLACK_BACKGROUND;
            }


            U64 squareBB = 1ULL << (8 * rank + file);
            //U64 squareBB = static_cast<U64>(1L) << (8 * rank + file);
            U64 figureBB = bothBB & squareBB;
            //if something

            printf(" ");
            if (figureBB) {
                if (figureBB & pawnBB) {
                    if (figureBB & whiteBB)
                        printf("P");
                    else
                        printf("p");
                }
                else if (figureBB & knightBB) {
                    if (figureBB & whiteBB)
                        printf("N");
                    else
                        printf("n");
                }
                else if (figureBB & bishopBB) {
                    if (figureBB & whiteBB)
                        printf("B");
                    else
                        printf("b");
                }
                else if (figureBB & rookBB) {
                    if (figureBB & whiteBB)
                        printf("R");
                    else
                        printf("r");
                }
                else if (figureBB & queenBB) {
                    if (figureBB & whiteBB)
                        printf("Q");
                    else
                        printf("q");
                }
                else if (figureBB & kingBB) {
                    if (figureBB & whiteBB)
                        printf("K");
                    else
                        printf("k");
                }
            }
            else {
                printf(" ");
            }
            printf(" ");

            std::cout << RESET_BACKGROUND;
            std::cout << RESET_FOREGROUND;
        }
        printf(" %d", 8 - rank);
        printf("\n");
    }
    printf("\n    a  b  c  d  e  f  g  h  \n\n");
}

void loadBoard(std::string fen) {
    U64 squareBB = 1ULL;
    //U64 squareBB = static_cast<U64>(1L);
    for (int i = 0; i < fen.length(); i++) {
        char c = fen[i];

        if (c == '/') {
            continue;
        }

        if (c > '0' && c < '9') {
            squareBB = squareBB << (c - '0');   //skip next n-1 squares
            continue;
        }


        if (c == 'P') {
            whiteBB = whiteBB | squareBB;
            pawnBB = pawnBB | squareBB;
        }
        else if (c == 'p') {
            blackBB = blackBB | squareBB;
            pawnBB = pawnBB | squareBB;
        }
        else if (c == 'N') {
            whiteBB = whiteBB | squareBB;
            knightBB = knightBB | squareBB;
        }
        else if (c == 'n') {
            blackBB = blackBB | squareBB;
            knightBB = knightBB | squareBB;
        }
        else if (c == 'B') {
            whiteBB = whiteBB | squareBB;
            bishopBB = bishopBB | squareBB;
        }
        else if (c == 'b') {
            blackBB = blackBB | squareBB;
            bishopBB = bishopBB | squareBB;
        }
        else if (c == 'R') {
            whiteBB = whiteBB | squareBB;
            rookBB = rookBB | squareBB;
        }
        else if (c == 'r') {
            blackBB = blackBB | squareBB;
            rookBB = rookBB | squareBB;
        }
        else if (c == 'Q') {
            whiteBB = whiteBB | squareBB;
            queenBB = queenBB | squareBB;
        }
        else if (c == 'q') {
            blackBB = blackBB | squareBB;
            queenBB = queenBB | squareBB;
        }
        else if (c == 'K') {
            whiteBB = whiteBB | squareBB;
            kingBB = kingBB | squareBB;
        }
        else if (c == 'k') {
            blackBB = blackBB | squareBB;
            kingBB = kingBB | squareBB;
        }

        squareBB = squareBB << 1;
    }
}

U64 getMoves(U64 piecePositionBB) {
    U64 bothBB = blackBB | whiteBB;

    if (activeColor == Color::White) {
        if (piecePositionBB & whiteBB) {
            if (piecePositionBB & pawnBB) {
                //attacks
                //is enemy on attacking positions
                U64 attacks = ((piecePositionBB << 9) & blackBB)
                            | ((piecePositionBB << 7) & blackBB);

                U64 move = ~((piecePositionBB << 8) & bothBB);
                U64 doubleMove = 0Ull;
                //TODO: optimization
                if (piecePositionBB & rank2_BB) {
                    if (move) {
                        doubleMove = ~((move << 8) & bothBB);
                    }
                }

                //TODO: promotion
            }
            else if (piecePositionBB & knightBB) {

            }
            else if (piecePositionBB & bishopBB) {

            }
            else if (piecePositionBB & rookBB) {

            }
            else if (piecePositionBB & queenBB) {

            }
            else if (piecePositionBB & kingBB) {

            }
        }
        else
        {
            // Empty position or enemy piece
            // no moves available
            return 0ULL;
        }
    }

    return 0Ull;
}