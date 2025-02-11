//
// Created by Casa on 09/02/2025.
//

#include <stdio.h>

#include "../include/menu.h"
#include "../include/pessoa.h"

void exibirPessoa(Pessoa pessoa) {
    printf("---\n");
    printf("Codigo: %d\n", pessoa.codigo);
    printf("Nome: %s\n", pessoa.nome);
    printf("Telefone: %d\n", pessoa.telefone);
    printf("Data Formatada: %s\n", pessoa.dataFormatada);
    printf("Endereco: %s\n", pessoa.endereco);
    printf("---\n");
}