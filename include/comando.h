//
// Created by vinicius on 07/02/25.
//

#ifndef COMANDO_H
#define COMANDO_H

typedef struct Comandos {
    char descrição [1000];
    struct Comandos *proximo;
}Comando;

typedef struct {
    Comando *inicio;
    Comando *final;
} Fila_comando;

void carregar_comando_arquivo(Fila_comando **fila, const char* arquivo);
int validar_comando(const char* comando);
void inicializar_fila(Fila_comando **fila);
void inserir_comando(Fila_comando *fila, const char* descricao);
void imprimir_fila(Fila_comando *fila);
void destruir_fila(Fila_comando *fila);

#endif //COMANDO_H
