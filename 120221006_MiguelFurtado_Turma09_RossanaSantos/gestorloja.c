#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "stackEstatico.h"
#include "iterator.h"
#include "cliente.h"
#include "gestorLoja.h"
#include "loja.h"
#include "dataLoja.h"
#include "binaryTree.h"

void gerirListaClientes(Loja loja, PtStackE stackClientes)
{
    PtStackE aux = stackCreateEstatico();

    Cliente clienteAux = criarCliente();
    Cliente aux2 = criarCliente();

    while(!stackIsEmptyEstatico(stackClientes))
    {
        stackPopEstatico(stackClientes, &clienteAux);
        stackPushEstatico(aux, clienteAux);

        if(listSize(loja->lista) == 0)
        {
            decompoeClienteNaoExiste(&clienteAux, loja);
            listAdd(loja->lista, loja->lista->nElems, clienteAux);
            loja->clienteNo = BSTnodeCreate(clienteAux);
            strcpy(aux2.nome, clienteAux.nome);
        }

        else
        {
            if(encontrarCliente(loja, clienteAux, aux2) == 0)
            {
                decompoeClienteNaoExiste(&clienteAux, loja);
                listAdd(loja->lista, loja->lista->nElems, clienteAux);
                BSTInsertRec(&loja->clienteNo, clienteAux);
                strcpy(aux2.nome, clienteAux.nome);
            }
            else
            {
                strcpy(aux2.nome, clienteAux.nome);
            }
        }
    }

    while(!stackIsEmptyEstatico(aux))
    {
        stackPopEstatico(aux, &clienteAux);
        stackPushEstatico(stackClientes, clienteAux);
    }

    stackDestroyEstatico(&aux);
    confirmarAtividade(loja);
}


void decompoeClienteNaoExiste(Cliente *cliente, Loja loja)
{
    cliente->id = loja->lista->nElems + 1;

    if(cliente->valorDeCompras == 0)
    {
        cliente->nVisitas++;

        loja->nrClienteVisitaram++;
        loja->nrClientesSemCompras++;
    }
    else
    {
        cliente->nVisitas++;
        cliente->nVisitasComCompras++;

        loja->nrClienteVisitaram++;
        loja->nrClienteVistaramCompras++;
    }
}

int encontrarCliente(Loja loja, Cliente cliente, Cliente global)
{
    PtListIterator ptIt = listIteratorCreate(loja->lista);
    Cliente *clienteAux;
    PtBSTnode clienteNo;



    if(strcmp(cliente.nome, global.nome) != 0)
    {
        if(listSize(loja->lista) == 1)
        {
            clienteAux = nextElem(ptIt);
            clienteNo = BSTSearchRec(loja->clienteNo, cliente);

            if(strcmp(clienteAux->nome, cliente.nome) == 0)
            {
                if(cliente.valorDeCompras == 0)
                {
                    clienteAux->nVisitas++;

                    if(clienteAux->estado == 1)
                    {
                        clienteNo->ptElem->nVisitas++;
                    }

                    loja->nrClienteVisitaram++;
                    loja->nrClientesSemCompras++;

                    clienteAux->dia = loja->dataLoja->dia;
                    clienteAux->mes = loja->dataLoja->mes;
                    clienteAux->ano = loja->dataLoja->ano;
                }
                else
                {
                    clienteAux->nVisitas++;
                    if(clienteAux->estado != 1)
                    {
                        BSTInsertRec(&loja->clienteNo, cliente);
                        clienteAux->estado = 1;
                        clienteNo = BSTSearchRec(loja->clienteNo, cliente);
                    }

                    if(clienteAux->estado == 1)
                    {
                        clienteNo->ptElem->nVisitas++;
                    }

                    clienteAux->nVisitasComCompras++;
                    clienteAux->valorDeCompras = clienteAux->valorDeCompras + cliente.valorDeCompras;
                    clienteAux->dia = loja->dataLoja->dia;
                    clienteAux->mes = loja->dataLoja->mes;
                    clienteAux->ano = loja->dataLoja->ano;

                    loja->nrClienteVisitaram++;
                    loja->nrClienteVistaramCompras++;
                }
                return 1;
            }
        }

        while(hasNextElem(ptIt))
        {
            clienteAux = nextElem(ptIt);
            clienteNo = BSTSearchRec(loja->clienteNo, cliente);

            if(strcmp(clienteAux->nome, cliente.nome) == 0)
            {
                if(cliente.valorDeCompras == 0)
                {
                    clienteAux->nVisitas++;

                    if(clienteAux->estado == 1)
                    {
                        clienteNo->ptElem->nVisitas++;
                    }

                    clienteAux->dia = loja->dataLoja->dia;
                    clienteAux->mes = loja->dataLoja->mes;
                    clienteAux->ano = loja->dataLoja->ano;

                    loja->nrClienteVisitaram++;
                    loja->nrClientesSemCompras++;
                }
                else
                {
                    clienteAux->nVisitas++;

                     if(clienteAux->estado != 1)
                    {
                        BSTInsertRec(&loja->clienteNo, cliente);
                        clienteAux->estado = 1;
                        clienteNo = BSTSearchRec(loja->clienteNo, cliente);
                    }

                    if(clienteAux->estado == 1)
                    {
                        clienteNo->ptElem->nVisitas++;
                    }

                    clienteAux->nVisitasComCompras++;
                    clienteAux->valorDeCompras = clienteAux->valorDeCompras + cliente.valorDeCompras;
                    clienteAux->dia = loja->dataLoja->dia;
                    clienteAux->mes = loja->dataLoja->mes;
                    clienteAux->ano = loja->dataLoja->ano;

                    loja->nrClienteVisitaram++;
                    loja->nrClienteVistaramCompras++;
                }
                return 1;
            }
        }
    }
    else
    {
        if(listSize(loja->lista) == 1)
        {
            clienteAux = nextElem(ptIt);

            if(strcmp(clienteAux->nome, cliente.nome) == 0)
            {
                clienteAux->valorDeCompras = clienteAux->valorDeCompras + cliente.valorDeCompras;

                return 1;
            }
        }

        while(hasNextElem(ptIt))
        {
            clienteAux = nextElem(ptIt);

            if(strcmp(clienteAux->nome, cliente.nome) == 0)
            {
                clienteAux->valorDeCompras = clienteAux->valorDeCompras + cliente.valorDeCompras;

                return 1;
            }
        }
    }
    return 0;
}

