#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myReadkey.h"
#include <cstring>
#include <iostream>

using namespace std;

void print_window()
{

    mt_setbgcolor(GRAY);
    mt_setfgcolor(BLACK);
    mt_clrscr();

    bc_box(1, 1, 12, 63);
    mt_gotoXY(1, 30);
    printf("Memory");

    mt_gotoXY(2, 2);

    int index = 0;
    int value;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            mt_gotoXY(2 + i, 3 + 6 * j);
            sc_memoryGet(index, &value);
            index++;
            printf("+%.2X%.2X ", (value >> 8), (value & 0x7F));
        }
    }

    bc_box(1, 64, 3, 23);

    mt_gotoXY(1, 69);
    printf("accumulator");

    mt_gotoXY(2, 72);
    printf("+9999");

    bc_box(4, 64, 3, 23);

    mt_gotoXY(4, 66);
    printf("instructionCounter");

    mt_gotoXY(5, 72);
    printf("+0000");

    bc_box(7, 64, 3, 23);

    mt_gotoXY(7, 71);
    printf("Operation");

    mt_gotoXY(8, 71);
    printf("+00 : 00");

    bc_box(10, 64, 3, 23);

    mt_gotoXY(10, 73);
    printf("Flags");

    mt_gotoXY(11, 72);
    printf("O E V M");

    bc_box(13, 1, 10, 46);

    bc_box(13, 47, 10, 40);

    mt_gotoXY(13, 48);
    printf("Keys:");

    mt_gotoXY(14, 48);
    printf("l  - load");

    mt_gotoXY(15, 48);
    printf("s  - save");

    mt_gotoXY(16, 48);
    printf("r  - run");

    mt_gotoXY(17, 48);
    printf("t  - step");

    mt_gotoXY(18, 48);
    printf("r  - reset");

    mt_gotoXY(19, 48);
    printf("F5 - accumulator");

    mt_gotoXY(20, 48);
    printf("F6 - instructionCounter");
}

int main()
{
    mt_clrscr();

    sc_memoryInit();

    print_window();
    
    int A[2];
    bc_bigchartemple(A, -1);
    bc_printbigchar(A, 14, 2, BLACK, GRAY);
    bc_bigchartemple(A, 0);
    bc_printbigchar(A, 14, 11, BLACK, GRAY);
    bc_bigchartemple(A, 1);
    bc_printbigchar(A, 14, 20, BLACK, GRAY);
    bc_bigchartemple(A, 2);
    bc_printbigchar(A, 14, 29, BLACK, GRAY);
    bc_bigchartemple(A, 4);
    bc_printbigchar(A, 14, 38, BLACK, GRAY);
    mt_gotoXY(90,1);
    return 0;
}
