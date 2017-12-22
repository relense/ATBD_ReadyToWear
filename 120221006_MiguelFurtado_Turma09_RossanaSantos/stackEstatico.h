#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#define N 20
#include "element.h"

struct stack
{
    TElem table[N];
    unsigned int size;
};

typedef struct stack *PtStackE;

PtStackE stackCreateEstatico(void);
int stackDestroyEstatico(PtStackE *pstack);
int stackPushEstatico(PtStackE pstack, TElem pelem);
int stackPopEstatico(PtStackE pstack, TElem *pelem);
int stackPeekEstatico(PtStackE pstack, TElem *pelem);
int stackIsEmptyEstatico(PtStackE pstack);
int stackIsFullEstatico(PtStackE pstack);
int stackSizeEstatico(PtStackE pstack, unsigned int *pelement);

#endif // STACK_H_INCLUDED
