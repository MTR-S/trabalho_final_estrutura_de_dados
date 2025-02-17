//
// Created by Casa on 15/02/2025.
//


#ifndef TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PET_H
#define TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PET_H

#include "pessoa.h"
#include "tipoDePet.h"

typedef struct listaDePessoas ListaDePessoas;

typedef struct pet {
    int codigo;
    int codigo_pes;
    char nome[50];
    int codigo_tipo;
    struct pet * prox;
    struct pet * ant;
}Pet;

typedef struct listaDePet {
    int quantidade;
    struct pet * cabeca;
}ListaDePet;

typedef struct petNaArvoreBin {
    struct pet * petNaLista;
    struct petNaArvoreBin * direita;
    struct petNaArvoreBin * esquerda;
}PetNaArvoreBin;

enum camposDePet {
    CODIGO_PET,
    CODIGO_PES_PET,
    NOME_PET,
    CODIGO_TIPO_PET,
};

int comparaPet(Pet *atual, enum camposDePet campo, void *valor);
int maiorQuePet(PetNaArvoreBin * raiz, enum camposDePet campo, Pet * proximoInserido);
int menorQuePet(PetNaArvoreBin * raiz, enum camposDePet campo, Pet * proximoInserido);

PetNaArvoreBin * insertNaArvoreDePet(PetNaArvoreBin * raiz, Pet * proximoInserido, enum camposDePet campoOrderBy);
PetNaArvoreBin * orderByPet(ListaDePet * listaDePet, enum camposDePet campoOrderBy);
void * inOrderTraversalArvorePet(PetNaArvoreBin * raiz);

ListaDePet * criaListaDePet();
Pet * criaPet(int codigo, int codigo_pes, char * nome, int codigo_tipo, int restringirCampos, ListaDePet * listaDePet, ListaDePessoas * listaDePessoa, ListaDeTipoDePets * listaDeTipoDePets);

void selectListaDePet(ListaDePet ** listaDePet, enum camposDePet campo, void * valor, int orderByPresente, enum camposDePet campoOrderBy);
ListaDePet * insertIntoListaDePet(ListaDePet ** listaDePet, Pet * novoPet);
ListaDePet * deletePet(ListaDePet ** listaDePet, enum camposDePet campo, void * valor) ;
ListaDePet * updatePet(ListaDePet **listaDePet, Pet * camposAtualizados, enum camposDePet campo, void * valor, ListaDePessoas * listaDePessoa, ListaDeTipoDePets * listaDeTipoDePets);

#endif //TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PET_H
