#include "../dbgcli.h"
#include <stdarg.h>
#include <stdio.h>

//TODO: replace printf with something more generic

void dbgCliErrorHandler(dbgCliError_t error){
    switch (error) {
        case DBGCLI_SUCCESS:
        break;

        case DBGCLI_UNKNOWN_KEYWORD:
        printf("Error: Unknown Command\n\r");
        break;

        case DBGCLI_UNKNOWN_PARAMETER:
        printf("Error: Unknown Argument\n\r");
        break;

        case DBGCLI_TOO_FEW_ARGS:
        printf("Error: Missing Arguments\n\r");
        break;

        case DBGCLI_TOO_MANY_ARGS:
        printf("Error: Too Many Arguments\n\r");
        break;

        default: 
            printf("Unkown Error\n\r");
        break;
    }
    return;
}


// void printDBG(const char *restrict inputStr, ...){
//     //thius is not done yet

// char * buffer;

// va_list args;
// va_start(args,inputStr);

// sprintf(buffer, inputStr, args); //have sprintf handle formatting

// va_end(args);

// return;
// }

dbgCliError_t parseInput (char * command, const dbgCliMenu_t *menu){
    dbgCliError_t error = DBGCLI_SUCCESS;
    char* token = strtok(command, " ");
    bool valid = false;
    size_t argc = 1;
    char *argv[DBG_CLI_MAX_ARGS];

    if (token == NULL) {
        error = DBGCLI_UNKNOWN_KEYWORD;
    } else if (strcmp(token, "help")==0) {
        dbgCliHelp(menu);
    } else {
        size_t i; 
        for (i = 1; i<menu->cmdNum; i++) { //help must always be the 0th command
            if (strcmp(token, menu->commands[i].keyword[1]) == 0 || strcmp(token, menu->commands[i].keyword[0]) == 0) {
                valid = true;
                break;
            }
        }

        if (valid) {
            argv[0] = token;
            token = strtok(NULL, " ");

            while (token != NULL){
                argc ++;
                argv[argc-1] = token;
                token = strtok(NULL, " ");
            }
            error = menu->commands[i].cmdFunc(argc, argv);

        } else {
            error = DBGCLI_UNKNOWN_KEYWORD;
        }
    }

    dbgCliErrorHandler(error);

    return error;
}

void dbgCliPresent(const dbgCliMenu_t *menu){
    // printf("%c^[[1J\n\r", 27);
    printf("\f");
    printf("%s \n\r", menu->description);
    printf("Enter ""help"" for a list of commands\n\r");
    printf("There are: %d commands\n\r", menu->cmdNum);

}

void dbgCliHelp(const dbgCliMenu_t *menu){
        printf("%s\n\r", menu->help);
    for (size_t i = 0; i<menu->cmdNum; i++) {
        printf("%s, %s    %s\n\r", menu->commands[i].keyword[0],menu->commands[i].keyword[1],menu->commands[i].help); 
    }

    return;
}

