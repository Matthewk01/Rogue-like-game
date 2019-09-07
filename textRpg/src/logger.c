#include <w32api/synchapi.h>
#include <stdio.h>
#include "logger.h"

void loggerPrint(const char *message) {
        size_t len = strlen(message);
        for(size_t i = 0; i < len; ++i) {
            putchar(message[i]);
            fflush(stdout);
            Sleep(MS);
        }
}
