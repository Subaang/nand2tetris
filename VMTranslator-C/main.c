#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "codewriter.h"

#define LINE_LENGTH 30 //max length of any line in the vm file
#define MAX_FILE_LENGTH 600 //how many lines are in the vm file.

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


int main(void) {
    FILE *fptr_read = fopen("D:\\C\\VMTranslator-C\\Test.txt", "r");

    char reader[MAX_FILE_LENGTH];
    char content[MAX_FILE_LENGTH][LINE_LENGTH];
    int i = 0;


    if(fptr_read != NULL) {
        while(fgets(reader,MAX_FILE_LENGTH,fptr_read)) {
            strcpy(reader,trimwhitespace(reader));
            if(reader[0] != '/' && reader[0] != '\n' && reader[0] != '\0') {
                strncpy(content[i],reader,50);
                strtok(content[i],"\n/");
                i++;
            }
        }
    }
    else{
        printf("Unsuccessful");
    }


    for(int k = 0; k < i; k++) {
        codeWriter(parse(LINE_LENGTH,content[k]));
    }



    fclose(fptr_read);
    return 0;
}
