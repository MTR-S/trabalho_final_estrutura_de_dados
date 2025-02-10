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
    struct tm dataDeNascimento;
    char * dataFormatada;
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

int comparaCodigo(Pessoa *p, void *valor);
int comparaNome(Pessoa *p, void *valor);
int comparaTelefone(Pessoa *p, void *valor);
int comparaData(Pessoa *p, void *valor);
ListaDePessoas * criaListaDePessoas();
Pessoa * criaPessoa(int codigo, char * nome, int telefone, struct tm dataDeNascimento, char * endereco);
ListaDePessoas * selectListaPessoas(ListaDePessoas ** listaDePessoas, enum camposDePessoa campo, void * valor);
ListaDePessoas * insertIntoListaPessoas(ListaDePessoas ** listaDePessoas, Pessoa * novaPessoa);
ListaDePessoas * deletePessoa(ListaDePessoas ** listaDePessoas, int codigo);

#endif //TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PESSOA_H
