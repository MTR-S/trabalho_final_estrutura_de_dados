//
// Created by Casa on 10/02/2025.
//

#include "../include/comando.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializar_fila(Fila_comando **fila) {
    *fila = (Fila_comando *)malloc(sizeof(Fila_comando));
    if (*fila == NULL) {
        printf("Erro ao alocar memória para a fila.\n");
        exit(1);
    }
    (*fila)->inicio = NULL;
    (*fila)->final = NULL;
}

void inserir_comando(Fila_comando *fila, const char* descricao) {
    if (!validar_comando(descricao)) return;

    Comando *new_cmd = (Comando*)malloc(sizeof(Comando));
    strcpy(new_cmd->descrição, descricao);
    new_cmd->proximo = NULL;

    if (fila->final) {
        fila->final->proximo = new_cmd;
    }else {
        fila->inicio = new_cmd;
    }
    fila->final = new_cmd;
}

int validar_comando(const char* comando) {

    if (strstr(comando, "insert into") == comando ||
        strstr(comando, "update") == comando ||
        strstr(comando, "delete from") == comando ||
        strstr(comando, "select") == comando ) {
        return 1;
    }
    return 0;
}

void carregar_comando_arquivo(Fila_comando **fila, const char* arquivo) {
    FILE *file = fopen(arquivo, "r");
    if (!file) {
        printf("erro ao abrir o arquivo!\n");
        perror("Detalhes do erro");
        return ;
    }
    char linha[1000];
    while (fgets(linha, sizeof(linha), file)!= NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        inserir_comando(*fila, linha);
    }
    fclose(file);

}

void imprimir_fila(Fila_comando *fila) {
    Comando *aux = fila->inicio;
    if (fila->inicio == NULL) {
        printf("A fila de comandos está vazia!\n");
        return;
    }
    while (aux) {
        printf("%s\n", aux->descrição);
        aux = aux->proximo;
    }
}
void destruir_fila(Fila_comando *fila) {
    Comando *aux = fila->inicio;
    while (aux) {
        Comando *temp = aux;
        aux = aux->proximo;
        free(temp);
    }
    fila->inicio = fila->final = NULL;
}
