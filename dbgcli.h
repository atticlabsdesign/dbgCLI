#ifndef DBGCLI_H
#define DBGCLI_H

#include <string.h>

typedef enum {
    DBGCLI_SUCCESS,
    DBGCLI_UNKNOWN_KEYWORD,
    DBGCLI_UNKNOWN_PARAMETER,
} dbgCliError_t;

typedef struct {
    char keyword[2][5]; //one shorthand and one longhand supported
    char* param; 
    char* help;
    char* options;
    size_t paramLeng;
}dbgCliCommand_t;



typedef struct {
    char*   description;
    // size_t  descLeng;
    char*   help;
    size_t  helpLeng;
    dbgCliCommand_t* commands;
    size_t  cmdNum;
    dbgCliError_t (*parse)(char *input, size_t length, dbgCliCommand_t* commands, size_t cmdNum);
} submenu_t;

typedef struct {} menu_t;

#endif