#ifndef PARSER_H
#define PARSER_H
#define commandEquality(txt) strcmp(res->command,txt)==0
typedef enum{
    C_ARITHMENIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL
}commandType;

typedef struct{
    commandType name;
    char *command;
    char *target;
    int value;
}vmInstruction;


extern vmInstruction *parse(int lineLength,char content[lineLength]);

#endif //PARSER_H
