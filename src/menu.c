//
// Created by Casa on 09/02/2025.
//

#include <stdio.h>

#include "../include/menu.h"
#include "../include/pet.h"

void exibirPessoa(Pessoa pessoa) {
    printf("---\n");
    printf("Codigo: %d\n", pessoa.codigo);
    printf("Nome: %s\n", pessoa.nome);
    printf("Telefone: %d\n", pessoa.telefone);
    printf("Data Formatada: %s\n", pessoa.dataFormatada);
    printf("Endereco: %s\n", pessoa.endereco);
    printf("---\n");
}

void exibirTipoDePet(TipoDePet tipoDePet) {
    printf("---\n");
    printf("Codigo: %d\n", tipoDePet.codigo);
    printf("Nome: %s\n", tipoDePet.nome);
    printf("---\n");
};

void exibirPet(Pet pet) {
    printf("---\n");
    printf("Codigo: %d\n", pet.codigo);
    printf("Codigo da Pessoa: %d\n", pet.codigo_pes);
    printf("Nome do Pet: %s\n", pet.nome);
    printf("Codigo do Tipo de Pet: %d\n", pet.codigo_tipo);
    printf("---\n");
};