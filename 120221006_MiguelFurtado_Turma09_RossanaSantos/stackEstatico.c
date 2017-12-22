#include <stdlib.h>
#include <stdio.h>
#include "stackEstatico.h"

#define OK          0
#define NULL_PTR    1
#define NO_STACK    2
#define STACK_EMPTY 4
#define STACK_FULL  5


PtStackE stackCreateEstatico()
{
    PtStackE myStack;

    if((myStack = (PtStackE) malloc (sizeof (struct stack))) == NULL)
        return NULL;

    myStack->size = 0;

    return myStack;
}

int stackDestroyEstatico(PtStackE *pstack)
{
    if(*pstack == NULL) return NO_STACK;
    free(*pstack);
    *pstack = NULL;

    return OK;
}

int stackPushEstatico(PtStackE pstack, TElem pelem)
{
    if(pstack == NULL) return NO_STACK;
    if(pstack->size == N) return STACK_FULL;

    pstack->table[pstack->size++] = pelem;
    return OK;
}

int stackPopEstatico(PtStackE pstack, TElem *pelem)
{
    if(pstack == NULL) return NO_STACK;
    if(pstack->size == 0) return STACK_EMPTY;
    if(pelem == NULL) return NULL_PTR;

    *pelem = pstack->table[--pstack->size];

    return OK;
}

int stackPeekEstatico(PtStackE pstack, TElem *pelem)
{
    if(pstack == NULL) return NO_STACK;
    if(pstack->size == 0) return STACK_EMPTY;
    if(pelem == NULL) return NULL_PTR;

    *pelem = pstack->table[pstack->size];
    return OK;
}

int stackIsEmptyEstatico(PtStackE pstack)
{
    if(pstack == NULL) return NO_STACK;
    if(pstack->size == 0) return STACK_EMPTY;

    return OK;
}

int stackIsFullEstatico(PtStackE pstack)
{
    if(pstack == NULL) return NO_STACK;
    if(pstack->size == N) return STACK_FULL;

     return OK;
}

int stackSizeEstatico(PtStackE pstack, unsigned int *pelement)
{
    if(pstack == NULL) return NO_STACK;
    if(pelement == NULL) return NULL_PTR;

    *pelement = pstack->size;
    if(pstack->size == 0) return STACK_EMPTY;

    return OK;
}
