#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackDinamico.h"
#include "ficheiros.h"
#include "cliente.h"
#include "stackEstatico.h"
#include "gestorFicheiros.h"
#include "ficheiros.h"
#include "dataLoja.h"

int carregarFicheiro(FILE* file, Ficheiro ficheiro, DataLoja data)
{
    char str[30];
    int count = 0;

    //Ler a data
    fgets(str, sizeof str, file);

    int dia, mes, ano;
    dia = atoi(strtok(str, "/"));
    mes = atoi(strtok(NULL, "/"));
    ano = atoi(strtok(NULL, "/"));

    if(mes > 12 || mes < 1 || dia > 31 || dia < 1 || ano < 2016){
        printf("ERRO DATA DE FICHEIRO INVALIDA\n");
        return 1;
    }

    if(ano == 2016 && dia < 31 && mes == 1){
        printf("ERRO DATA DE FICHEIRO INVALIDA\n");
        return 1;
    }

    if((ano == data->ano && mes == data->mes && dia == data->dia) ||(ano < data->ano && mes < data->mes && dia < data->dia))
    {
        printf("Ficheiro ja existente\n");
        return 1;
    }
    else
    {
        ficheiro->dia = dia;
        ficheiro->mes = mes;
        ficheiro->ano = ano;

        data->ano = ficheiro->ano;
        data->dia = ficheiro->dia;
        data->mes = ficheiro->mes;
    }

    //Ler os clientes
    while(fgets(str, sizeof str, file) != NULL)
    {
        Cliente cliente = criarCliente();
        cliente.dia = dia;
        cliente.mes = mes;
        cliente.ano = ano;

        strcpy(cliente.nome, strtok(str, ","));
        count = 0;

        while(count <= 1)
        {
            if(count == 0)
            {
                count++;
                strcpy(cliente.genero, strtok(NULL, ","));

                if(strcmp(cliente.genero, "f") == 0)
                    strcpy(cliente.genero, "feminino");
                else
                    strcpy(cliente.genero, "masculino");
            }
            else
            {
                count++;
                cliente.valorDeCompras = atoi(strtok(NULL, ","));
            }
        }
        stackPushEstatico(ficheiro->stackClientes, cliente);
    }

    ficheiro->stackClientes = ordenaPilha(ficheiro->stackClientes);

    return 0;
}

void guardarFicheiro(PtStackD stack, Ficheiro ficheiro)
{
    stackPushDinamico(stack, ficheiro);
}

void imprimePilha(PtStackE stack)
{
    PtStackE aux = stackCreateEstatico();
    Cliente cliente = criarCliente();

    while(!stackIsEmptyEstatico(stack))
    {
        stackPopEstatico(stack, &cliente);
        stackPushEstatico(aux, cliente);
    }

    while(!stackIsEmptyEstatico(aux))
    {
        stackPopEstatico(aux, &cliente);
        printf("NOME: %s\n", cliente.nome);
        stackPushEstatico(stack, cliente);
    }

    stackDestroyEstatico(&aux);
}

PtStackE ordenaPilha(PtStackE stack)
{
    PtStackE aux = stackCreateEstatico();
    Cliente cliente = criarCliente();

    while(!stackIsEmptyEstatico(stack))
    {
        stackPopEstatico(stack, &cliente);
        stackPushEstatico(aux, cliente);
    }

    return aux;
}
