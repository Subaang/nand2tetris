#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

#include <ctype.h>

#include "symboltable.h"



extern tableElement elementArray[];

void translate(int fileLength,char content[][LINE_LENGTH]) {
    tableElement *firstElement = &elementArray[0];

    //Translate symbols -> labels themselves will stay. we wont pass those lines into the parser
    char buffer[50];
    char newAInstr[50];
    int val = -1;
    for(int i = 0; i < fileLength; i++) {
        if(content[i][0] == '@' && isalpha(content[i][1]) ) {
            memcpy(buffer,content[i]+1,strlen(content[i]));
            val = findValue(firstElement,buffer); //If -1, it indicates failure
            snprintf(newAInstr,50,"@%d",val);
            strcpy(content[i],newAInstr);

        }
    }

}


instruction *parseBasic(int lineLength, char input[lineLength]){
    instruction *res = malloc(sizeof(instruction));
    res->comp = malloc(4*sizeof(char));
    res->dest = malloc(4*sizeof(char));
    res->jump = malloc(4*sizeof(char));
    bool compFilled = false;
    bool destFilled = false;
    bool jumpFilled = false;

    if(input[0] == '@') {
        res->opcode = 0;
        memmove (input, input+1, strlen (input+1) + 1); // +1 because we are copying over the null terminator as well memmove() doesnt work as intended without null terminators
        sscanf(input,"%d",&(res->address));
    }
    else {
        res->opcode = 1;

        char buffer[4];
        int k = 0;

        for(int i = 0; i < lineLength; i++) {
            if(input[i] != '=' && input[i] != ';' && input[i] != ' ' && input[i] != '\0') {
                buffer[k] = input[i];
                k++;
            }
            if(input[i] == '=') {
                buffer[k] = '\0';
                strcpy(res->dest,buffer);
                destFilled = true;
                k = 0;
            }
            if(input[i] == ';') {
                buffer[k] = '\0';
                strcpy(res->comp,buffer);
                compFilled = true;
                k = 0;
            }
            if(input[i] == ' ' | input[i] == '\0') {
                buffer[k] = '\0';
                if(compFilled) {
                    strcpy(res->jump,buffer);
                    jumpFilled = true;
                }
                else {
                    strcpy(res->comp,buffer);
                    compFilled = true;
                }
                k = 0;
                break;
            }
        }
    }

    if(!compFilled) { //compFilled = False
        res->comp = NULL;
    }
    if(!destFilled) {
        res->dest = NULL;
    }
    if(!jumpFilled) {
        res->jump = NULL;
    }


    return res;
}
