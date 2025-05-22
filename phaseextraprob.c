2 QUESTION -WELCOME

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMORY_SIZE 400
#define PAGE_SIZE 10

char memory[MEMORY_SIZE][5];  // Memory words
char IR[5];                   // Instruction Register
char R[5];                    // General Purpose Register
int IC = 0;                   // Instruction Counter
int C = 0;                    // Toggle Register

// Page Table: page 0 → 11, page 1 → 23, page 2 → 5
int pageTable[] = {11, 23, 5};
int pageTableSize = 3;

// ----------------------------------------
// OS Function: Translate Virtual Address to Real Address
int translate(int VA) {
    int page = VA / PAGE_SIZE;
    int offset = VA % PAGE_SIZE;
    if (page >= pageTableSize) {
        printf("OS ERROR: Invalid Virtual Address %d (page %d out of range)\n", VA, page);
        return -1;
    }
    int realAddress = pageTable[page] * PAGE_SIZE + offset;
    printf("VA = %d → Page = %d, Offset = %d → Real Address = %d\n", VA, page, offset, realAddress);
    return realAddress;
}

// ----------------------------------------
// Load Program into Memory
void load_program() {
    strcpy(memory[0], "GD10");   // Get data into VA 10 (will hold "WELCOME")
    strcpy(memory[1], "PD10");   // Print data from VA 10
    strcpy(memory[2], "H");      // Halt
}

// ----------------------------------------
// Execute Program Instructions
void execute() {
    while (1) {
        strcpy(IR, memory[IC]);
        printf("\nIC = %02d | Executing: %s\n", IC, IR);
        IC++;

        char opcode[3], operandStr[3];
        strncpy(opcode, IR, 2); opcode[2] = '\0';
        strncpy(operandStr, IR + 2, 2); operandStr[2] = '\0';

        int operand = (strcmp(opcode, "H") == 0) ? 0 : atoi(operandStr);
        int RA = (strcmp(opcode, "H") == 0) ? 0 : translate(operand);

        if (RA == -1 && strcmp(opcode, "H") != 0) return;

        if (strcmp(opcode, "GD") == 0) {
            printf("GD: Enter 4-character data (1st part of message): ");
            scanf("%4s", memory[RA]);
            RA++; // Write second part of message into next location
            printf("GD: Enter 3-character data (2nd part): ");
            scanf("%3s", memory[RA]);
        } else if (strcmp(opcode, "PD") == 0) {
            printf("PD Output: %s", memory[RA]);
            printf("%s\n", memory[RA + 1]);
        } else if (strcmp(opcode, "H") == 0) {
            printf("Program halted successfully.\n");
            return;
        }
        // Remaining instructions (LR, SR, CR, BT) are not used here
    }
}

// ----------------------------------------
// Main Function
int main() {
    // Clear memory
    for (int i = 0; i < MEMORY_SIZE; i++)
        strcpy(memory[i], "");

    printf("=== Virtual Machine with Paging ===\n");
    printf("Page Table: [Page 0 → %d, Page 1 → %d, Page 2 → %d]\n\n", pageTable[0], pageTable[1], pageTable[2]);

    // Test address translation
    int testVA = 12;
    printf("Translating example virtual address VA = %d...\n", testVA);
    int realAddr = translate(testVA);

    // Load and execute program
    load_program();
    execute();

    return 0;
}

OUTPUT : 
=== Virtual Machine with Paging ===
Page Table: [Page 0 → 11, Page 1 → 23, Page 2 → 5]

Translating example virtual address VA = 12...
VA = 12 → Page = 1, Offset = 2 → Real Address = 232

IC = 00 | Executing: GD10
VA = 10 → Page = 1, Offset = 0 → Real Address = 230
GD: Enter 4-character data (1st part of message): WELC
GD: Enter 3-character data (2nd part): OME

IC = 01 | Executing: PD10
VA = 10 → Page = 1, Offset = 0 → Real Address = 230
PD Output: WELCOME

