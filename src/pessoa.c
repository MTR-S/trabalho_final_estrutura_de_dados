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
    listaDePessoas->quantidade = 0;

    return listaDePessoas;
}

Pessoa * criaPessoa(int codigo, char * nome, int telefone, char * data, char * endereco, int restringirCampos) {
    Pessoa * novaPessoa = (Pessoa *) malloc(sizeof(typeof(Pessoa)));
    if(novaPessoa == NULL) {
        return NULL;
    }

    if(restringirCampos) {
        if(codigo < 0) {
            return NULL;
        }
        if(strlen(nome) == 0) {
            return NULL;
        }
        if(strlen(data) == 0) {
            return NULL;
        }
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

int maiorQuePessoa(PessoaNaArvoreBin * raiz, enum camposDePessoa campo, Pessoa * proximoInserido) {
    switch (campo) {
        case CODIGO:
            return proximoInserido->codigo > raiz->pessoaNaLista->codigo;

        case NOME:
            return (strcmp(proximoInserido->nome, raiz->pessoaNaLista->nome) > 0);

        case TELEFONE:
            return proximoInserido->telefone > raiz->pessoaNaLista->telefone;

        case DATA:
            return (strcmp(proximoInserido->dataFormatada, raiz->pessoaNaLista->dataFormatada) > 0);

        case ENDERECO:
            return (strcmp(proximoInserido->endereco, raiz->pessoaNaLista->endereco) > 0);

        default:
            return 0;
    }
}

int menorQuePessoa(PessoaNaArvoreBin * raiz, enum camposDePessoa campo, Pessoa * proximoInserido) {
    switch (campo) {
        case CODIGO:
            return proximoInserido->codigo < raiz->pessoaNaLista->codigo;

        case NOME:
            return (strcmp(proximoInserido->nome, raiz->pessoaNaLista->nome) < 0);

        case TELEFONE:
            return proximoInserido->telefone < raiz->pessoaNaLista->telefone;

        case DATA:
            return (strcmp(proximoInserido->dataFormatada, raiz->pessoaNaLista->dataFormatada) < 0);

        case ENDERECO:
            return (strcmp(proximoInserido->endereco, raiz->pessoaNaLista->endereco) < 0);

        default:
            return 0;
    }
}

PessoaNaArvoreBin * insertNaArvoreDePessoas(PessoaNaArvoreBin * raiz, Pessoa * proximoInserido, enum camposDePessoa campoOrderBy) {
    if(raiz == NULL) {
        PessoaNaArvoreBin * novaPessoaInseridaNaArvore = (PessoaNaArvoreBin *) malloc(sizeof(typeof(PessoaNaArvoreBin)));
        if(novaPessoaInseridaNaArvore == NULL) {
            return NULL;
        }

        novaPessoaInseridaNaArvore->pessoaNaLista = proximoInserido;
        novaPessoaInseridaNaArvore->direita = NULL;
        novaPessoaInseridaNaArvore->esquerda = NULL;

        return novaPessoaInseridaNaArvore;
    }

    if(menorQuePessoa(raiz, campoOrderBy, proximoInserido)) {
        raiz->esquerda = insertNaArvoreDePessoas(raiz->esquerda, proximoInserido, campoOrderBy);
    }

    if(maiorQuePessoa(raiz, campoOrderBy, proximoInserido)) {
        raiz->direita = insertNaArvoreDePessoas(raiz->direita, proximoInserido, campoOrderBy);
    }

    return raiz;
}

PessoaNaArvoreBin * orderByPessoa(ListaDePessoas * listaDePessoas, enum camposDePessoa campoOrderBy) {
    PessoaNaArvoreBin * raiz = (PessoaNaArvoreBin *) malloc(sizeof(typeof(PessoaNaArvoreBin)));
    if(raiz == NULL) {
        return NULL;
    }

    raiz->pessoaNaLista = listaDePessoas->cabeca;
    raiz->direita = NULL;
    raiz->esquerda = NULL;

    Pessoa * atual = listaDePessoas->cabeca;

    while(atual != NULL) {
        raiz = insertNaArvoreDePessoas(raiz, atual, campoOrderBy);
        atual = atual->prox;
    }

    return raiz;
}

void * inOrderTraversalArvorePessoa(PessoaNaArvoreBin * raiz) {
    if(raiz == NULL) {
        return NULL;
    }

    inOrderTraversalArvorePessoa(raiz->esquerda);

    exibirPessoa(*(raiz->pessoaNaLista));

    inOrderTraversalArvorePessoa(raiz->direita);

    return raiz;
}


void selectListaPessoas(ListaDePessoas **listaDePessoas, enum camposDePessoa campo, void *valor, int orderByPresente, enum camposDePessoa campoOrderBy) {
    if ((*listaDePessoas)->cabeca == NULL) {
        return;
    }

    Pessoa * atual = (*listaDePessoas)->cabeca;

    if(orderByPresente) {
        PessoaNaArvoreBin * raiz = orderByPessoa(*listaDePessoas, campoOrderBy);
        inOrderTraversalArvorePessoa(raiz);

        return;
    }

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
    (*listaDePessoas)->quantidade++;

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
            (*listaDePessoas)->quantidade--;
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



