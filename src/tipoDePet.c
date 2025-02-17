#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/tipoDePet.h"
#include "../include/menu.h"

ListaDeTipoDePets * criaListaDeTiposDePet(){
    ListaDeTipoDePets * listaDeTipoDePets = (ListaDeTipoDePets *) malloc(sizeof(typeof(ListaDeTipoDePets)));
    if(listaDeTipoDePets == NULL) {
        return NULL;
    }

    listaDeTipoDePets->cabeca = NULL;
    listaDeTipoDePets->quantidade = 0;

    return listaDeTipoDePets;
}

TipoDePet * criaTipoDePet(int codigo, char * nome, int restringirCampos, ListaDeTipoDePets * listaDeTipoDePets) {
    TipoDePet * novoTipoDePet = (TipoDePet *) malloc(sizeof(typeof(TipoDePet)));
    if(novoTipoDePet == NULL) {
        return NULL;
    }

    if(restringirCampos) {
        if(codigo < 0) {
            return NULL;
        }
        if(strlen(nome) == 0) {
            return NULL;
        }
    }

    TipoDePet * atual = listaDeTipoDePets->cabeca;
    while(atual != NULL) {
        if(atual->codigo == codigo) {
            return NULL;
        }
        atual = atual->prox;
    }

    novoTipoDePet->codigo = codigo;
    strcpy(novoTipoDePet->nome, nome);

    novoTipoDePet->prox = NULL;
    novoTipoDePet->ant = NULL;

    return novoTipoDePet;
}

int comparaTipoDePet(TipoDePet *atual, enum camposDeTipoDePet campo, void *valor) {
    switch (campo) {
        case CODIGO_TIPO_DE_PET:
            return (atual->codigo == *(int *)valor);
        default:
            return (strcmp(atual->nome, (char *)valor) == 0);
    }
}
int maiorQueTipoDePet(TipoDePetNaArvoreBin * raiz, enum camposDeTipoDePet campo, TipoDePet * proximoInserido){
    switch (campo) {
        case CODIGO_TIPO_DE_PET:
            return proximoInserido->codigo > raiz->tipoDePetNaLista->codigo;
        default:
            return (strcmp(proximoInserido->nome, raiz->tipoDePetNaLista->nome) > 0);
    }
}

int menorQueTipoDePet(TipoDePetNaArvoreBin * raiz, enum camposDeTipoDePet campo, TipoDePet * proximoInserido) {
    switch (campo) {
        case CODIGO_TIPO_DE_PET:
            return proximoInserido->codigo < raiz->tipoDePetNaLista->codigo;
        default:
            return (strcmp(proximoInserido->nome, raiz->tipoDePetNaLista->nome) < 0);
    }
}

TipoDePetNaArvoreBin * insertNaArvoreDeTipoDePet(TipoDePetNaArvoreBin * raiz, TipoDePet * proximoInserido, enum camposDeTipoDePet campoOrderBy) {
    if(raiz == NULL) {
        TipoDePetNaArvoreBin * novoTipoDePetInseridoNaArvore = (TipoDePetNaArvoreBin *) malloc(sizeof(typeof(TipoDePetNaArvoreBin)));
        if(novoTipoDePetInseridoNaArvore == NULL) {
            return NULL;
        }

        novoTipoDePetInseridoNaArvore->tipoDePetNaLista = proximoInserido;
        novoTipoDePetInseridoNaArvore->direita = NULL;
        novoTipoDePetInseridoNaArvore->esquerda = NULL;

        return novoTipoDePetInseridoNaArvore;
    }

    if(menorQueTipoDePet(raiz, campoOrderBy, proximoInserido)) {
        raiz->esquerda = insertNaArvoreDeTipoDePet(raiz->esquerda, proximoInserido, campoOrderBy);
    }

    if(maiorQueTipoDePet(raiz, campoOrderBy, proximoInserido)) {
        raiz->direita = insertNaArvoreDeTipoDePet(raiz->direita, proximoInserido, campoOrderBy);
    }

    return raiz;
}

