//
// Created by subaa on 20-10-2024.
//

#ifndef PARSER_H
#define PARSER_H

#define LINE_LENGTH 50

typedef struct {
    int opcode;
    int address; // used only for A instruction, stores value after @ symbol
    char *comp;
    char *dest;
    char *jump;

}instruction;

extern void translate(int fileLength, char content[fileLength][LINE_LENGTH]);
extern instruction *parseBasic( int lineLength, char input[lineLength]);
extern void buildTable(int fileLength,char content[][LINE_LENGTH]);

#endif //PARSER_H
