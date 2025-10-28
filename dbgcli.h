#ifndef DBGCLI_H
#define DBGCLI_H

#include <stdio.h>
#include <string.h>

typedef enum {
    DBGCLI_SUCCESS,
    DBGCLI_UNKNOWN_KEYWORD,
    DBGCLI_UNKNOWN_PARAMETER,
    DBGCLI_TOO_FEW_ARGS,
    DBGCLI_TOO_MANY_ARGS,
} dbgCliError_t;



typedef struct {
    char keyword[2][5]; //one shorthand and one longhand supported
    char* param; 
    char* help;
    char* options;
    size_t paramLeng;
    dbgCliError_t (*cmdFunc)(char * dataIn); //dataIn should be a an array, starting with the length of the array of custom data per command function
}dbgCliCommand_t;

typedef struct {
    char*   description;
    // size_t  descLeng;
    char*   help;
    size_t  helpLeng;
    dbgCliCommand_t* commands;
    size_t  cmdNum;
    // dbgCliError_t (*parse)(char *input, size_t length, dbgCliCommand_t* commands, size_t cmdNum);
} submenu_t;

typedef struct {} menu_t;

void printDBG(const char *restrict, ...);

#endif