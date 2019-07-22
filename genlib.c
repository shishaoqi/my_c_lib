/*
 * File: genlib.c
 * Version: 1.0
 * Last modified on Sun Jul 24 10:29:46 1994 by eroberts
 * -----------------------------------------------------
 * This file implements the general C library package.  See the
 * interface description in genlib.h for details.
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include "genlib.h"


/*
 * Constants:
 * ----------
 * ErrorExitStatus -- Status value used in exit call
  */

#define ErrorExitStatus 1

/* Section 1 -- Define new "primitive" types */

/*
 * Constant: UNDEFINED
 * -------------------
 * This entry defines the target of the UNDEFINED constant.
 */

char undefined_object[] = "UNDEFINED";

/* Section 2 -- Memory allocation */

/* Memory allocation implementation */

void *GetBlock(size_t nbytes)
{
    void *result;

    result = malloc(nbytes);
    if (result == NULL) Error("No memory available");
    return (result);
}

void FreeBlock(void *ptr)
{
    free(ptr);
}


/* Section 3 -- Basic error handling */


void Error(string msg, ...)
{
    va_list args;

    va_start(args, msg);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, msg, args);
    fprintf (stderr, "\n");
    va_end(args);
    exit(ErrorExitStatus);
}
