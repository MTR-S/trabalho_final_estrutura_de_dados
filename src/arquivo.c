//
// Created by Casa on 07/02/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/arquivo.h"

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

void inserirNoArquivoPessoa(Pessoa *cabeca, const char *caminhoDoArquivo) {
    FILE * arquivoAberto = fopen(caminhoDoArquivo, "rb+");
    if(arquivoAberto == NULL) {
        arquivoAberto = fopen(caminhoDoArquivo, "wb+");
        if(arquivoAberto == NULL) {
            return;
        }
    }

    Pessoa *atual = cabeca;
    while (atual != NULL) {
        fwrite(&atual->codigo, sizeof(int), 1, arquivoAberto);
        fwrite(atual->nome, sizeof(char), 50, arquivoAberto);
        fwrite(&atual->telefone, sizeof(int), 1, arquivoAberto);
        fwrite(atual->dataFormatada, sizeof(char), 11, arquivoAberto);
        fwrite(atual->endereco, sizeof(char), 50, arquivoAberto);

        atual = atual->prox;
    }

    fclose(arquivoAberto);
}

void * extrairDoArquivoPessoa(const char *caminhoDoArquivo) {
    FILE * arquivoAberto = fopen(caminhoDoArquivo, "rb");
    if(arquivoAberto == NULL) {
        return NULL;
    }

    Pessoa *cabeca = NULL;
    Pessoa *atual = NULL;

    while (1) {
        Pessoa *novaPessoa = (Pessoa *)malloc(sizeof(Pessoa));
        if (fread(&novaPessoa->codigo, sizeof(int), 1, arquivoAberto) != 1) {
            free(novaPessoa);
            break;
        }
        fread(novaPessoa->nome, sizeof(char), 50, arquivoAberto);
        fread(&novaPessoa->telefone, sizeof(int), 1, arquivoAberto);
        fread(novaPessoa->dataFormatada, sizeof(char), 11, arquivoAberto);
        fread(novaPessoa->endereco, sizeof(char), 50, arquivoAberto);

        novaPessoa->prox = NULL;
        novaPessoa->ant = atual;

        if (atual != NULL) {
            atual->prox = novaPessoa;
        } else {
            cabeca = novaPessoa;
        }

        atual = novaPessoa;
    }

    fclose(arquivoAberto);
    return cabeca;
}

void inserirNoArquivoPet(Pet *cabeca, const char *caminhoDoArquivo) {
    FILE * arquivoAberto = fopen(caminhoDoArquivo, "rb+");
    if(arquivoAberto == NULL) {
        arquivoAberto = fopen(caminhoDoArquivo, "wb+");
        if(arquivoAberto == NULL) {
            return;
        }
    }

    Pet *atual = cabeca;
    while (atual != NULL) {
        fwrite(&atual->codigo, sizeof(int), 1, arquivoAberto);
        fwrite(&atual->codigo_pes, sizeof(int), 1, arquivoAberto);
        fwrite(atual->nome, sizeof(char), 50, arquivoAberto);
        fwrite(&atual->codigo_tipo, sizeof(int), 1, arquivoAberto);

        atual = atual->prox;
    }

    fclose(arquivoAberto);
}

void * extrairDoArquivoPet(const char *caminhoDoArquivo) {
    FILE * arquivoAberto = fopen(caminhoDoArquivo, "rb");
    if(arquivoAberto == NULL) {
        return NULL;
    }
    Pet *cabeca = NULL;
    Pet *atual = NULL;

    while (1) {
        Pet *novoPet = (Pet *)malloc(sizeof(Pet));
        if (fread(&novoPet->codigo, sizeof(int), 1, arquivoAberto) != 1) {
            free(novoPet);
            break;
        }

        fread(&novoPet->codigo_pes, sizeof(int), 1, arquivoAberto);
        fread(novoPet->nome, sizeof(char), 50, arquivoAberto);
        fread(&novoPet->codigo_tipo, sizeof(int), 1, arquivoAberto);

        novoPet->prox = NULL;
        novoPet->ant = atual;

        if (atual != NULL) {
            atual->prox = novoPet;
        } else {
            cabeca = novoPet;
        }

        atual = novoPet;
    }

    fclose(arquivoAberto);
    return cabeca;
}

void inserirNoArquivoTipoDePet(TipoDePet *cabeca, const char *caminhoDoArquivo) {
    FILE * arquivoAberto = fopen(caminhoDoArquivo, "rb+");
    if(arquivoAberto == NULL) {
        arquivoAberto = fopen(caminhoDoArquivo, "wb+");
        if(arquivoAberto == NULL) {
            return;
        }
    }

    TipoDePet *atual = cabeca;
    while (atual != NULL) {
        fwrite(&atual->codigo, sizeof(int), 1, arquivoAberto);
        fwrite(atual->nome, sizeof(char), 50, arquivoAberto);

        atual = atual->prox;
    }

    fclose(arquivoAberto);
}

void * extrairDoArquivoTipoDePet(const char *caminhoDoArquivo) {
    FILE * arquivoAberto = fopen(caminhoDoArquivo, "rb");
    if(arquivoAberto == NULL) {
        return NULL;
    }

    TipoDePet *cabeca = NULL;
    TipoDePet *atual = NULL;

    while (1) {
        TipoDePet *novoTipoDePet = (TipoDePet *)malloc(sizeof(TipoDePet));
        if (fread(&novoTipoDePet->codigo, sizeof(int), 1, arquivoAberto) != 1) {
            free(novoTipoDePet);
            break;
        }

        fread(novoTipoDePet->nome, sizeof(char), 50, arquivoAberto);

        novoTipoDePet->prox = NULL;
        novoTipoDePet->ant = atual;

        if (atual != NULL) {
            atual->prox = novoTipoDePet;
        } else {
            cabeca = novoTipoDePet;
        }

        atual = novoTipoDePet;
    }

    fclose(arquivoAberto);
    return cabeca;
}