//
// Created by subaa on 21-10-2024.
//

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <stddef.h>
#define LINE_LENGTH 50

typedef struct tableElement{
    char *symbol;
    int value;
    struct tableElement *next_ptr;
}tableElement;

extern int findValue(tableElement *head, char *symbol);
extern bool inTable(tableElement *head,char *symbol);
extern void appendToTable(tableElement *head,char *symbol, int value);
//extern void buildTable(int fileLength,char content[][LINE_LENGTH]);
extern void initializeTable();


#endif //SYMBOLTABLE_H