TipoDePetNaArvoreBin * orderByTipoDePet(ListaDeTipoDePets * listaDePet, enum camposDeTipoDePet campoOrderBy){
    TipoDePetNaArvoreBin * raiz = (TipoDePetNaArvoreBin *) malloc(sizeof(typeof(TipoDePetNaArvoreBin)));
    if(raiz == NULL) {
        return NULL;
    }

    raiz->tipoDePetNaLista = listaDePet->cabeca;
    raiz->direita = NULL;
    raiz->esquerda = NULL;

    TipoDePet * atual = listaDePet->cabeca;

    while(atual != NULL) {
        raiz = insertNaArvoreDeTipoDePet(raiz, atual, campoOrderBy);
        atual = atual->prox;
    }

    return raiz;
}

void * inOrderTraversalArvoreTipoDePet(TipoDePetNaArvoreBin * raiz) {
    if(raiz == NULL) {
        return NULL;
    }

    inOrderTraversalArvoreTipoDePet(raiz->esquerda);

    exibirTipoDePet(*(raiz->tipoDePetNaLista));

    inOrderTraversalArvoreTipoDePet(raiz->direita);

    return raiz;
}

void selectListaTipoDePet(ListaDeTipoDePets ** listaDeTipoDePet, enum camposDeTipoDePet campo, void * valor, int orderByPresente, enum camposDeTipoDePet campoOrderBy) {
    if ((*listaDeTipoDePet)->cabeca == NULL) {
        return;
    }

    TipoDePet * atual = (*listaDeTipoDePet)->cabeca;

    if(orderByPresente) {
        TipoDePetNaArvoreBin * raiz = orderByTipoDePet(*listaDeTipoDePet, campoOrderBy);
        inOrderTraversalArvoreTipoDePet(raiz);

        return;
    }

    while (atual != NULL) {
        if (comparaTipoDePet(atual, campo, valor)) {
            exibirTipoDePet(*atual);
        }
        atual = atual->prox;
    }
}

ListaDeTipoDePets * insertIntoTipoDePet(ListaDeTipoDePets ** listaDeTipoDePet, TipoDePet * novoTipoDePet) {
    if(novoTipoDePet == NULL) {
        return NULL;
    }

    if(*listaDeTipoDePet == NULL) {
        return NULL;
    }

    if((*listaDeTipoDePet)->cabeca != NULL) {
        novoTipoDePet->prox = (*listaDeTipoDePet)->cabeca;
        (*listaDeTipoDePet)->cabeca->ant = novoTipoDePet;
    }

    (*listaDeTipoDePet)->cabeca = novoTipoDePet;
    (*listaDeTipoDePet)->quantidade++;

    return *listaDeTipoDePet;
}

ListaDeTipoDePets * deleteTipoDePet(ListaDeTipoDePets ** listaDeTipoDePets, enum camposDeTipoDePet campo, void * valor)  {
    if ((*listaDeTipoDePets)->cabeca == NULL) {
        return NULL;
    }

    TipoDePet * atual = (*listaDeTipoDePets)->cabeca;

    while (atual != NULL) {
        if (comparaTipoDePet(atual, campo, valor)) {
            if (atual->ant == NULL) {
                (*listaDeTipoDePets)->cabeca = atual->prox;
                if (atual->prox != NULL) {
                    atual->prox->ant = NULL;
                }
            } else {
                atual->ant->prox = atual->prox;
                if (atual->prox != NULL) {
                    atual->prox->ant = atual->ant;
                }
            }

            TipoDePet *temp = atual;
            atual = atual->prox;
            free(temp);
            (*listaDeTipoDePets)->quantidade--;
        } else {
            atual = atual->prox;
        }
    }

    return *listaDeTipoDePets;
}

ListaDeTipoDePets * updateTipoDePet(ListaDeTipoDePets **listaDeTipoDePets, TipoDePet * camposAtualizados, enum camposDeTipoDePet campo, void * valor){
    if((*listaDeTipoDePets)->cabeca == NULL) {
        return NULL;
    }

    TipoDePet * atual = (*listaDeTipoDePets)->cabeca;

    while (atual != NULL) {
        if (comparaTipoDePet(atual, campo, valor)) {
            if (camposAtualizados->codigo != -1) {
                atual->codigo = camposAtualizados->codigo;
            }

            if (strlen(camposAtualizados->nome) > 0) {
                strcpy(atual->nome, camposAtualizados->nome);
            }
        }
        atual = atual->prox;
    }

    return *listaDeTipoDePets;
}



