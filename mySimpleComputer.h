#pragma once

#include <iostream>
#include <stdio.h>

#define MEMORY_SIZE 100

// Flags
#define OVERFLOW 0
#define DIVIDE_BY_ZERO 1
#define OUT_OF_MEMORY 2
#define IGNORING_CLOCK 3
#define INVALID_COMMAND 4

// Commands
#define READ 10
#define WRITE 11

#define LOAD 20
#define STORE 21

#define ADD 30
#define SUB 31
#define DIVIDE 32
#define MUL 33

#define JUMP 40
#define JNEG 41
#define JZ 42
#define HALT 43

#define NOT 51
#define AND 52
#define OR 53
#define XOR 54
#define JNS 55
#define JC 56
#define JNC 57
#define JP 58
#define JNP 59
#define CHL 60
#define SHR 61
#define RCL 62
#define RCR 63
#define NEG 64
#define ADDC 65
#define SUBC 66
#define LOGLC 67
#define LOGRC 68
#define RCCL 69
#define RCCR 70
#define MOVA 71
#define MOVR 72
#define MOVCA 73
#define MOVCR 74
#define ADDC_C 75
#define SUBC_C 76

int memory[MEMORY_SIZE];
int flag_register;

int sc_memoryInit(void)
{
    for (int i = 0; i < MEMORY_SIZE; i++)
        memory[i] = 0;

    return EXIT_SUCCESS;
}

int sc_memorySet(int address, int value)
{
    if (address >= MEMORY_SIZE || address < 0) {
        flag_register = flag_register | (1 << OUT_OF_MEMORY);
        return EXIT_FAILURE;
    }
    if (value > 65535) {
        flag_register = flag_register | (1 << OVERFLOW);
        return EXIT_FAILURE;
    }

    memory[address] = value;

    return EXIT_SUCCESS;
}

int sc_memoryGet(int address, int* value)
{
    if (address >= MEMORY_SIZE || address < 0) {
        flag_register = flag_register | (1 << OUT_OF_MEMORY);
        return EXIT_FAILURE;
    }

    *value = memory[address];

    return EXIT_SUCCESS;
}

int sc_memorySave(char* filename)
{
    FILE* outFile;
    outFile = fopen(filename, "wb");
    fwrite(memory, sizeof(int), MEMORY_SIZE, outFile);
    fclose(outFile);

    return EXIT_SUCCESS;
}

int sc_memoryLoad(char* filename)
{
    FILE* inFile;
    inFile = fopen(filename, "rb");
    if (inFile == NULL)
        return EXIT_FAILURE;

    fread(memory, sizeof(int), MEMORY_SIZE, inFile);
    fclose(inFile);

    return EXIT_SUCCESS;
}

int sc_regInit()
{
    if (&flag_register != NULL)
        flag_register = flag_register & 0;
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int sc_regSet(int registr, int value)
{
    if (!(registr >= OVERFLOW || registr <= INVALID_COMMAND))
        return EXIT_FAILURE;
    if (!(value >= 0 || value <= 1))
        return EXIT_FAILURE;

    if (value) {
        flag_register = flag_register | (1 << (registr));
    } else {
        flag_register = flag_register & (~(1 << (registr)));
    }

    return EXIT_SUCCESS;
}

int sc_regGet(int registr, int* value)
{
    if (!(registr >= OVERFLOW || registr <= INVALID_COMMAND))
        return EXIT_FAILURE;

    *value = (flag_register >> registr) & 1;

    return EXIT_SUCCESS;
}

int sc_commandEncode(int command, int operand, int* value)
{
    if (!((command >= READ && command <= WRITE)
          || (command >= LOAD && command <= STORE)
          || (command >= ADD && command <= MUL)
          || (command >= JUMP && command <= SUBC_C)))
        return EXIT_FAILURE;
    if (!(operand >= 0 && operand <= 127))
        return EXIT_FAILURE;

    *value = (command << 7) | operand;

    return EXIT_SUCCESS;
}

int sc_commandDecode(int value, int* command, int* operand)
{
    int _command = value >> 7;

    if (!((_command >= READ && _command <= WRITE)
          || (_command >= LOAD && _command <= STORE)
          || (_command >= ADD && _command <= MUL)
          || (_command >= JUMP && _command <= SUBC_C))) {
        flag_register = flag_register | (1 << INVALID_COMMAND);
        return EXIT_FAILURE;
    }

    int _operand = value & 127;

    if (!(_operand >= 0 && _operand <= 127)) {
        flag_register = flag_register | (1 << INVALID_COMMAND);
        return EXIT_FAILURE;
    }

    *command = _command;
    *operand = _operand;

    return EXIT_SUCCESS;
}
