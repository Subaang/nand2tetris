#include <stdio.h>
#include <string.h>
#include "assembler.h"
#include <stdlib.h>
#include "parser.h"

static char *decToBinary16(int n)
{
    char binCharArr[17] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','\0'};
    char *binString = malloc(17*sizeof(char));
    char binaryNum[16] = {0};

    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    int k = 0;
    int j = 15;
    while(k < i) {
        binCharArr[j] = binaryNum[k]+48;
        k++;
        j--;
    }

    strcpy(binString,binCharArr);
    return binString;
}

char *assemble(int lineLength,char input[lineLength]) {
    instruction *parsedStruct = parseBasic(lineLength,input);
    char *res = malloc(17*sizeof(char));
    strcpy(res,"111");


    if(parsedStruct->opcode == 0) { //Translating A instruction
        res = decToBinary16(parsedStruct->address);
        return res;
    }

    char *compStrs[28] = {"0","1","-1","D","A","!D","!A","-D","-A","D+1","A+1","D-1","A-1","D+A","D-A","A-D","D&A","D|A","M","!M","-M","M+1","M-1","D+M","D-M","M-D","D&M","D|M"};
    char *compBins[28] = {"0101010","0111111","0111010","0001100","0110000","0001101","0110001","0001111","0110011","0011111","0110111","0001110","0110010","0000010","0010011","0000111","0000000","0010101","1110000","1110001","1110011","1110111","1110010","1000010","1010011","1000111","1000000","1010101"};

    for(int i = 0; i < 28; i++) {
        if(parsedStruct->comp == NULL) {
            strcat(res,"000");
            break;
        }
        if(strcmp(parsedStruct->comp,compStrs[i]) == 0) {
            strcat(res,compBins[i]);
           // printf("%s %s Appended %s\n",parsedStruct->comp,compStrs[i],compBins[i]);
            break;
        }
    }

    char *destStrs[7] = {"M","D","MD","A","AM","AD","AMD"};
    char *destBins[7] = {"001","010","011","100","101","110","111"};

    for(int i = 0; i < 7; i++) { //NOTE: Cant pass null to strcpy. handle it first
        if(parsedStruct->dest == NULL) {
            strcat(res,"000");
            break;
        }
        if(strcmp(parsedStruct->dest,destStrs[i]) == 0) {
            strcat(res,destBins[i]);
            break;
        }
    }


    char *jumpStrs[7] = {"JGT","JEQ","JGE","JLT","JNE","JLE","JMP"};
    char *jumppBins[7] = {"001","010","011","100","101","110","111"};

    for(int i = 0; i < 7; i++) {
        if(parsedStruct->jump == NULL) {
           // printf("\nHi\n");
            strcat(res,"000");
            break;
        }
        if(strcmp(parsedStruct->jump,jumpStrs[i]) == 0) {
            strcat(res,jumppBins[i]);
            break;
        }
    }

    free(parsedStruct->comp);
    free(parsedStruct->dest);
    free(parsedStruct->jump);
    free(parsedStruct);

    return res;

}
