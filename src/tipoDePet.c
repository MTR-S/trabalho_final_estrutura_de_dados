#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "..\include\tipoDePet.h"
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

TipoDePet * criaTipoDePet(int codigo, char * nome) {
    TipoDePet * novoTipoDePet = (TipoDePet *) malloc(sizeof(typeof(TipoDePet)));
    if(novoTipoDePet == NULL) {
        return NULL;
    }

    if(codigo < 0) {
        return NULL;
    }
    if(strlen(nome) == 0) {
        return NULL;
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
void selectListaTipoDePet(ListaDeTipoDePets ** listaDeTipoDePets, enum camposDeTipoDePet campo, void * valor) {
    if ((*listaDeTipoDePets)->cabeca == NULL) {
        return;
    }

    TipoDePet * atual = (*listaDeTipoDePets)->cabeca;

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



