#ifndef STACKDINAMICO_H_INCLUDED
#define STACKDINAMICO_H_INCLUDED
#include "elementFicheiro.h"

typedef struct node *PtNode;

struct node
{
    TElemF *ptElem;
    PtNode ptPrev;
};

 struct stackd
{
    PtNode top;
    unsigned int size;
};

typedef struct stackd *PtStackD;

PtStackD stackCreateDinamico(void);                             /* criar um stack dinamico*/
int stackDestroyDinamico(PtStackD *pStack);                     /* destruir um stack */
int stackPushDinamico(PtStackD pStack, TElemF pelem);           /* adicionar um elemento à stack*/
int stackPopDinamico(PtStackD pStack, TElemF *pelem);           /* remover um elemento da stack*/
int stackPeekDinamico(PtStackD pStack, TElemF *pelem);          /* mostra qual é o elemento no top da stack*/
int stackIsEmptyDinamico(PtStackD pStack);                      /* esta vazio*/
int stackIsFullDinamico(PtStackD pStack);                       /* esta cheio*/
int stackSizeDinamico(PtStackD pStack, unsigned int *pnelem);   /* tamanha da stack*/

#endif // STACKDINAMICO_H_INCLUDED
