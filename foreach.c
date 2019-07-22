/*
 * File: foreach.c
 * ---------------
 * This interface implements the foreach construct.
 */

#include <stdio.h>
#include "genlib.h"
#include "iterator2.h"
#include "foreach.h"

typedef struct cellT {
    void *ep;
    iteratorADT iterator;
    struct cellT *link;
} cellT;

static cellT *iteratorList = NULL;

/* Entry points */

void InitForEach(void *ep, void *collection)
{
    cellT *cp;

    for (cp = iteratorList; cp != NULL && cp->ep != ep; cp = cp->link) {
        /* no action */
    }
    if (cp == NULL) {
        cp = New(cellT *);
        cp->ep = ep;
        cp->link = iteratorList;
        iteratorList = cp;
    } else {
        if (cp->iterator != NULL) FreeIterator(cp->iterator);
    }
    cp->iterator = NewIterator(collection);
}

bool StepForEach(void *ep)
{
    cellT *cp;
    bool result;

    for (cp = iteratorList; cp != NULL && cp->ep != ep; cp = cp->link) {
        /* no action */
    }
    if (cp == NULL) Error("foreach iterator undefined");
    result = StepIterator(cp->iterator, ep);
    if (!result) {
        FreeIterator(cp->iterator);
        cp->iterator = NULL;
    }
    return (result);
}
