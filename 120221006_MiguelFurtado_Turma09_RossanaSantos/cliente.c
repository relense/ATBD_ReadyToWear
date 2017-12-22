#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

/*Método para criar um cliente*/
Cliente criarCliente(void)
{
    Cliente cliente;

    cliente.estado = 1; /*Ativo se igual a 1, inativo se igual a 0*/
    cliente.nVisitas = 0;
    cliente.nVisitasComCompras = 0;
    cliente.consumoMedio = 0;
    cliente.visto = 0;
    cliente.dia = 0;
    cliente.mes = 0;
    cliente.ano = 0;

    return cliente;
}
