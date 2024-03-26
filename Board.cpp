#include "Board.h"
    
//constants
#define rank_BB(nr) (rank_BB[nr-1])

const U64 rank_BB[8] = {
    0xFF00000000000000,
    0x00FF000000000000,
    0x0000FF0000000000,
    0x000000FF00000000,
    0x00000000FF000000,
    0x0000000000FF0000,
    0x000000000000FF00,
    0x00000000000000FF
};

const U64 file_BB[8] = {
    0b0000000100000001000000010000000100000001000000010000000100000001,
    0b0000001000000010000000100000001000000010000000100000001000000010,
    0b0000010000000100000001000000010000000100000001000000010000000100,
    0b0000100000001000000010000000100000001000000010000000100000001000,
    0b0001000000010000000100000001000000010000000100000001000000010000,
    0b0010000000100000001000000010000000100000001000000010000000100000,
    0b0100000001000000010000000100000001000000010000000100000001000000,
    0b1000000010000000100000001000000010000000100000001000000010000000
};


//TERMINAL COLOR CONSTANTS
#define BLACK_FOREGROUND "\x1b[30m"
#define WHITE_FOREGROUND "\x1b[37m"
#define WHITE_BACKGROUND "\x1b[47m"
#define BLACK_BACKGROUND "\x1b[40m"
#define RESET_BACKGROUND "\x1b[49m"
#define RESET_FOREGROUND "\x1b[39m"

void Board::printBoard() {
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
        printf("  %d", 8 - rank);
        printf("\n");
    }
    printf("\n    a  b  c  d  e  f  g  h  \n\n");
}

void Board::debugPrintBB(U64 BB) {
    printf("    a  b  c  d  e  f  g  h  \n\n");
    for (int rank = 0; rank < 8; rank++) {
        printf("%d  ", 8 - rank);
        //files
        for (int file = 0; file < 8; file++) {
            U64 squareBB = 1ULL << (8 * rank + file);
            U64 figureBB = BB & squareBB;
            printf(" %u ", figureBB ? 1 : 0);
        }
        printf(" %d", 8 - rank);
        printf("\n");
    }
    printf("\n    a  b  c  d  e  f  g  h  \n\n");

}

void Board::loadBoard(std::string fen) {
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

/*
* move:
* U64 from
* U64 to
* MoveType moveType
*/


std::vector<Move> Board::getMoves(U64 piecePositionBB) {
    std::vector<Move> moves;
    moves.reserve(8);
    //TODO: zoptymalizowac potem na podstawie mierzonej sredniej ilosci wyliczanych ruchow

    U64 bothBB = blackBB | whiteBB;

    if (activeColor == Color::WHITE) {
        if (piecePositionBB & whiteBB) {
            if (piecePositionBB & pawnBB) {
                bool isPromotioinPossible = piecePositionBB & rank_BB(7);
                
                //right square attack
                U64 move = ((piecePositionBB << 9) & blackBB);
                if (move) {
                    isPromotioinPossible ?
                        moves.push_back(Move(piecePositionBB, move, MoveType::PROMOTION))
                        :
                        moves.push_back(Move(piecePositionBB, move, MoveType::CAPTURE));
                }

                //left square attack
                move = ((piecePositionBB << 7) & blackBB);
                if (move) {
                    isPromotioinPossible ?
                        moves.push_back(Move(piecePositionBB, move, MoveType::PROMOTION))
                        :
                        moves.push_back(Move(piecePositionBB, move, MoveType::CAPTURE));
                }

                // move one square ahead
                move = (piecePositionBB << 8) & (~bothBB);
                if (move) {
                    isPromotioinPossible ?
                        moves.push_back(Move(piecePositionBB, move, MoveType::PROMOTION))
                        :
                        moves.push_back(Move(piecePositionBB, move, MoveType::CAPTURE));

                    //TODO: optimization
                    if (piecePositionBB & rank_BB(2)) {
                        move = (move << 8) & ~bothBB;
                        moves.push_back( Move(piecePositionBB, move, MoveType::PAWN_LONG) );
                    }
                }


                //TODO: promotion
                if (piecePositionBB & rank_BB(7)) {

                }
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
            return moves;
        }
    }

    return moves;
}