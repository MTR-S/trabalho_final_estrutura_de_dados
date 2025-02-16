//
// Created by Casa on 15/02/2025.
//

#ifndef TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PET_H
#define TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PET_H
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

enum camposDePet {
    CODIGO_PET,
    CODIGO_PES_PET,
    NOME_PET,
    CODIGO_TIPO_PET,
};

int comparaPet(Pet *atual, enum camposDePet campo, void *valor);

ListaDePet * criaListaDePet();
Pet * criaPet(int codigo, int codigo_pes, char * nome, int codigo_tipo, int restringirCampos);

void selectListaDePet(ListaDePet ** listaDePet, enum camposDePet campo, void * valor);
ListaDePet * insertIntoListaDePet(ListaDePet ** listaDePet, Pet * novoPet);
ListaDePet * deletePet(ListaDePet ** listaDePet, enum camposDePet campo, void * valor) ;
ListaDePet * updatePet(ListaDePet **listaDePet, Pet * camposAtualizados, enum camposDePet campo, void * valor);

#endif //TRABALHO_FINAL_ESTRUTURA_DE_DADOS_PET_H
