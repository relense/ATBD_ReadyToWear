#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "binaryTree.h"
#include "filaEstatica.h"

void writeElem(PtBSTnode node)
{
    printf("%s, %d", node->ptElem->nome, node->ptElem->nVisitas);
}

PtBSTnode BSTnodeCreate (TElem pelem)	/* aloca��o do n� decomposto */
{
    PtBSTnode node; /* Criar um n� */

    if ((node = (PtBSTnode) malloc (sizeof (struct abpnode))) == NULL) /* Alocar o n� na mem�ria, se n�o for poss�vel retorna NULL */
        return NULL;

    if ((node->ptElem = (TElem *) malloc (sizeof (TElem))) == NULL) /* Alocar o elemento na mem�ria, se n�o for poss�vel liberta o n� anteriormene guardado e retorna NULL */
    {
        free (node);
        return NULL;
    }

    *node->ptElem = pelem;	/* copiar a informa��o */
    node->ptLeft = NULL;	/* apontar para a esquerda para NULL */

    node->ptRight = NULL;	/* apontar para a direita para NULL */

    return node;
}

void BSTnodeDestroy (PtBSTnode *pelem)	/* liberta��o do n� decomposto */
{
    free ((*pelem)->ptElem);	/* liberta��o do elemento */
    free (*pelem);	/* liberta��o do n� */
    *pelem = NULL;	/* colocar o ponteiro a nulo */
}

unsigned int BSTSize (PtBSTnode proot)  /* c�lculo do n�mero de elementos recursiva */
{
    if (proot == NULL)
        return 0;	/* �rvore vazia */

    else
        return 1 + BSTSize (proot->ptLeft) + BSTSize (proot->ptRight);
}

unsigned int BSTHeight (PtBSTnode proot)
{
    unsigned int leftHeight, rightHeight;

    if (proot == NULL)
        return 0;	/* n� externo no n�vel 0 */

    else
    {
        leftHeight = BSTHeight (proot->ptLeft);	/* sub�rvore esquerda */
        rightHeight = BSTHeight (proot->ptRight);	/* sub�rvore direita */

        if (leftHeight > rightHeight)
            return leftHeight + 1;

        else
            return rightHeight + 1;
    }
}

PtBSTnode BSTSearchRec (PtBSTnode proot, TElem pelem)   /* pesquisa recursiva */
{
    if (proot == NULL)
        return NULL;	/* pesquisa sem sucesso */

    if (strcmp(proot->ptElem->nome, pelem.nome) == 0)
        return proot;	/* pesquisa com sucesso */

    else if (strcmp (proot->ptElem->nome, pelem.nome) > 0)
        return BSTSearchRec (proot->ptLeft, pelem);

    else
        return BSTSearchRec (proot->ptRight, pelem);
}

PtBSTnode BSTMinRec (PtBSTnode proot)  /* pesquisa de m�nimo recursiva */
{
    if (proot == NULL)
        return NULL;

    else if (proot->ptLeft == NULL)
        return proot;

    else
        return BSTMinRec (proot->ptLeft);
}

PtBSTnode BSTMaxRec (PtBSTnode proot)  /* pesquisa de m�ximo recursiva */
{
    if (proot == NULL)
        return NULL;

    else if (proot->ptRight == NULL)
        return proot;

    else
        return BSTMaxRec (proot->ptRight);
}

void BSTInsertRec (PtBSTnode *proot, TElem pelem)  /* inser��o recursiva */
{
    if (*proot == NULL)
    {
        if ((*proot = BSTnodeCreate (pelem)) == NULL)
            return;
    }

    else if (strcmp((*proot)->ptElem->nome, pelem.nome) > 0)	/* sub�rvore esquerda */
        BSTInsertRec (&(*proot)->ptLeft, pelem);

    else if (strcmp((*proot)->ptElem->nome, pelem.nome) < 0)	/* sub�rvore direita */
        BSTInsertRec (&(*proot)->ptRight, pelem);

    else
        return;	/* o elemento j� existe */
}

void nodeDelete (PtBSTnode *proot)
{
    PtBSTnode node = *proot;

    if ((*proot)->ptLeft == NULL && (*proot)->ptRight == NULL)
        BSTnodeDestroy (proot);	/* n� folha - eliminar o elemento */

    else if ((*proot)->ptLeft == NULL)	/* com sub�rvore direita */
    {
        *proot = (*proot)->ptRight;	/* ligar � direita */
        BSTnodeDestroy (&node);	/* eliminar o elemento */
    }

    else if ((*proot)->ptRight == NULL)	/* com sub�rvore esquerda */
    {
        *proot = (*proot)->ptLeft;	/* ligar � esquerda */
        BSTnodeDestroy (&node);	/* eliminar o elemento */
    }

    else	/* com sub�rvores direita e esquerda */
    {
        /* substituir pelo menor elemento da sub�rvore direita */
        *(*proot)->ptElem = *FindMin ((*proot)->ptRight)->ptElem;
        /* remover o menor elemento da sub�rvore direita */
        BSTDeleteRec (&(*proot)->ptRight, (*proot)->ptElem);
    }
}

PtBSTnode FindMin (PtBSTnode proot)
{
    PtBSTnode node = proot;

    while (node->ptLeft != NULL)
        node = node->ptLeft;

    return node;/* devolver um ponteiro para o elemento */
}

void BSTDeleteRecTotal (PtBSTnode *proot, TElem *pelem)	/* remo��o recursiva */
{
    if (*proot == NULL)
        return;	/* �rvore vazia ou elemento inexistente */

    if (strcmp((*proot)->ptElem->nome, pelem->nome) > 0)
        BSTDeleteRec (&(*proot)->ptLeft, pelem);

    else if (strcmp((*proot)->ptElem->nome, pelem->nome) < 0)
        BSTDeleteRec (&(*proot)->ptRight, pelem);

    else
    {
        *pelem = *(*proot)->ptElem;	/* copiar o elemento */
        nodeDelete(proot);	/* eliminar o elemento */
    }
}

