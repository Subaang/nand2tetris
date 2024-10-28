#include "codewriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define targetEquality(txt) strcmp(instruction->target,txt)==0
#define i instruction->value
#define FILENAME "@test"


void codeWriter(vmInstruction *instruction) {
    if(instruction->name == C_PUSH) {
            if(targetEquality("local")) {
                printf("@LCL\n");
                printf("D=M\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("A=D\n");
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
            }
            else if(targetEquality("this")) {
                printf("@THIS\n");
                printf("D=M\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("A=D\n");
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
            }
            else if(targetEquality("that")) {
                printf("@THAT\n");
                printf("D=M\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("A=D\n");
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
            }
            else if(targetEquality("argument")) {
                printf("@ARG\n");
                printf("D=M\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("A=D\n");
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
            }
            else if(targetEquality("constant")) {
                printf("@%d\n",i);
                printf("D=A\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
            }
            else if(targetEquality("this")) {
                printf("@5\n");
                printf("D=A\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("A=D\n");
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
            }
            else if(targetEquality("static")) {
                printf(FILENAME);
                printf(".%d\n",i);
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
            }
            else if(targetEquality("pointer")) {
                printf("@R3\n");
                printf("D=A\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("A=D\n");
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
            }
            else {
                printf("PUSH WHAT!!!");
            }
        }

    if(instruction->name == C_POP) {
            if(targetEquality("local")) {
                printf("@LCL\n");
                printf("D=M\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("@R13\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M-1\n");
                printf("A=M\n");
                printf("D=M\n");
                printf("@R13\n");
                printf("A=M\n");
                printf("M=D\n");
            }
            else if(targetEquality("this")) {
                printf("@THIS\n");
                printf("D=M\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("@R13\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M-1\n");
                printf("A=M\n");
                printf("D=M\n");
                printf("@R13\n");
                printf("A=M\n");
                printf("M=D\n");
            }
            else if(targetEquality("that")) {
                printf("@THAT\n");
                printf("D=M\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("@R13\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M-1\n");
                printf("A=M\n");
                printf("D=M\n");
                printf("@R13\n");
                printf("A=M\n");
                printf("M=D\n");
            }
            else if(targetEquality("argument")) {
                printf("@ARG\n");
                printf("D=M\n");
                printf("@%d\n",i);
                printf("D=D+A\n");
                printf("@R13\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M-1\n");
                printf("A=M\n");
                printf("D=M\n");
                printf("@R13\n");
                printf("A=M\n");
                printf("M=D\n");
        }
        else if(targetEquality("temp")) {
            printf("@5\n");
            printf("D=A\n");
            printf("@%d\n",i);
            printf("D=D+A\n");
            printf("@R13\n");
            printf("M=D\n");
            printf("@SP\n");
            printf("M=M-1\n");
            printf("A=M\n");
            printf("D=M\n");
            printf("@R13\n");
            printf("A=M\n");
            printf("M=D\n");
        }
        else if(targetEquality("constant")) {
            printf("Invalid! pop constant?");
        }
        else if(targetEquality("static")) {
            printf("@SP\n");
            printf("M=M-1\n");
            printf("A=M\n");
            printf("D=M\n");
            printf(FILENAME);
            printf(".%d\n",i);
            printf("M=D");
        }
        else if(targetEquality("pointer")) {
            printf("@R3\n");
            printf("D=A\n");
            printf("@%d",i);
            printf("D=D+A\n");
            printf("@R13\n");
            printf("M=D\n");
            printf("@SP\n");
            printf("M=M-1\n");
            printf("A=M\n");
            printf("D=M\n");
            printf("@R13\n");
            printf("A=M\n");
            printf("M=D\n");
        }
        else {
            printf("POP WHAT!!!");
        }

        }

    if(instruction->name == C_ARITHMENIC) {
        if(targetEquality("add")) {
            printf("@SP\n");
            printf("A=M\n");
            printf("D=M\n");
            printf("A=A-1\n");
            printf("D=D+M\n");
            printf("M=D\n");
        }
        else if(targetEquality("sub")) {
            printf("@SP\n");
            printf("A=M\n");
            printf("D=M\n");
            printf("A=A-1\n");
            printf("D=M-D\n");
            printf("M=D\n");
        }
        else if(targetEquality("neg")) {
            printf("@SP\n");
            printf("A=M-1\n");
            printf("M=-M\n");
            
        }

        }


    free(instruction->target);
    free(instruction->command);
    free(instruction);

}

