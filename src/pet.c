#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/menu.h"
#include "../include/pet.h"

ListaDePet * criaListaDePet() {
    ListaDePet * listaDePet = (ListaDePet *) malloc(sizeof(typeof(ListaDePet)));
    if(listaDePet == NULL) {
        return NULL;
    }

    listaDePet->cabeca = NULL;
    listaDePet->quantidade = 0;

    return listaDePet;
}

Pet * criaPet(int codigo, int codigo_pes, char * nome, int codigo_tipo, int restringirCampos) {
    Pet * novoPet = (Pet *) malloc(sizeof(typeof(Pet)));
    if(novoPet == NULL) {
        return NULL;
    }

    if(restringirCampos) {
        if(codigo < 0) {
            return NULL;
        }
        if(codigo_pes < 0) {
            return NULL;
        }
        if(strlen(nome) == 0) {
            return NULL;
        }
        if(codigo_tipo < 0) {
            return NULL;
        }
    }

    novoPet->codigo = codigo;
    strcpy(novoPet->nome, nome);
    novoPet->codigo_pes = codigo;
    novoPet->codigo_tipo = codigo;

    novoPet->prox = NULL;
    novoPet->ant = NULL;

    return novoPet;
}

int comparaPet(Pet *atual, enum camposDePet campo, void *valor){
    switch (campo) {
        case CODIGO_PET:
            return (atual->codigo == *(int *)valor);

        case CODIGO_PES_PET:
            return (atual->codigo_pes == *(int *)valor);

        case NOME_PET:
            return (strcmp(atual->nome, (char *)valor) == 0);
        default:
            return (atual->codigo_tipo == *(int *)valor);
    }
}

void selectListaDePet(ListaDePet ** listaDePet, enum camposDePet campo, void * valor){
    if ((*listaDePet)->cabeca == NULL) {
        return;
    }

    Pet * atual = (*listaDePet)->cabeca;

    while (atual != NULL) {
        if (comparaPet(atual, campo, valor)) {
            exibirPet(*atual);
        }
        atual = atual->prox;
    }
}


ListaDePet * insertIntoListaDePet(ListaDePet ** listaDePet, Pet * novoPet) {
    if(novoPet == NULL) {
        return NULL;
    }

    if(*listaDePet == NULL) {
        return NULL;
    }

    if((*listaDePet)->cabeca != NULL) {
        novoPet->prox = (*listaDePet)->cabeca;
        (*listaDePet)->cabeca->ant = novoPet;
    }

    (*listaDePet)->cabeca = novoPet;
    (*listaDePet)->quantidade++;

    return *listaDePet;
}

ListaDePet * deletePet(ListaDePet ** listaDePet, enum camposDePet campo, void * valor) {
    if ((*listaDePet)->cabeca == NULL) {
        return NULL;
    }

    Pet * atual = (*listaDePet)->cabeca;

    while (atual != NULL) {
        if (comparaPet(atual, campo, valor)) {
            if (atual->ant == NULL) {
                (*listaDePet)->cabeca = atual->prox;
                if (atual->prox != NULL) {
                    atual->prox->ant = NULL;
                }
            } else {
                atual->ant->prox = atual->prox;
                if (atual->prox != NULL) {
                    atual->prox->ant = atual->ant;
                }
            }

            Pet *temp = atual;
            atual = atual->prox;
            free(temp);
            (*listaDePet)->quantidade--;
        } else {
            atual = atual->prox;
        }
    }

    return *listaDePet;
}

ListaDePet * updatePet(ListaDePet **listaDePet, Pet * camposAtualizados, enum camposDePet campo, void * valor){
    if((*listaDePet)->cabeca == NULL) {
        return NULL;
    }

    Pet * atual = (*listaDePet)->cabeca;

    while (atual != NULL) {
        if (comparaPet(atual, campo, valor)) {
            if (camposAtualizados->codigo != -1) {
                atual->codigo = camposAtualizados->codigo;
            }

            if (strlen(camposAtualizados->nome) > 0) {
                strcpy(atual->nome, camposAtualizados->nome);
            }

            if (camposAtualizados->codigo_pes != -1) {
                atual->codigo_pes = camposAtualizados->codigo_pes;
            }

            if (camposAtualizados->codigo_tipo != -1) {
                atual->codigo_tipo = camposAtualizados->codigo_tipo;
            }
        }
        atual = atual->prox;
    }

    return *listaDePet;
}



