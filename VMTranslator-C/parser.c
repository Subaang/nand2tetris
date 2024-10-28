#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include <stdlib.h>
#include <string.h>

#define MAX_TARGET_SIZE 9 //size of 2nd word in vm instructions




vmInstruction *parse(int lineLength,char content[lineLength]) {
    vmInstruction *res = malloc(sizeof(vmInstruction)); //https://stackoverflow.com/questions/18248047/allocate-memory-for-a-struct-with-a-character-pointer-in-c
    res->command = malloc(9);
    res->target = malloc(MAX_TARGET_SIZE);

    char buff[MAX_TARGET_SIZE];
    int k = 0;
    int i = 0;
    while(i < lineLength) {
        if(content[i] == ' ' || content[i] == '\0') {
            buff[k] = '\0';
            strcpy(res->command, buff);
            break;
        }
        buff[k] = content[i];
        k++;
        i++;
    }

    k = 0;
    i++;
    if(content[i] != '\0') {
        while(i < lineLength) {
            if(content[i] == ' ' || content[i] == '\0') {
                buff[k] = '\0';
                strcpy(res->target, buff);
                break;
            }
            buff[k] = content[i];
            k++;
            i++;
        }
    }
    else {
        strcpy(res->target, "X");
    }

    k = 0;
    i++;
    if(content[i] != '\0') {
        while(i < lineLength) {
            if(content[i] == ' ' || content[i] == '\0') {
                buff[k] = '\0';
                res->value = (int)strtol(buff, NULL, 10);
                break;
            }
            buff[k] = content[i];
            k++;
            i++;
        }
    }
    else {
        res->value = -1;
    }

    if(strcmp(res->command,"push") == 0) {
        res->name = C_PUSH;
    }
    else if(strcmp(res->command,"pop") == 0) {
        res->name = C_POP;
    }
    else if(commandEquality("add") || commandEquality("sub") || commandEquality("eq") || commandEquality("neg") || commandEquality("gt") || commandEquality("lt") || commandEquality("and") || commandEquality("or") || commandEquality("or") || commandEquality("not")){
        res->name = C_ARITHMENIC;
    }

    return res;
}
