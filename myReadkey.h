#pragma once

#include <sys/ioctl.h>
#include <termios.h>

struct termios termState;        // temp / to change
struct termios termStateCurrent; // current
struct termios termStateSave;    // save

enum keys {
    Up,
    Down,
    Left,
    Right,
    Save,
    Load,
    Run,
    Step,
    Reset,
    Input,
    F5_Accumulator,
    F6_InstructionCounter,
    Quit,
    Cancel,
    Incorrect_key
};

void rk_mytermsave(void)
{
    tcgetattr(0, &termStateSave);
}

void rk_mytermrestore(void)
{
    tcsetattr(0, TCSANOW, &termStateSave);
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    if (regime < 0 || regime > 1 || echo < 0 || echo > 1 || sigint < 0
        || sigint > 1)
        return -1;

    rk_mytermsave();
    tcgetattr(0, &termStateCurrent);
    termState = termStateCurrent;

    // Canonical mode
    if (regime)
        termState.c_lflag |= ICANON;
    else
        termState.c_lflag &= ~ICANON;

    // Display characters
    if (echo)
        termState.c_lflag |= ECHO;
    else
        termState.c_lflag &= ~ECHO;

    // Handle control characters
    if (sigint)
        termState.c_lflag |= ISIG;
    else
        termState.c_lflag &= ~ISIG;

    termState.c_cc[VMIN] = vmin;
    termState.c_cc[VTIME] = vtime;

    tcsetattr(0, TCSANOW, &termState);

    return 0;
}

int rk_readkey(enum keys* key)
{
    char buffer;
    rk_mytermregime(0, 0, 1, 0, 0);
    read(1, &buffer, 1);

    switch (buffer) {
    case 'c':
        *key = Cancel;
        break;
    case 'p':
        *key = Reset;
        break;
    case 'i':
        *key = Input;
        break;
    case 'q':
        *key = Quit;
        break;
    case 'l':
        *key = Load;
        break;
    case 's':
        *key = Save;
        break;
    case 'r':
        *key = Run;
        break;
    case 't':
        *key = Step;
        break;

    case '\E':
        read(1, &buffer, 1);
        read(1, &buffer, 1);
        switch (buffer) {
        case 65:
            *key = Up;
            break;
        case 66:
            *key = Down;
            break;
        case 67:
            *key = Right;
            break;
        case 68:
            *key = Left;
            break;
        case '1':
            read(1, &buffer, 1);
            if (buffer == '5') {
                read(1, &buffer, 1);
                if (buffer == '~')
                    *key = F5_Accumulator;
            }
            if (buffer == '7') {
                read(1, &buffer, 1);
                if (buffer == '~')
                    *key = F6_InstructionCounter;
            }
            break;
        default:
            *key = Incorrect_key;
        }
        break;
    default:
        *key = Incorrect_key;
        break;
    }

    tcsetattr(0, TCSANOW, &termStateCurrent);
    return 0;
}
