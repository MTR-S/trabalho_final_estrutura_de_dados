//
// Created by Casa on 13/02/2025.
//

#ifndef TRABALHO_FINAL_ESTRUTURA_DE_DADOS_TIPODEPET_H
#define TRABALHO_FINAL_ESTRUTURA_DE_DADOS_TIPODEPET_H

#include <time.h>

typedef struct tipoDePet {
    int codigo;
    char nome[50];
    struct tipoDePet * prox;
    struct tipoDePet * ant;
}TipoDePet;

typedef struct listaDeTipoDePets {
    int quantidade;
    struct tipoDePet * cabeca;
}ListaDeTipoDePets;

enum camposDeTipoDePet {
    CODIGO_TIPO_DE_PET,
    NOME_TIPO_DE_PET
};

typedef int (*ComparacaoDosCamposTiposDePet)(TipoDePet *, void *);
int comparaTipoDePet(TipoDePet *atual, enum camposDeTipoDePet campo, void *valor);

ListaDeTipoDePets * criaListaDeTiposDePet();
TipoDePet * criaTipoDePet(int codigo, char * nome);

void selectListaTipoDePet(ListaDeTipoDePets ** listaDeTipoDePets, enum camposDeTipoDePet campo, void * valor);
ListaDeTipoDePets * insertIntoTipoDePet(ListaDeTipoDePets ** listaDeTipoDePet, TipoDePet * novoTipoDePet);
ListaDeTipoDePets * deleteTipoDePet(ListaDeTipoDePets ** listaDeTipoDePets, enum camposDeTipoDePet campo, void * valor) ;
ListaDeTipoDePets * updateTipoDePet(ListaDeTipoDePets **listaDeTipoDePets, TipoDePet * camposAtualizados, enum camposDeTipoDePet campo, void * valor);


#endif //TRABALHO_FINAL_ESTRUTURA_DE_DADOS_TIPODEPET_H
