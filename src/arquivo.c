//
// Created by Casa on 07/02/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "..\include\arquivo.h"

void *inserirNoArquivo(void *dados, size_t tamanhoElemento, int quantidade, const char *caminhoDoArquivo) {
    FILE * arquivoAberto = fopen(caminhoDoArquivo, "rb+");
    if(arquivoAberto == NULL) {
        arquivoAberto = fopen(caminhoDoArquivo, "wb+");
        if(arquivoAberto == NULL) {
            return NULL;
        }
    }

    fwrite(dados, tamanhoElemento, quantidade, arquivoAberto);
    fclose(arquivoAberto);

    return dados;
}

int extrairQuantidadeNoArquivo(void *lista,  size_t tamanhoElemento, const char *caminhoDoArquivo) {
    FILE * arquivoAberto = fopen(caminhoDoArquivo, "rb");
    if(arquivoAberto == NULL) {
        return 0;
    }

    fseek(arquivoAberto, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivoAberto);
    rewind(arquivoAberto);

    fclose(arquivoAberto);
    return tamanhoArquivo / tamanhoElemento;
}

void * extrairDoArquivo(void *lista,  size_t tamanhoElemento, const char *caminhoDoArquivo, int quantidade) {
    FILE * arquivoAberto = fopen(caminhoDoArquivo, "rb+");
    if(arquivoAberto == NULL) {
        return 0;
    }

    fread(lista, tamanhoElemento, quantidade, arquivoAberto);
    fclose(arquivoAberto);

    return lista;
}
