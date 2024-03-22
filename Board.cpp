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
U64 rankBB = 0x00000000000000FF;
U64 fileBB = 0b0000000100000001000000010000000100000001000000010000000100000001;

//bitboards
U64 blackBB = 0x0000000000000000;
U64 whiteBB = 0x0000000000000000;
U64 pawnBB = 0x0000000000000000;
U64 knightBB = 0x0000000000000000;
U64 bishopBB = 0x0000000000000000;
U64 rookBB = 0x0000000000000000;
U64 queenBB = 0x0000000000000000;
U64 kingBB = 0x0000000000000000;


void printBoard() {
    //ranks
#define BLACK_FOREGROUND "\x1b[30m"
#define WHITE_FOREGROUND "\x1b[37m"
#define WHITE_BACKGROUND "\x1b[47m"
#define BLACK_BACKGROUND "\x1b[40m"
#define RESET_BACKGROUND "\x1b[49m"
#define RESET_FOREGROUND "\x1b[39m"

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

