//
// Created by Casa on 06/02/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "..\include\pessoa.h"

ListaDePessoas * criaListaDePessoas() {
    ListaDePessoas * listaDePessoas = (ListaDePessoas *) malloc(sizeof(typeof(ListaDePessoas)));
    if(listaDePessoas == NULL) {
        return NULL;
    }

    listaDePessoas->cabeca = NULL;
    listaDePessoas->quantidadeTotalDePessoas = 0;

    return listaDePessoas;
}

Pessoa * criaPessoa(int codigo, char * nome, int telefone, struct tm dataDeNascimento, char * endereco) {
    Pessoa * novaPessoa = (Pessoa *) malloc(sizeof(typeof(Pessoa)));
    if(novaPessoa == NULL) {
        return NULL;
    }

    novaPessoa->codigo = codigo;
    strcpy(novaPessoa->nome, nome);
    novaPessoa->telefone = telefone;
    novaPessoa->dataDeNascimento = dataDeNascimento;
    strcpy(novaPessoa->endereco, endereco);

    novaPessoa->prox = NULL;
    novaPessoa->ant = NULL;

    return novaPessoa;
}

ListaDePessoas * inserePessoaNaListaDeNovos(ListaDePessoas ** listaDePessoas, Pessoa * novaPessoa) {
    if(novaPessoa == NULL) {
        return NULL;
    }

    if((*listaDePessoas)->cabeca != NULL) {
        novaPessoa->prox = (*listaDePessoas)->cabeca;
        (*listaDePessoas)->cabeca->ant = novaPessoa;
    }

    (*listaDePessoas)->cabeca = novaPessoa;
    (*listaDePessoas)->quantidadeTotalDePessoas++;

    return *listaDePessoas;
}

//inserir pessoa no bin
// deletar pessoa
// exibir pessoa
//extrair pessoa no bin
