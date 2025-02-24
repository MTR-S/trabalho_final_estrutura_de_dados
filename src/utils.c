//
// Created by vinicius on 14/02/25.
//

#include "../include/utils.h"
void normalizar_aspas(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '‘' || str[i] == '’') {
            str[i] = '\'';
        }
    }
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função para remover espaços em branco do início e do final de uma string
void trim(char *str) {
    if (str == NULL) return; // Verifica se a string é válida

    // Remove espaços do início
    char *inicio = str;
    while (isspace((unsigned char)*inicio)) {
        inicio++;
    }

    // Remove espaços do final
    char *fim = str + strlen(str) - 1;
    while (fim > inicio && isspace((unsigned char)*fim)) {
        fim--;
    }

    // Adiciona o terminador nulo no novo final
    *(fim + 1) = '\0';

    // Move a string para o início, se necessário
    if (inicio != str) {
        memmove(str, inicio, fim - inicio + 2); // +2 para incluir o '\0'
    }
}
void remover_aspas(char *str) {
    int len = strlen(str);

    if (len > 1 && str[0] == '\'' && str[len - 1] == '\'') {
        // Move todos os caracteres uma posição para trás, sobrescrevendo a primeira aspas
        memmove(str, str + 1, len - 2);
        // Adiciona o caractere nulo no final, removendo a última aspas
        str[len - 2] = '\0';
    }
}

void remover_ponto_e_virgula(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == ';') {
        str[len - 1] = '\0';  // Substitui o ';' por um terminador de string
    }
}

