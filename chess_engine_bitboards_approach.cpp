#include <iostream>

typedef uint64_t U64;
// ranks = rows
// files = columns

//Board bitboards

U64 rankBB = 0x00000000000000FF;
U64 fileBB = 0b0000000100000001000000010000000100000001000000010000000100000001;

U64 blackBB =   0x000000000000FFFF;
U64 whiteBB =   0xFFFF000000000000;
U64 pawnBB =    0x00FF00000000FF00;
U64 knightBB =  0b0100001000000000000000000000000000000000000000000000000001000010;
U64 bishopBB =  0b0010010000000000000000000000000000000000000000000000000000100100;
U64 rookBB =    0b1000000100000000000000000000000000000000000000000000000010000001;
U64 queenBB =   0b0000100000000000000000000000000000000000000000000000000000001000;
U64 kingBB =    0b0001000000000000000000000000000000000000000000000000000000010000;
                //hgfedcbahgfedcbahgfedcbahgfedcbahgfedcbahgfedcbahgfedcbahgfedcba

void printBinary(U64 number) {
    printf("\n");
    for (int i = 63; i >= 0; i--) {
        U64 index = static_cast<U64>(1L) << i;
        printf("%u", (number & index) >> i);
    }
    printf("\n");
}

void printBoard() {
    //ranks

    U64 bothBB = blackBB | whiteBB;
    printf("   a b c d e f g h  \n\n");
    for (int rank = 0; rank < 8; rank++) {
        printf("%d  ", 8-rank);
        //files
        for (int file = 0; file < 8; file++) {
            //_____________________________________________________
            U64 squareBB = static_cast<U64>(1L) << (8 * rank + file);
            U64 figureBB = bothBB & squareBB;
            //if something
            if (figureBB) {
                if (figureBB & pawnBB) {
                    if(figureBB & whiteBB)
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
                    printf("0");
                /*if ((rank + file) % 2 == 0)
                    printf("x");
                else
                    printf(" ");*/
            }
            printf(" ");
        }
        printf(" %d", 8 - rank);
        printf("\n");
    }
    printf("\n   a b c d e f g h  ");
}

void setBoardFromFen(std::string fen) {
    int _rank = 0, _file = 0;
    for (int i = 0; i < fen.length(); i++) {
        char c = fen[i];

        if (c == '/') {
            _rank++;
            _file = 0;
            continue;
        }

        if(c > )
    }
}

int main()
{
    printBoard();

    printf("\n\n\n\n\t__END__\n");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
