#include "logf.h"
#include <stdio.h>
#include <stdarg.h>

void
game_logf (const char* format, ...)
{
    va_list arglist;
    va_start (arglist, format);
    vprintf (format, arglist);
    va_end (arglist);
    fflush (stdin);
}
