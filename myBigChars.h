// enter_alt_charset_mode=^N
// exit_alt_charset_mode=^O
/*
         Glyph                       ACS            Ascii     acsc     acsc
         Name                        Name           Default   Char     Value
         ────────────────────────────────────────────────────────────────────
         arrow pointing right        ACS_RARROW     >         +        0x2b
         arrow pointing left         ACS_LARROW     <         ,        0x2c
         arrow pointing up           ACS_UARROW     ^         -        0x2d
         arrow pointing down         ACS_DARROW     v         .        0x2e
         solid square block          ACS_BLOCK      #         0        0x30
         diamond                     ACS_DIAMOND    +         `        0x60
         checker board (stipple)     ACS_CKBOARD    :         a        0x61
         degree symbol               ACS_DEGREE     \         f        0x66
         plus/minus                  ACS_PLMINUS    #         g        0x67
         board of squares            ACS_BOARD      #         h        0x68
         lantern symbol              ACS_LANTERN    #         i        0x69
         lower right corner          ACS_LRCORNER   +         j        0x6a
         upper right corner          ACS_URCORNER   +         k        0x6b
         upper left corner           ACS_ULCORNER   +         l        0x6c
         lower left corner           ACS_LLCORNER   +         m        0x6d
         large plus or crossover     ACS_PLUS       +         n        0x6e
         scan line 1                 ACS_S1         ~         o        0x6f
         scan line 3                 ACS_S3         -         p        0x70
         horizontal line             ACS_HLINE      -         q        0x71
         scan line 7                 ACS_S7         -         r        0x72
         scan line 9                 ACS_S9         _         s        0x73
         tee pointing right          ACS_LTEE       +         t        0x74
         tee pointing left           ACS_RTEE       +         u        0x75
         tee pointing up             ACS_BTEE       +         v        0x76
         tee pointing down           ACS_TTEE       +         w        0x77
         vertical line               ACS_VLINE      |         x        0x78
         less-than-or-equal-to       ACS_LEQUAL     <         y        0x79
         greater-than-or-equal-to    ACS_GEQUAL     >         z        0x7a
         greek pi                    ACS_PI         *         {        0x7b
         not-equal                   ACS_NEQUAL     !         |        0x7c
         UK pound sign               ACS_STERLING   f         }        0x7d
         bullet                      ACS_BULLET     o         ~        0x7e
*/

#pragma once
#include "myTerm.h"

int bc_printA(char* str)
{
    printf("\E(0%s", str);
    printf("\E(B");
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2) // x2 = height, y2 = width
{
    // UP
    mt_gotoXY(x1, y1);
    printf("\u250C"); // ┌
    for (int i = 1; i < y2 - 1; i++) {
        bc_printA("\u2500"); // ─
    }
    bc_printA("\u2510"); // ┐

    // LEFT + RIGHT
    for (int i = 1; i < x2 - 1; i++) {
        mt_gotoXY(x1 + i, y1);
        bc_printA("\u2502"); // │
        mt_gotoXY(x1 + i, y1 + y2 - 1);
        bc_printA("\u2502"); // │
    }

    // DOWN
    mt_gotoXY(x1 + x2 - 1, y1); // └
    bc_printA("\u2514");
    for (int i = 1; i < y2 - 1; i++) {
        bc_printA("\u2500"); // ─
    }
    bc_printA("\u2518"); // ┘

    return 0;
}

int bc_bigchartemple(int* A, int number)
{
    switch (number) {
    case 0:
        A[0] = 0xC3C3C33C;
        A[1] = 0x3CC3C3C3;
        return 0;
    case 1:
        A[0] = 0x181F1E18;
        A[1] = 0xFF181818;
        return 0;
    case 2:
        A[0] = 0x30C0C33C;
        A[1] = 0xFF03030C;
        return 0;
    case 3:
        A[0] = 0x30C0C33C;
        A[1] = 0x3CC3C030;
        return 0;
    case 4:
        A[0] = 0xFFC3C3C3;
        A[1] = 0xC0C0C0C0;
        return 0;
    case 5:
        A[0] = 0x3C0303FF;
        A[1] = 0x3FC0C0C0;
        return 0;
    case 6:
        A[0] = 0x3F0303FC;
        A[1] = 0x3CC3C3C3;
        return 0;
    case 7:
        A[0] = 0x30C0C0FF;
        A[1] = 0x0C0C0C30;
        return 0;
    case 8:
        A[0] = 0x3CC3C33C;
        A[1] = 0x3CC3C3C3;
        return 0;
    case 9:
        A[0] = 0xFCC3C33C;
        A[1] = 0x3CC3C0C0;
        return 0;
    case 10: // A
        A[0] = 0xFFC3C33C;
        A[1] = 0xC3C3C3C3;
        return 0;
    case 11: // B
        A[0] = 0x3FC3C33F;
        A[1] = 0x3FC3C3C3;
        return 0;
    case 12: // C
        A[0] = 0x0303C33C;
        A[1] = 0x3CC30303;
        return 0;
    case 13: // D
        A[0] = 0xC3C3C33F;
        A[1] = 0x3FC3C3C3;
        return 0;
    case 14: // E
        A[0] = 0x3F0303FF;
        A[1] = 0xFF030303;
        return 0;
    case 15: // F
        A[0] = 0x3F0303FF;
        A[1] = 0x03030303;
        return 0;
    case -1: // +
        A[0] = 0xFF181800;
        A[1] = 0x00001818;
        return 0;
    case -2: // -
        A[0] = 0xFF000000;
        A[1] = 0x00000000;
        return 0;
    }
    return -1;
}

int bc_printbigchar(
        int* A, int x, int y, enum colors fg_color, enum colors bg_color)
{
    mt_gotoXY(x, y);
    mt_setfgcolor(fg_color);
    mt_setbgcolor(bg_color);

    int part = 0;

    for (int i = 1; i <= 8; i++) {
        if (i > 4)
            part = 1;

        for (int j = 1; j <= 8; j++) {
            if (A[part] & 1)
                bc_printA("\u2588");
            else
                bc_printA(" ");

            A[part] = A[part] >> 1;
        }

        x++;
        mt_gotoXY(x, y);
    }

    return 0;
}

int bc_setbigcharpos(int* big, int x, int y, int value)
{
    if ((value != 0 && value != 1) || x < 1 || x > 8 || y < 1 || y > 8)
        return -1;
    if (value == 1) {
        big[x / 5] |= 1 << ((x - 1) * 8 + (y - 1));
        return 0;
    }
    if (value == 0) {
        big[x / 5] &= ~(1 << ((x - 1) * 8 + (y - 1)));
        return 0;
    }
    return -1;
}

int bc_getbigcharpos(int* big, int x, int y, int* value)
{
    if (x < 1 || x > 8 || y < 1 || y > 8)
        return -1;
    *value = (big[x / 5] >> ((x - 1) * 8 + (y - 1))) & 0x1;
    return 0;
}

int bc_bigcharwrite(int fd, int* big, int count)
{
    write(fd, big, sizeof(count) * 2 * count);
    close(fd);
    return 0;
}

int bc_bigcharread(int fd, int* big, int need_count, int* count)
{
    *count = read(fd, big, sizeof(need_count) * 2 * need_count) / 8;
    if (*count == 0)
        return -1;
    close(fd);
    return 0;
}
