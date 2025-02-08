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
    char endereco[50];
    struct pessoa * prox;
    struct pessoa * ant;
}Pessoa;

typedef struct listaDePessoas {
    int quantidadeTotalDePessoas;
    struct pessoa * cabeca;
}ListaDePessoas;

ListaDePessoas * criaListaDePessoas();
Pessoa * criaPessoa(int codigo, char * nome, int telefone, struct tm dataDeNascimento, char * endereco);
ListaDePessoas * inserePessoaNaListaDeNovos(ListaDePessoas ** listaDePessoas, Pessoa * novaPessoa);

#endif //TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PESSOA_H
