#include "myBigChars.h"
#include "myReadkey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <cstring>
#include <iostream>

using namespace std;

void print_window(int selected)
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
            if (selected / 10 == i && selected % 10 == j) {
                mt_setbgcolor(ORANGE);
                printf("+%04X", value);
                mt_setbgcolor(GRAY);
                continue;
            }
            printf("+%04X", value);
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

    mt_gotoXY(5, 74);
    printf("%02d", selected);

    bc_box(7, 64, 3, 23);

    mt_gotoXY(7, 71);
    printf("Operation");

    mt_gotoXY(8, 71);
    printf("+00 : 00");

    bc_box(10, 64, 3, 23);

    mt_gotoXY(10, 73);
    printf("Flags");

    for (int i = 0; i < 5; i++) {
        char flags[5] = {'O', 'Z', 'M', 'C', 'I'};
        sc_regGet(i, &value);
        if (value)
            mt_setfgcolor(RED);
        else
            mt_setfgcolor(BLACK);
        mt_gotoXY(11, 71 + 2 * i);
        printf("%c", flags[i]);
    }
    mt_setfgcolor(BLACK);

    bc_box(13, 1, 10, 46);

    int A[2];
    bc_bigchartemple(A, -1);
    bc_printbigchar(A, 14, 2, BLACK, GRAY);
    bc_bigchartemple(A, (memory[selected] >> 12) % 16);
    bc_printbigchar(A, 14, 11, BLACK, GRAY);
    bc_bigchartemple(A, (memory[selected] >> 8) % 16);
    bc_printbigchar(A, 14, 20, BLACK, GRAY);
    bc_bigchartemple(A, (memory[selected] >> 4) % 16);
    bc_printbigchar(A, 14, 29, BLACK, GRAY);
    bc_bigchartemple(A, memory[selected] % 16);
    bc_printbigchar(A, 14, 38, BLACK, GRAY);

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
    printf("p  - reset");

    mt_gotoXY(19, 48);
    printf("F5 - accumulator");

    mt_gotoXY(20, 48);
    printf("F6 - instructionCounter");

    mt_gotoXY(24, 1);
    printf("Input\\Output:");
}

int main()
{
    int selected = 0, value, value_optional;
    bool exitflag = false;
    mt_clrscr();

    sc_memoryInit();
    sc_regInit();

    mt_gotoXY(90, 1);
    while (true) {
        enum keys key;
        print_window(selected);
        rk_readkey(&key);
        switch (key) {
        case Flags:
            mt_gotoXY(25, 1);
            cin >> value >> value_optional;
            if (value >= 0 && value <= 4 && value_optional >=0 && value_optional <= 1)
                sc_regSet(value, value_optional);
            break;
        case Input:
            mt_gotoXY(25, 1);
            cin >> value;
            sc_memorySet(selected, value);
            break;
        case F6_InstructionCounter:
            mt_gotoXY(25, 1);
            cin >> value;
            if (value >= 0 && value <= 99)
                selected = value;
            break;
        case Save:
            sc_memorySave("SimpleComputer");
            break;
        case Load:
            sc_memoryLoad("SimpleComputer");
            break;
        case Quit:
            exitflag = true;
            break;
        }
        if (exitflag)
            break;
        sleep(0.1);
    }

    print_window(selected);

    mt_gotoXY(90, 1);
    return 0;
}
