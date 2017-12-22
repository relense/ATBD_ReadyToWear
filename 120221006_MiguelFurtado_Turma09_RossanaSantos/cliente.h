#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct cliente
{
    char nome[20];
    char genero[20];
    int dia, mes, ano;
    int nVisitas, nVisitasComCompras, id, valorDeCompras, estado, consumoMedio, visto;

} Cliente;

/*Método para criar um cliente*/
Cliente criarCliente(void);

#endif // CLIENTE_H_INCLUDED
