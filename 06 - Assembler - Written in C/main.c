#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "assembler.h"
#include "symboltable.h"

#define LINE_LENGTH 50 //max length of any line in the asm file
#define MAX_FILE_LENGTH 40000 //how many lines are in the asm file.

static char *trimwhitespace(char *str)
{
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

//Note: in function, arrays are degraded to pointers. any length in the **first** brackets are for documentation purpose only

int main(int argc, char *argv[]) {

    FILE *fptr_read = fopen("D:\\C\\assembler\\Test.txt", "r");

    char reader[MAX_FILE_LENGTH];
    char content[MAX_FILE_LENGTH][LINE_LENGTH];
    int i = 0;


    if(fptr_read != NULL) {
        while(fgets(reader,MAX_FILE_LENGTH,fptr_read)) {
            strcpy(reader,trimwhitespace(reader));
            if(reader[0] != '/' && reader[0] != '\n' && reader[0] != '\0') {
                strncpy(content[i],reader,50);
                strtok(content[i],"\n /");
                i++;
            }
        }


        buildTable(i,content);
        translate(i,content);

        for(int k = 0; k < i; k++) {
            if(content[k][0] != '(') {
                char *bin = assemble(LINE_LENGTH,content[k]);
                printf("%s\n",bin);
                free(bin);
            }
        }
        // for(int k = 0; k < i; k++) {
        //     printf("%d : %s\n",k,content[k]);
        // }
    }

    else {
        printf("Unsuccessful");
    }

    fclose(fptr_read);
    return 0;
}
