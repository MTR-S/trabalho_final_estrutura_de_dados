//
// Created by Casa on 07/02/2025.
//

#ifndef TRABALHO_FINAL_ESTRUTURA_DE_DADOS_ARQUIVO_H
#define TRABALHO_FINAL_ESTRUTURA_DE_DADOS_ARQUIVO_H

#include <time.h>
#include "pessoa.h"

void *inserirNoArquivo(void *dados, size_t tamanhoElemento, int quantidade, const char *caminhoDoArquivo);
int extrairQuantidadeNoArquivo(void *lista,  size_t tamanhoElemento, const char *caminhoDoArquivo);
void * extrairDoArquivoPessoa(const char *caminhoDoArquivo) ;
void inserirNoArquivoPessoa(Pessoa *cabeca, const char *caminhoDoArquivo);
void inserirNoArquivoPet(Pet *cabeca, const char *caminhoDoArquivo);
void * extrairDoArquivoPet(const char *caminhoDoArquivo);
void inserirNoArquivoTipoDePet(TipoDePet *cabeca, const char *caminhoDoArquivo);
void * extrairDoArquivoTipoDePet(const char *caminhoDoArquivo);


#endif //TRABALHO_FINAL_ESTRUTURA_DE_DADOS_ARQUIVO_H