IC = 02 | Executing: H
Program halted successfully.

QUESTION 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MEMORY_SIZE 200

char memory[MEMORY_SIZE][5]; // Each word has 4 chars + '\0'
char IR[5]; // Instruction Register
char R[5];  // General Purpose Register
int IC = 0; // Instruction Counter
bool C = false; // Toggle register for compare

const char *valid_opcodes[] = {"GD", "PD", "LR", "SR", "CR", "BT", "H", "AD"}; // AD added

bool is_valid_opcode(char *opcode) {
    for (int i = 0; i < 8; i++) {
        if (strncmp(opcode, valid_opcodes[i], 2) == 0)
            return true;
    }
    return false;
}

int str_to_int(char *str) {
    return atoi(str);
}

void int_to_str(int val, char *str) {
    snprintf(str, 5, "%04d", val);
}

void execute() {
    while (1) {
        strcpy(IR, memory[IC]);
        printf("IC=%02d | Executing: %s\n", IC, IR);
        IC++;

        char opcode[3], operand_str[3];
        strncpy(opcode, IR, 2);
        opcode[2] = '\0';
        strncpy(operand_str, IR + 2, 2);
        operand_str[2] = '\0';

        if (!is_valid_opcode(opcode)) {
            printf("ERROR: Invalid Opcode '%s' at %02d\n", opcode, IC - 1);
            return;
        }

        int operand = 0;
        if (strcmp(opcode, "H") != 0) {
            operand = atoi(operand_str);
            if (operand < 0 || operand >= MEMORY_SIZE) {
                printf("ERROR: Invalid Operand '%d' at %02d\n", operand, IC - 1);
                return;
            }
        }

        if (strcmp(opcode, "GD") == 0) {
            printf("GD: Enter 4-digit number: ");
            scanf("%4s", memory[operand]);
        }
        else if (strcmp(opcode, "PD") == 0) {
            printf("PD: Data at %02d = %s\n", operand, memory[operand]);
        }
        else if (strcmp(opcode, "LR") == 0) {
            strcpy(R, memory[operand]);
        }
        else if (strcmp(opcode, "SR") == 0) {
            strcpy(memory[operand], R);
        }
        else if (strcmp(opcode, "CR") == 0) {
            C = (strcmp(R, memory[operand]) == 0);
        }
        else if (strcmp(opcode, "BT") == 0) {
            if (C) IC = operand;
        }
        else if (strcmp(opcode, "AD") == 0) {
            int valR = str_to_int(R);
            int valM = str_to_int(memory[operand]);
            int sum = valR + valM;
            int_to_str(sum, R);
            printf("AD: R = %s (after adding %s from %02d)\n", R, memory[operand], operand);
        }
        else if (strcmp(opcode, "H") == 0) {
            printf("Program halted.\n");
            return;
        }
    }
}

void load_program() {
    strcpy(memory[0], "GD10");
    strcpy(memory[1], "GD11");
    strcpy(memory[2], "LR10");
    strcpy(memory[3], "AD11");
    strcpy(memory[4], "SR12");
    strcpy(memory[5], "PD12");
    strcpy(memory[6], "H");

    // Optional initial data (not required since GD inputs)
    strcpy(memory[10], "0000");
    strcpy(memory[11], "0000");
}

int main() {
    for (int i = 0; i < MEMORY_SIZE; i++) strcpy(memory[i], "0000");

    load_program();
    execute();

    return 0;
}

OUTPUT

IC=00 | Executing: GD10
GD: Enter 4-digit number: 1234
IC=01 | Executing: GD11
GD: Enter 4-digit number: 4321
IC=02 | Executing: LR10
IC=03 | Executing: AD11
AD: R = 5555 (after adding 4321 from 11)
IC=04 | Executing: SR12
IC=05 | Executing: PD12
PD: Data at 12 = 5555
IC=06 | Executing: H
Program halted.