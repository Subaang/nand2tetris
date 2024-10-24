#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "symboltable.h"
#include <ctype.h>
#include <stdlib.h>

#define LINE_LENGTH 50

tableElement elementArray[] = {
    {"R0",0,NULL},
    {"R1",1,NULL},
    {"R2",2,NULL},
    {"R3",3,NULL},
    {"R4",4,NULL},
    {"R5",5,NULL},
    {"R6",6,NULL},
    {"R7",7,NULL},
    {"R8",8,NULL},
    {"R9",9,NULL},
    {"R10",10,NULL},
    {"R11",11,NULL},
    {"R12",12,NULL},
    {"R13",13,NULL},
    {"R14",14,NULL},
    {"R15",15,NULL},
    {"SCREEN",16384,NULL},
    {"KBD",24576,NULL},
    {"SP",0,NULL},
    {"LCL",1,NULL},
    {"ARG",2,NULL},
    {"THIS",3,NULL},
    {"THAT",4,NULL},

};

int findValue(tableElement *head, char *symbol) {
    tableElement *ptr = head;
    while(ptr != NULL) {
        if(strcmp(ptr->symbol,symbol) == 0) {
            int value = ptr->value;
            return value;
        }
        ptr = ptr->next_ptr;
    }

    printf("NOT FOUND!");
    return -1;
}

bool inTable(tableElement *head,char *symbol) {
    tableElement *ptr = head;

    while(ptr != NULL) {
        if(strcmp(ptr->symbol,symbol) == 0) {
            return true;
        }
        ptr = ptr->next_ptr;
    }
    return false;
}

void appendToTable(tableElement *head,char *symbol, int value) {
    tableElement *ptr = head;
    tableElement *temp = (tableElement *) malloc(sizeof(tableElement));

    temp->symbol = strdup(symbol);
    temp->value = value;
    temp->next_ptr = NULL;

    while(ptr->next_ptr != NULL) {
        ptr = ptr->next_ptr;
    }
    ptr->next_ptr = temp;
}


void initializeTable() {
    //Initialize table
    tableElement *navigator = &elementArray[0];
    for(int i = 0; i < 22; i++) {
        elementArray[i].next_ptr = &elementArray[i+1];
    }
}

void buildTable(int fileLength,char content[][LINE_LENGTH]) {
        //equivalent to char (*contentPtr)[50] -> pointer to array 50 of char
        //Initialize table
        initializeTable();
        tableElement *firstElement = &elementArray[0];
        tableElement *navigator = &elementArray[22];

        //First pass of symboltable - add the label symbols
        int labelCount = 0;
        char label[LINE_LENGTH];
        for(int i = 0; i < fileLength; i++) {
            if(content[i][0] == '(') {
                labelCount++;
                for(int k = 0; k < LINE_LENGTH; k++) {
                    if(content[i][k] == ')') {
                        label[k-1] = '\0';
                        break;
                    }
                    label[k-1] = content[i][k];
                }

                /*
                 *labelCount keeps track of number of labels passed
                 *each label passed increases required line number by 1 and starts from zero
                 */

                if(!inTable(firstElement,label)) {
                    appendToTable(firstElement,label,i-labelCount+1); //i will be the line number(starting from 0) of label. +1 because labels refer to instruction below
                }
            }
        }

        //Second pass of symboltable -add the variable symbols
        char variable[LINE_LENGTH];
        int line = 16; // we assign ram values starting from 16 to variables
        for(int i = 0; i < fileLength; i++) {
            if(content[i][0] == '@' && isalpha(content[i][1]) ){ //Variable names cant start with a number
                //inside if, i will carry the line number(starting from 0) of the variable
                memcpy(variable,content[i]+1,strlen(content[i]));
                if(!inTable(firstElement,variable)) {
                    appendToTable(firstElement,variable,line);
                    line++;
                }
            }
        }
    }




