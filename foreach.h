/*
 * File: foreach.h
 * ---------------
 * This interface provides a simple syntactic extension for
 * iterators that makes them easier to read.
 */

#ifndef _foreach_h
#define _foreach_h

#include "genlib.h"

/*
 * Statement form: foreach
 * Usage: foreach (element in collection) {
 *            . . . code involving element . . .
 *        }
 * ---------------------------------------------
 * This macro definition creates a new statement form that
 * simplifies the use of iterators.  The variable element
 * must be declared in the current scope and must be
 * compatible with the base type of the collection.  The
 * functions InitForEach and StepForEach are not called
 * directly by the client.
 */

#define in ,
#define foreach(arg) _foreach(arg)
#define _foreach(e, c) for (InitForEach(&e, c); StepForEach(&e); )

void InitForEach(void *ep, void *collection);
bool StepForEach(void *ep);

#endif
