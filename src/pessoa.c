//
// Created by Casa on 06/02/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "..\include\pessoa.h"
#include "../include/menu.h"

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

    char dataFormatada [11];
    strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%y", &(novaPessoa->dataDeNascimento));

    novaPessoa->dataFormatada = dataFormatada;

    novaPessoa->prox = NULL;
    novaPessoa->ant = NULL;

    return novaPessoa;
}

int comparaCodigo(Pessoa *p, void *valor) {
    return p->codigo == *(int *)valor;
}

int comparaNome(Pessoa *p, void *valor) {
    return strstr(p->nome, (char *)valor) != NULL;
}

int comparaTelefone(Pessoa *p, void *valor) {
    return p->telefone == *(int *)valor;
}

int comparaData(Pessoa *p, void *valor) {
    return strcmp(p->dataFormatada, (char *)valor) == 0;
}

ListaDePessoas * selectListaPessoas(ListaDePessoas ** listaDePessoas, enum camposDePessoa campo, void * valor) {
    if(*listaDePessoas == NULL) {
        return NULL;
    }

    ComparacaoDosCampos comparacao = NULL;

    switch (campo) {
        case CODIGO:
            comparacao = comparaCodigo;
            break;
        case NOME:
            comparacao = comparaNome;
            break;
        case TELEFONE:
            comparacao = comparaTelefone;
            break;
        case DATA:
            comparacao = comparaData;
            break;
        default:
            return NULL;
    }

    ListaDePessoas *listaFiltrada = criaListaDePessoas();
    Pessoa *atual = (*listaDePessoas)->cabeca;

    while (atual != NULL) {
        if (comparacao(atual, valor)) {
            exibirPessoa(*atual);
        }
        atual = atual->prox;
    }

    return listaFiltrada;
}


ListaDePessoas * insertIntoListaPessoas(ListaDePessoas ** listaDePessoas, Pessoa * novaPessoa) {
    if(novaPessoa == NULL) {
        return NULL;
    }

    if(*listaDePessoas == NULL) {
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

ListaDePessoas * deletePessoa(ListaDePessoas ** listaDePessoas, int codigo) {
    if(*listaDePessoas == NULL) {
        return NULL;
    }

    Pessoa * listaDePessoasAuxiliar = (*listaDePessoas)->cabeca;

    while(listaDePessoasAuxiliar != NULL && listaDePessoasAuxiliar->codigo != codigo) {
        listaDePessoasAuxiliar = listaDePessoasAuxiliar->prox;
    }

    if(listaDePessoasAuxiliar == NULL) {
        return NULL;
    }

    if(listaDePessoasAuxiliar->ant == NULL && listaDePessoasAuxiliar->prox == NULL) {
        (*listaDePessoas)->cabeca = NULL;
    }
    else if(listaDePessoasAuxiliar->ant == NULL) {
        (*listaDePessoas)->cabeca = listaDePessoasAuxiliar->prox;
        listaDePessoasAuxiliar->prox->ant = NULL;
    }

    else if(listaDePessoasAuxiliar->prox == NULL) {
        listaDePessoasAuxiliar->ant->prox = NULL;
    }

    else {
        listaDePessoasAuxiliar->ant->prox = listaDePessoasAuxiliar->prox;
        listaDePessoasAuxiliar->prox->ant = listaDePessoasAuxiliar->ant;
    }

    (*listaDePessoas)->quantidadeTotalDePessoas --;
    free(listaDePessoasAuxiliar);

    return *listaDePessoas;
}


//select
//insert into - OK
//delete
//update

