#ifndef GESTORLOJA_H_INCLUDED
#define GESTORLOJA_H_INCLUDED
#include "list.h"
#include "stackEstatico.h"
#include "cliente.h"
#include "loja.h"

void gerirListaClientes(Loja loja, PtStackE stackClientes); /**/
void decompoeClienteNaoExiste(Cliente *cliente, Loja loja);
void decompoeClienteExiste(Cliente *cliente, Cliente info);
int encontrarCliente(Loja loja, Cliente cliente, Cliente global);
void clienteQueMaisVisitou(Loja loja);
void generoQueMaisVisitou(Loja loja);
void calcularConsumosMedios(Loja loja);
void consumosTotais(Ficheiro ficheiro, FILE* file);
void confirmarAtividade(Loja loja);

#endif // GESTORLOJA_H_INCLUDED
