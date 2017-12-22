#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include "element.h"

typedef struct abpnode *PtBSTnode;

struct abpnode
{
    PtBSTnode ptLeft;
    PtBSTnode ptRight;
    TElem *ptElem;
};

PtBSTnode BSTnodeCreate (TElem pelem);                  /* criar um n� da �rvore */
unsigned int BSTSize (PtBSTnode proot);                 /* saber o tamanho da �rvore */
unsigned int BSTHeight (PtBSTnode proot);               /* saber a altura da �rvore */

PtBSTnode BSTSearchRec (PtBSTnode proot, TElem pelem) ; /* pesquisa recursiva */
PtBSTnode BSTMinRec (PtBSTnode proot);                  /* pesquisa de minimo recursiva */
PtBSTnode BSTMaxRec (PtBSTnode proot);                  /* pesquisa de m�ximo recursiva */

void BSTInsertRec (PtBSTnode *proot, TElem pelem);      /* inser��o recursiva */
void BSTDeleteRecTotal (PtBSTnode *proot, TElem *pelem);/* remo��o recursiva Total*/
PtBSTnode FindMin (PtBSTnode proot);                    /* encontrar o minimo */
void BSTDestroy (PtBSTnode *proot);                     /* destruir a �rvore */
void nodeRemove (PtBSTnode *proot);
void BSTDeleteRec (PtBSTnode *proot, TElem *pelem);	    /* remo��o recursiva  sem apagar elemento da mem�ria*/

void BSTPreOrderRec (PtBSTnode proot);                  /* travessia em pr�-ordem recursiva */
void BSTInOrderRec (PtBSTnode proot);                   /* travessia em ordem recursiva */
void BSTPostOrderRec (PtBSTnode proot);                 /* travessia em p�s-ordem recursiva */

void BSTByLevel (PtBSTnode proot);          /* mostrar em largura  - Precisa de confirma��o, n�o tenho a certeza se imprime*/
void BSTDisplay (PtBSTnode proot, unsigned int plevel); /* mostrar em profrundidade */

void writeElem(PtBSTnode node);


#endif // BINARYTREE_H_INCLUDED
