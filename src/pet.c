#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/menu.h"
#include "../include/pet.h"
#include "../include/pessoa.h"

ListaDePet * criaListaDePet() {
    ListaDePet * listaDePet = (ListaDePet *) malloc(sizeof(typeof(ListaDePet)));
    if(listaDePet == NULL) {
        return NULL;
    }

    listaDePet->cabeca = NULL;
    listaDePet->quantidade = 0;

    return listaDePet;
}

Pet * criaPet(int codigo, int codigo_pes, char * nome, int codigo_tipo, int restringirCampos, ListaDePet * listaDePet, ListaDePessoas * listaDePessoa, ListaDeTipoDePets * listaDeTipoDePets) {
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

    Pet * atualPet = listaDePet->cabeca;
    while(atualPet != NULL) {
        if(atualPet->codigo == codigo) {
            return NULL;
        }
        atualPet = atualPet->prox;
    }

    TipoDePet * atualTipoDePet = listaDeTipoDePets->cabeca;
    while(atualTipoDePet != NULL) {
        if(atualTipoDePet->codigo == codigo_tipo) {
            return NULL;
        }
        atualTipoDePet = atualTipoDePet->prox;
    }

    Pessoa * atualPessoa = listaDePessoa->cabeca;
    while(atualPessoa != NULL) {
        if(atualPessoa->codigo == codigo_pes) {
            return NULL;
        }
        atualPessoa = atualPessoa->prox;
    }

    novoPet->codigo = codigo;
    strcpy(novoPet->nome, nome);
    novoPet->codigo_pes = codigo_pes;
    novoPet->codigo_tipo = codigo_tipo;

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

int maiorQuePet(PetNaArvoreBin * raiz, enum camposDePet campo, Pet * proximoInserido) {
    switch (campo) {
        case CODIGO_PET:
            return proximoInserido->codigo > raiz->petNaLista->codigo;

        case CODIGO_PES_PET:
            return proximoInserido->codigo_pes > raiz->petNaLista->codigo_pes;

        case NOME_PET:
            return (strcmp(proximoInserido->nome, raiz->petNaLista->nome) > 0);
        default:
            return proximoInserido->codigo_tipo > raiz->petNaLista->codigo_tipo;
    }
}

int menorQuePet(PetNaArvoreBin * raiz, enum camposDePet campo, Pet * proximoInserido) {
    switch (campo) {
        case CODIGO_PET:
            return proximoInserido->codigo < raiz->petNaLista->codigo;

        case CODIGO_PES_PET:
            return proximoInserido->codigo_pes < raiz->petNaLista->codigo_pes;

        case NOME_PET:
            return (strcmp(proximoInserido->nome, raiz->petNaLista->nome) < 0);
        default:
            return proximoInserido->codigo_tipo < raiz->petNaLista->codigo_tipo;
    }
}

PetNaArvoreBin * insertNaArvoreDePet(PetNaArvoreBin * raiz, Pet * proximoInserido, enum camposDePet campoOrderBy) {
    if(raiz == NULL) {
        PetNaArvoreBin * novaPessoaInseridaNaArvore = (PessoaNaArvoreBin *) malloc(sizeof(typeof(PessoaNaArvoreBin)));
        if(novaPessoaInseridaNaArvore == NULL) {
            return NULL;
        }

        novaPessoaInseridaNaArvore->petNaLista = proximoInserido;
        novaPessoaInseridaNaArvore->direita = NULL;
        novaPessoaInseridaNaArvore->esquerda = NULL;

        return novaPessoaInseridaNaArvore;
    }

    if(menorQuePet(raiz, campoOrderBy, proximoInserido)) {
        raiz->esquerda = insertNaArvoreDePet(raiz->esquerda, proximoInserido, campoOrderBy);
    }

    if(maiorQuePet(raiz, campoOrderBy, proximoInserido)) {
        raiz->direita = insertNaArvoreDePet(raiz->direita, proximoInserido, campoOrderBy);
    }

    return raiz;
}

PetNaArvoreBin * orderByPet(ListaDePet * listaDePet, enum camposDePet campoOrderBy){
    PetNaArvoreBin * raiz = (PetNaArvoreBin *) malloc(sizeof(typeof(PetNaArvoreBin)));
    if(raiz == NULL) {
        return NULL;
    }

    raiz->petNaLista = listaDePet->cabeca;
    raiz->direita = NULL;
    raiz->esquerda = NULL;

    Pet * atual = listaDePet->cabeca;

    while(atual != NULL) {
        raiz = insertNaArvoreDePet(raiz, atual, campoOrderBy);
        atual = atual->prox;
    }

    return raiz;
}

void * inOrderTraversalArvorePet(PetNaArvoreBin * raiz) {
    if(raiz == NULL) {
        return NULL;
    }

    inOrderTraversalArvorePet(raiz->esquerda);

    exibirPet(*(raiz->petNaLista));

    inOrderTraversalArvorePet(raiz->direita);

    return raiz;
}

void selectListaDePet(ListaDePet ** listaDePet, enum camposDePet campo, void * valor, int orderByPresente, enum camposDePet campoOrderBy){
    if ((*listaDePet)->cabeca == NULL) {
        return;
    }

    Pet * atual = (*listaDePet)->cabeca;

    if(orderByPresente) {
        PetNaArvoreBin * raiz = orderByPet(*listaDePet, campoOrderBy);
        inOrderTraversalArvorePet(raiz);

        return;
    }

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

ListaDePet * updatePet(ListaDePet **listaDePet, Pet * camposAtualizados, enum camposDePet campo, void * valor, ListaDePessoas * listaDePessoa, ListaDeTipoDePets * listaDeTipoDePets){
    if((*listaDePet)->cabeca == NULL) {
        return NULL;
    }

    Pet * atual = (*listaDePet)->cabeca;

    while (atual != NULL) {
        if (comparaPet(atual, campo, valor)) {
            Pet * atualPet = (*listaDePet)->cabeca;
            while(atualPet != NULL) {
                if(atualPet->codigo == atual->codigo) {
                    return NULL;
                }
                atualPet = atualPet->prox;
            }

            TipoDePet * atualTipoDePet = listaDeTipoDePets->cabeca;
            while(atualTipoDePet != NULL) {
                if(atualTipoDePet->codigo == atual->codigo_tipo) {
                    return NULL;
                }
                atualTipoDePet = atualTipoDePet->prox;
            }

            Pessoa * atualPessoa = listaDePessoa->cabeca;
            while(atualPessoa != NULL) {
                if(atualPessoa->codigo == atual->codigo_pes) {
                    return NULL;
                }
                atualPessoa = atualPessoa->prox;
            }

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



