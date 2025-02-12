//
// Created by Casa on 06/02/2025.
//

#ifndef TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PESSOA_H
#define TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PESSOA_H

#include <time.h>

typedef struct pessoa {
    int codigo;
    char nome[50];
    int telefone;
    char dataFormatada[11];
    char endereco[50];
    struct pessoa * prox;
    struct pessoa * ant;
}Pessoa;

typedef struct listaDePessoas {
    int quantidadeTotalDePessoas;
    struct pessoa * cabeca;
}ListaDePessoas;

enum camposDePessoa {
    CODIGO,
    NOME,
    TELEFONE,
    DATA,
    ENDERECO,
};

typedef int (*ComparacaoDosCampos)(Pessoa *, void *);
int comparaPessoa(Pessoa *atual, enum camposDePessoa campo, void *valor);

ListaDePessoas * criaListaDePessoas();
Pessoa * criaPessoa(int codigo, char * nome, int telefone, char * data, char * endereco);

void selectListaPessoas(ListaDePessoas ** listaDePessoas, enum camposDePessoa campo, void * valor);
ListaDePessoas * insertIntoListaPessoas(ListaDePessoas ** listaDePessoas, Pessoa * novaPessoa);
ListaDePessoas * deletePessoa(ListaDePessoas ** listaDePessoas, enum camposDePessoa campo, void * valor) ;
ListaDePessoas * updatePessoas(ListaDePessoas **listaDePessoas, Pessoa * camposAtualizados, enum camposDePessoa campo, void * valor);

#endif //TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PESSOA_H