void clienteQueMaisVisitou(Loja loja)
{
    PtListIterator ptIt = listIteratorCreate(loja->lista);
    Cliente *aux;

    aux = nextElem(ptIt);

    loja->clienteGastouMais = aux;

    while(hasNextElem(ptIt))
    {
        aux = nextElem(ptIt);
        if(loja->clienteGastouMais->valorDeCompras < aux->valorDeCompras)
        {
            loja->clienteGastouMais = aux;
        }
    }
}

void generoQueMaisVisitou(Loja loja)
{
    PtListIterator ptIt = listIteratorCreate(loja->lista);
    Cliente *aux;
    int masculino = 0, feminino = 0;

    while(hasNextElem(ptIt))
    {
        aux = nextElem(ptIt);
        if(strcmp(aux->genero, "masculino") == 0)
            masculino++;
        else
            feminino++;
    }

    if(masculino > feminino)
        strcpy(loja->generoMaisVisitou, "masculino");
    else if(masculino < feminino)
        strcpy(loja->generoMaisVisitou, "feminino");
    else
        strcpy(loja->generoMaisVisitou, "igual");
}

void calcularConsumosMedios(Loja loja)
{
    PtListIterator ptIt = listIteratorCreate(loja->lista);
    Cliente *aux;

    while(hasNextElem(ptIt))
    {
        aux = nextElem(ptIt);
        if(aux->valorDeCompras > 0)
            aux->consumoMedio = aux->valorDeCompras / aux->nVisitas;
        else
            continue;
    }
}

void consumosTotais(Ficheiro ficheiro, FILE* file)
{
    PtStackE stackAux = stackCreateEstatico();
    PtStackE stackAux2 = stackCreateEstatico();
    Cliente clienteAux1;
    Cliente clienteAux2;

    unsigned int size;
    stackSizeEstatico(ficheiro->stackClientes, &size);

    while(size != 0)
    {
        stackPopEstatico(ficheiro->stackClientes, &clienteAux1);
        stackPushEstatico(stackAux, clienteAux1);
        size--;

        while(!stackIsEmptyEstatico(ficheiro->stackClientes))
        {
            stackPopEstatico(ficheiro->stackClientes, &clienteAux2);
            if(strcmp(clienteAux1.nome, clienteAux2.nome) == 0)
            {
                clienteAux1.valorDeCompras += clienteAux2.valorDeCompras;
                stackPushEstatico(stackAux, clienteAux2);
                size--;
            }
            else
            {
                stackPushEstatico(stackAux2, clienteAux2);
            }
        }

        if(clienteAux1.valorDeCompras > 0)
        {
            printf("\t   %s, %d\n", clienteAux1.nome, clienteAux1.valorDeCompras);
            fprintf(file, "\t   %s, %d\n", clienteAux1.nome, clienteAux1.valorDeCompras);
        }

        while(!stackIsEmptyEstatico(stackAux2))
        {
            stackPopEstatico(stackAux2, &clienteAux2);
            stackPushEstatico(ficheiro->stackClientes, clienteAux2);
        }
    }

    while(!stackIsEmptyEstatico(stackAux))
    {
        stackPopEstatico(stackAux, &clienteAux1);
        stackPushEstatico(ficheiro->stackClientes, clienteAux1);
    }

    stackDestroyEstatico(&stackAux);
    stackDestroyEstatico(&stackAux2);
}

void confirmarAtividade(Loja loja)
{
    PtListIterator ptIt = listIteratorCreate(loja->lista);
    Cliente *aux;
    int diasDescontar;

    while(hasNextElem(ptIt))
    {
        diasDescontar = 30;
        aux = nextElem(ptIt);
        if(aux->mes == loja->dataLoja->mes)
        {
            if((aux->dia - loja->dataLoja->dia) >= 30)
            {
                aux->estado = 0;
                aux->valorDeCompras = 0;
                BSTDeleteRec(&loja->clienteNo, aux);
            }
            else
            {
                continue;
            }
        }
        else
        {
            if((loja->dataLoja->mes - aux->mes) >= 2)
            {
                aux->estado = 0;
                aux->valorDeCompras = 0;
                BSTDeleteRec(&loja->clienteNo, aux);
            }
            else
            {
                if(loja->dataLoja->mes & 1)
                {
                    diasDescontar = diasDescontar - loja->dataLoja->dia;
                    if(aux->dia < (30 - diasDescontar))
                    {
                        aux->estado = 0;
                        aux->valorDeCompras = 0;
                        BSTDeleteRec(&loja->clienteNo, aux);
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    diasDescontar = diasDescontar - loja->dataLoja->dia;
                    if(aux->dia < (31 - diasDescontar))
                    {
                        aux->estado = 0;
                        aux->valorDeCompras = 0;
                        BSTDeleteRec(&loja->clienteNo, aux);
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
}
