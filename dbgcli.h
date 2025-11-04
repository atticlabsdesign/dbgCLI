#ifndef DBGCLI_H
#define DBGCLI_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DBGCLI_DEFAULT_HELP \
           .keyword = {"help", "h"}, \
            .help = "List all commands and their descirptions",\
            .cmdFunc = NULL, 
    
#define DBG_CLI_MAX_ARGS 10

typedef enum {
    DBGCLI_SUCCESS,
    DBGCLI_UNKNOWN_KEYWORD,
    DBGCLI_UNKNOWN_PARAMETER,
    DBGCLI_TOO_FEW_ARGS,
    DBGCLI_TOO_MANY_ARGS,
} dbgCliError_t;

typedef struct {
    // uint8_t params; 
    const char* help;
    // size_t paramLeng;
    dbgCliError_t (*cmdFunc)(unsigned int argc, char *argv[]); //dataIn should be a an array, starting with the length of the array of custom data per command function
    const char *keyword[2]; //one shorthand and one longhand supported
    // char options[][2]; //need to think about handling options more in the future

}dbgCliCommand_t;

typedef struct {
    const char*   description;
    // size_t  descLeng;
    const char*   help;
    // size_t  helpLeng;
    const dbgCliCommand_t *commands;
    const size_t  cmdNum;
    // dbgCliError_t (*parse)(char *input, size_t length, dbgCliCommand_t* commands, size_t cmdNum);
} dbgCliMenu_t;


// void printDBG(const char *restrict, ...);

dbgCliError_t parseInput (char * command, const dbgCliMenu_t *menu);
void dbgCliPresent(const dbgCliMenu_t *menu);
void dbgCliHelp (const dbgCliMenu_t *menu);

#endif