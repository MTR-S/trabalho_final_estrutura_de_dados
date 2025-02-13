//
// Created by Casa on 06/02/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/pessoa.h"
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

Pessoa * criaPessoa(int codigo, char * nome, int telefone, char * data, char * endereco) {
    Pessoa * novaPessoa = (Pessoa *) malloc(sizeof(typeof(Pessoa)));
    if(novaPessoa == NULL) {
        return NULL;
    }

    novaPessoa->codigo = codigo;
    strcpy(novaPessoa->nome, nome);
    novaPessoa->telefone = telefone;
    strcpy(novaPessoa->endereco, endereco);
    strcpy(novaPessoa->dataFormatada, data);

    novaPessoa->prox = NULL;
    novaPessoa->ant = NULL;

    return novaPessoa;
}

int comparaPessoa(Pessoa *atual, enum camposDePessoa campo, void *valor) {
    switch (campo) {
        case CODIGO:
            return (atual->codigo == *(int *)valor);

        case NOME:
            return (strcmp(atual->nome, (char *)valor) == 0);

        case TELEFONE:
            return atual->telefone == *(int *)valor;

        case DATA:
            return (strcmp(atual->dataFormatada, (char *)valor) == 0);

        case ENDERECO:
            return (strcmp(atual->endereco, (char *)valor) == 0);

        default:
            return 0;
    }
}
void selectListaPessoas(ListaDePessoas **listaDePessoas, enum camposDePessoa campo, void *valor) {
    if ((*listaDePessoas)->cabeca == NULL) {
        return;
    }

    Pessoa * atual = (*listaDePessoas)->cabeca;

    while (atual != NULL) {
        if (comparaPessoa(atual, campo, valor)) {
            exibirPessoa(*atual);
        }
        atual = atual->prox;
    }
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

ListaDePessoas *deletePessoa(ListaDePessoas **listaDePessoas, enum camposDePessoa campo, void *valor) {
    if ((*listaDePessoas)->cabeca == NULL) {
        return NULL;
    }

    Pessoa * atual = (*listaDePessoas)->cabeca;

    while (atual != NULL) {
        if (comparaPessoa(atual, campo, valor)) {
            if (atual->ant == NULL) {
                (*listaDePessoas)->cabeca = atual->prox;
                if (atual->prox != NULL) {
                    atual->prox->ant = NULL;
                }
            } else {
                atual->ant->prox = atual->prox;
                if (atual->prox != NULL) {
                    atual->prox->ant = atual->ant;
                }
            }

            Pessoa *temp = atual;
            atual = atual->prox;
            free(temp);
            (*listaDePessoas)->quantidadeTotalDePessoas--;
        } else {
            atual = atual->prox;
        }
    }

    return *listaDePessoas;
}

ListaDePessoas * updatePessoas(ListaDePessoas **listaDePessoas, Pessoa * camposAtualizados, enum camposDePessoa campo, void * valor) {
    if((*listaDePessoas)->cabeca == NULL) {
        return NULL;
    }

    Pessoa * atual = (*listaDePessoas)->cabeca;

    while (atual != NULL) {
        if (comparaPessoa(atual, campo, valor)) {
            if (camposAtualizados->codigo != -1) {
                atual->codigo = camposAtualizados->codigo;
            }

            if (strlen(camposAtualizados->nome) > 0) {
                strcpy(atual->nome, camposAtualizados->nome);
            }

            if (camposAtualizados->telefone != -1) {
                atual->telefone = camposAtualizados->telefone;
            }

            if (strlen(camposAtualizados->dataFormatada) > 0) {
                strcpy(atual->dataFormatada, camposAtualizados->dataFormatada);
            }

            if (strlen(camposAtualizados->endereco) > 0) {
                strcpy(atual->endereco, camposAtualizados->endereco);
            }
        }
        atual = atual->prox;
    }

    return *listaDePessoas;
}



//select
//insert into - OK
//delete
//update

