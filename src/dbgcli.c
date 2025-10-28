#include "../dbgcli.h"
#include <stdarg.h>
#include <stdio.h>

void printDBG(const char *restrict inputStr, ...){
    //thius is not done yet

char * buffer;

va_list args;
va_start(args,inputStr);

sprintf(buffer, inputStr, args); //have sprintf handle formatting

va_end(args);

return;
}