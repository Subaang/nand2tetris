#include "codewriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define targetEquality(txt) strcmp(instructionList[k]->target,txt)==0
#define SP_BASE 256
#define LCL_BASE 1256
#define THIS_BASE 2256
#define THAT_BASE 3256
#define SP memory[0]
#define LCL memory[1]
#define THIS memory[2]
#define THAT memory[3]
#define i instructionList[k]->value



/*
 * Stack starts from memory 256 of ram
 * I.E it starts from M = 256
 */


void codeWriter(int number_of_instructions,vmInstruction **instructionList) {
    int *memory = malloc(4096*sizeof(int));

    SP = SP_BASE;
    LCL = LCL_BASE;
    THIS = THIS_BASE;
    THAT = THAT_BASE;

    int addr = -1; //Represents A register

    int k = 0;
    while(k < number_of_instructions) {
        if(instructionList[k]->name == C_PUSH) {
            if(targetEquality("local")) {
                addr = LCL+i;
                printf("@%d\n",addr);
                memory[SP] = memory[addr];
                printf("D=M\n");
                printf("@%d\n",SP);
                printf("M=D\n");
                SP++;
            }
            else if(targetEquality("this")) {
                addr = THIS+i;
                printf("@%d\n",addr);
                memory[SP] = memory[addr];
                printf("D=M\n");
                printf("@%d\n",SP);
                printf("M=D\n");
                SP++;
            }
            else if(targetEquality("that")) {
                addr = THAT+i;
                printf("@%d\n",addr);
                memory[SP] = memory[addr];
                printf("D=M\n");
                printf("@%d\n",SP);
                printf("M=D\n");
                SP++;
            }
            else if(targetEquality("constant")) {
                memory[SP] = i;
                printf("@%d\n",SP);
                printf("M=%d\n",i);
                SP++;
            }
            else {
                printf("PUSH WHAT!!!");
            }
        }

        if(instructionList[k]->name == C_POP) {
            if(targetEquality("local")) {
                addr = LCL+i;
                SP--;
                printf("@%d\n",SP);
                memory[addr] = memory[SP];
                printf("D=M\n");
                printf("@%d\n",addr);
                printf("M=D\n");
            }
            else if(targetEquality("this")) {
                addr = THIS+i;
                SP--;
                printf("@%d\n",SP);
                memory[addr] = memory[SP];
                printf("D=M\n");
                printf("@%d\n",memory[addr]);
                printf("M=D\n");
            }
            else if(targetEquality("that")) {
                addr = THAT+i;
                SP--;
                printf("@%d\n",SP);
                memory[addr] = memory[SP];
                printf("D=M\n");
                printf("@%d\n",memory[addr]);
                printf("M=D\n");
            }
            else if(targetEquality("constant")) {
                printf("Invalid!");
            }
            else {
                printf("POP WHAT!!!");
            }

        }

        if(instructionList[k]->name == C_ARITHMENIC) {

        }
        free(instructionList[k]->target);
        free(instructionList[k]->command);
        free(instructionList[k]);
        k++;
    }

free(memory);
}