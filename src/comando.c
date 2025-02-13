//
// Created by Casa on 10/02/2025.
//

#include "../include/comando.h"
#include "../include/regex.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "regex.h"

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
    char comando_lower[255];
    strncpy(comando_lower, comando, sizeof(comando_lower) - 1);
    comando_lower[sizeof(comando_lower) - 1] = '\0';

    for (int i = 0; comando_lower[i] != '\0'; ++i) {
        comando_lower[i] = (char)tolower(comando_lower[i]);
    }

    if (strstr(comando_lower, "insert into") == comando_lower) {
        const char *pattern = "^insert into[[:space:]]+(tipo_pet|pet|pessoa)[[:space:]]*\\([^)]*\\)[[:space:]]+values[[:space:]]*\\([^)]*\\)[[:space:]]*;?$";
        return (validar_sintaxe(comando_lower, pattern));
    }
    if (strstr(comando_lower, "update") == comando_lower){
        const char *pattern =  "^[[:space:]]*update[[:space:]]+(tipo_pet|pet|pessoa)[[:space:]]+set[[:space:]]+"
    "(([[:space:]]*(nome|codigo|fone|endereco|dt|codigo_pes|codigo_tipo)[[:space:]]*="
    "[[:space:]]*('[^']*'|[0-9]+)[[:space:]]*,?)+)[[:space:]]+"
    "where[[:space:]]+codigo[[:space:]]*=[[:space:]]*[0-9]+[[:space:]]*;$";
        return (validar_sintaxe(comando_lower, pattern));
    }
    if ( strstr(comando_lower, "delete from") == comando_lower) {
        const char *pattern = "^delete from[[:space:]]+(tipo_pet|pet|pessoa)[[:space:]]+where[[:space:]]+(nome|codigo|fone|endereco|dt|codigo_pes|codigo_tipo)[[:space:]]*=[[:space:]]*('[^']*'|[0-9]+)[[:space:]]*;$";
        return (validar_sintaxe(comando_lower, pattern));

    }
    if ( strstr(comando_lower, "select * from") == comando_lower ) {
        const char *pattern = "^select[[:space:]]+\\*[[:space:]]+from[[:space:]]+(pet|tipo_pet|pessoa)([[:space:]]+where[[:space:]]+(nome|codigo|fone|endereco|dt|codigo_pes|codigo_tipo)[[:space:]]*=[[:space:]]*('[^']*'|[0-9]+))?([[:space:]]+order[[:space:]]+by[[:space:]]+(nome|codigo)[[:space:]]*(asc|desc)?)?[[:space:]]*;$";
        return (validar_sintaxe(comando_lower, pattern));
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
