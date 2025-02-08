//
// Created by Casa on 07/02/2025.
//

#ifndef TRABALHO_FINAL_ESTRUTURA_DE_DADOS_ARQUIVO_H
#define TRABALHO_FINAL_ESTRUTURA_DE_DADOS_ARQUIVO_H

#include <time.h>

void *inserirNoArquivo(void *dados, size_t tamanhoElemento, int quantidade, const char *caminhoDoArquivo);
int extrairQuantidadeNoArquivo(void *lista,  size_t tamanhoElemento, const char *caminhoDoArquivo);
void * extrairDoArquivo(void *lista,  size_t tamanhoElemento, const char *caminhoDoArquivo, int quantidade);

#endif //TRABALHO_FINAL_ESTRUTURA_DE_DADOS_ARQUIVO_H
