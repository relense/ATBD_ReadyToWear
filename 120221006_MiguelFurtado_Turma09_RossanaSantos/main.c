#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestorFicheiros.h"
#include "stackDinamico.h"
#include "loja.h"
#include "gestorLoja.h"
#include "iterator.h"
#include "binaryTree.h"

void abrirFicheiro(char nomeFichero[], Loja loja);
void escolherOpcao();
void menu(Loja loja, char escolha);
void imprimirList(PtList lista);
void gerarRelatorio(Loja loja);

int main()
{
    Loja loja = criarLoja();
    char escolha;

    while(escolha != 'E')
    {
        printf("\nA - Carregar Ficheiro de Entrada\n");
        printf("B - Gerar Relatorio\n");
        printf("C - Imprimir Arvore de Registo\n");
        printf("D - Imprimir Lista\n");
        printf("E - Sair\n");

        scanf("%c", &escolha);

        menu(loja, escolha);
    }

    return 0;
}

void abrirFicheiro(char nomeFicheiro[], Loja loja)
{
    FILE *file;
    file = fopen(nomeFicheiro, "r");
    if(nomeFicheiro == NULL)perror("File does not exist");

    Ficheiro ficheiro = criaFicheiro();

    if(carregarFicheiro(file, ficheiro, loja->dataLoja) == 0)
    {

        fclose(file);

        gerirListaClientes(loja, ficheiro->stackClientes);
        guardarFicheiro(loja->stack, ficheiro);
    }

}

void menu(Loja loja, char escolha)
{
    char nomeFicheiro[10];

    switch(escolha)
    {
    case 'A':
        printf("Escreva o nome do ficheiro:");
        scanf("%s", nomeFicheiro);
        abrirFicheiro(nomeFicheiro, loja);
        break;
    case 'B':
        gerarRelatorio(loja);
        break;
    case 'C':
        BSTByLevel(loja->clienteNo);
        break;
    case 'D':
        imprimirList(loja->lista);
        break;
    case 'E':
        exit(0);
        break;
    default:
        printf("Invalid Option\n");
    }
}

void imprimirList(PtList lista)
{
    if(listSize(lista) == 0)
    {
        printf("\nLista de cliente vazia\n");
        return;
    }

    FILE* listaClientes;
    listaClientes = fopen("listaClientes.txt", "w+");
    if(listaClientes == NULL)perror("listaClientes.txt");

    PtListIterator ptIt = listIteratorCreate(lista);
    Cliente *aux;

    printf("\n");
    while(hasNextElem(ptIt))
    {
        aux = nextElem(ptIt);
        if(aux->estado == 0)
        {
            fprintf(listaClientes,"%d - %s, %s, %dEuros estado inativo DATA: %d/%d/%d\n ", aux->id, aux->nome, aux->genero, aux->valorDeCompras, aux->dia, aux->mes, aux->ano);
            printf("%d - %s, %s, %dEuros estado inativo DATA: %d/%d/%d\n ", aux->id, aux->nome, aux->genero, aux->valorDeCompras,aux->dia, aux->mes, aux->ano);
        }
        else
        {
            fprintf(listaClientes,"%d - %s, %s, %dEuros estado ativo DATA: %d/%d/%d\n ", aux->id, aux->nome, aux->genero, aux->valorDeCompras, aux->dia, aux->mes, aux->ano);
            printf("%d - %s, %s, %dEuros estado ativo DATA: %d/%d/%d\n ", aux->id, aux->nome, aux->genero, aux->valorDeCompras, aux->dia, aux->mes, aux->ano);
        }
    }
    printf("\n");

    fclose(listaClientes);
}

void gerarRelatorio(Loja loja)
{
    if(stackIsEmptyDinamico(loja->stack))
    {
        printf("\nNao existem ficheiros carregados para gerar relatorio\n");
        return;
    }

    FILE* relatorio;
    relatorio = fopen("relatorio.txt", "w+");
    if(relatorio == NULL)perror("relatorio.txt");

    PtStackD stackAux = stackCreateDinamico();
    Ficheiro ficheiro;

    clienteQueMaisVisitou(loja);
    generoQueMaisVisitou(loja);
    calcularConsumosMedios(loja);

    printf("\n");
    fprintf(relatorio, "Numero de clientes que visitaram a loja: %d\n", loja->nrClienteVisitaram);
    printf("Numero de clientes que visitaram a loja: %d\n", loja->nrClienteVisitaram);

    fprintf(relatorio, "Numero de clientes que efetuaram pelo menos uma compra: %d\n", loja->nrClienteVistaramCompras);
    printf("Numero de clientes que efetuaram pelo menos uma compra: %d\n", loja->nrClienteVistaramCompras);

    printf("Numero de clientes que so visitaram: %d\n", loja->nrClientesSemCompras);
    fprintf(relatorio, "Numero de clientes que so visitaram: %d\n", loja->nrClientesSemCompras);

    printf("Valores de consumos totais\n");
    fprintf(relatorio, "Valores de consumos totais\n");

    while(!stackIsEmptyDinamico(loja->stack))
    {
        stackPopDinamico(loja->stack, &ficheiro);
        stackPushDinamico(stackAux, ficheiro);
        printf("\t%d/%d/%d:\n", ficheiro->dia, ficheiro->mes, ficheiro->ano);
        fprintf(relatorio, "\t%d/%d/%d:\n", ficheiro->dia, ficheiro->mes, ficheiro->ano);
        consumosTotais(ficheiro, relatorio);
    }

    while(!stackIsEmptyDinamico(stackAux))
    {
        stackPopDinamico(stackAux, &ficheiro);
        stackPushDinamico(loja->stack, ficheiro);
    }

    stackDestroyDinamico(&stackAux);

    printf("Valores de consumos medios:\n");
    fprintf(relatorio, "Valores de consumos medios: \n");

    PtListIterator ptIt = listIteratorCreate(loja->lista);
    Cliente *aux;

    while(hasNextElem(ptIt))
    {
        aux = nextElem(ptIt);
        if(aux->consumoMedio != 0)
        {
            printf("\t   %s, %d\n", aux->nome, aux->consumoMedio);
            fprintf(relatorio, "\t   %s, %d\n", aux->nome, aux->consumoMedio);
        }
        else
            continue;
    }

    printf("Genero que mais visita a loja: %s\n", loja->generoMaisVisitou);
    fprintf(relatorio, "Genero que mais vista a loja: %s\n", loja->generoMaisVisitou);

    printf("Cliente que mais gastou na loja: %d, %s, %s, %d\n", loja->clienteGastouMais->id, loja->clienteGastouMais->nome, loja->clienteGastouMais->genero, loja->clienteGastouMais->valorDeCompras);
    fprintf(relatorio, "Cliente que mais gastou na loja: %d, %s, %s, %d\n", loja->clienteGastouMais->id, loja->clienteGastouMais->nome, loja->clienteGastouMais->genero, loja->clienteGastouMais->valorDeCompras);
    printf("\n");

    fclose(relatorio);
}