void BSTDestroy (PtBSTnode *proot)
{
    if (*proot != NULL)
    {
        BSTDestroy (&(*proot)->ptLeft);	/* destruir a sub�rvore esquerda */
        BSTDestroy (&(*proot)->ptRight);	/* destruir a sub�rvore direita */
        BSTnodeDestroy (proot);	/* eliminar o elemento */
    }
}

void BSTPreOrderRec (PtBSTnode proot)  /* travessia em pr�-ordem recursiva */
{
    if (proot != NULL)
    {
        writeElem(proot);	/* imprimir o conte�do do elemento */
        BSTPreOrderRec (proot->ptLeft);
        BSTPreOrderRec (proot->ptRight);
    }
}

void BSTInOrderRec (PtBSTnode proot)  /* travessia em ordem recursiva */
{
    if (proot != NULL)
    {
        BSTInOrderRec (proot->ptLeft);
        writeElem(proot);	/* imprimir o conte�do do elemento */
        BSTInOrderRec (proot->ptRight);
    }
}

void BSTPostOrderRec (PtBSTnode proot)  /* travessia em p�s-ordem recursiva */
{
    if (proot != NULL)
    {
        BSTPostOrderRec (proot->ptLeft);
        BSTPostOrderRec (proot->ptRight);
        writeElem(proot);	/* imprimir o conte�do do elemento */
    }
}

void BSTByLevel (PtBSTnode proot)
{
    PtBSTnode node;
    PtQueue queue;
    int nodesInLevel = 1;
    int altura = BSTHeight(proot);
    int alturaDouble = (double) altura;
    int numeroEspacos;

    FILE* arvore;
    arvore = fopen("arvore.txt", "w+");
    if(arvore == NULL)perror("arvore.txt");

    if (proot == NULL)
    {
        printf("\nArvore vazia\n");
        return;	/* �rvore vazia */
    }
    queue = queueCreate (100);

    if ((queue == NULL)) return;

    queueEnqueue (queue, proot);	/* armazenar a raiz */

    while (!queueIsEmpty (queue))
    {
        queueDequeue (queue, &node);	/* retirar o n� */

        numeroEspacos = pow(2, alturaDouble);

        while( numeroEspacos != 0)
        {
            printf(" ");
            numeroEspacos--;
        }
        alturaDouble--;

        printf("%s, %d", node->ptElem->nome, node->ptElem->nVisitas);
        fprintf(arvore,"%s, %d", node->ptElem->nome, node->ptElem->nVisitas);

        nodesInLevel--;

        if(nodesInLevel == 0)
        {
            printf("\n");
            fprintf(arvore,"\n");
        }

        /* armazenar a raiz da sub�rvore esquerda */
        if (node->ptLeft != NULL)
        {
            queueEnqueue (queue, node->ptLeft);
            nodesInLevel++;
        }

        /* armazenar a raiz da sub�rvore direita */
        if (node->ptRight != NULL)
        {
            queueEnqueue (queue, node->ptRight);
            nodesInLevel++;
        }
    }

    queueDestroy (&queue);	/* destruir a fila */
    fclose(arvore);
}

void listInOrder (PtBSTnode proot, TElem plist[], unsigned int *pcount)
{
    if (proot != NULL)
    {
        listInOrder (proot->ptLeft, plist, pcount);	/* �rvore esquerda */
        plist[(*pcount)++] = *proot->ptElem;	/* colocar elemento */
        listInOrder (proot->ptRight, plist, pcount);	/* �rvore direita */
    }
}

void BSTDisplay (PtBSTnode proot, unsigned int plevel)
{
    unsigned int i;

    if (proot == NULL)
    {
        for (i = 0; i < plevel; i++) printf ("\t");
        printf ("*\n");
        return;
    }


    BSTDisplay (proot->ptRight, plevel + 1);

    for (i = 0; i < plevel; i++) printf ("\t");

    writeElem(proot);
    printf("\n");

    BSTDisplay (proot->ptLeft, plevel + 1);
}

void nodeRemove (PtBSTnode *proot)
{

    if ((*proot)->ptLeft == NULL)	/* com sub�rvore direita */
    {
        *proot = (*proot)->ptRight;	/* ligar � direita */
    }

    else if ((*proot)->ptRight == NULL)	/* com sub�rvore esquerda */
    {
        *proot = (*proot)->ptLeft;	/* ligar � esquerda */
    }

    else	/* com sub�rvores direita e esquerda */
    {
        /* substituir pelo menor elemento da sub�rvore direita */
        *(*proot)->ptElem = *FindMin ((*proot)->ptRight)->ptElem;
        /* remover o menor elemento da sub�rvore direita */
        BSTDeleteRec (&(*proot)->ptRight, (*proot)->ptElem);
    }
}

void BSTDeleteRec (PtBSTnode *proot, TElem *pelem)	/* remo��o recursiva  sem apagar elemento da mem�ria*/
{
    if (*proot == NULL)
        return;	/* �rvore vazia ou elemento inexistente */

    if (strcmp((*proot)->ptElem->nome, pelem->nome) > 0)
        BSTDeleteRec (&(*proot)->ptLeft, pelem);

    else if (strcmp((*proot)->ptElem->nome, pelem->nome) < 0)
        BSTDeleteRec (&(*proot)->ptRight, pelem);

    else
    {
        nodeDelete(proot);	/* eliminar o elemento */
    }
}
