#include <iostream>
#include "Board.h"

//void printBinary(U64 number) {
//    printf("\n");
//    for (int i = 63; i >= 0; i--) {
//        U64 index = static_cast<U64>(1L) << i;
//        printf("%ull", (number & index) >> i);
//    }
//    printf("\n");
//}

int main()
{
    Board board;
    board.loadBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    board.printBoard();

    //board.debugPrintBB(board.whiteBB);

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
