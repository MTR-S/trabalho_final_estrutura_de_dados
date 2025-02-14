//
// Created by Casa on 10/02/2025.
//

#ifndef TRABALHO_FINAL_ESTRUTURA_DE_DADOS_COMANDO_H
#define TRABALHO_FINAL_ESTRUTURA_DE_DADOS_COMANDO_H

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
void inserir_comandoSQL(Fila_comando *fila, const char* descricao);
void imprimir_fila(Fila_comando *fila);
void destruir_fila(Fila_comando *fila);
void extrair_arg_insert();
void criar_fila_tipos(Fila_comando *fila, Fila_comando **fila_pessoa,Fila_comando **fila_pet,Fila_comando **fila_tipo_pet);
void inserir_comandoC(Fila_comando *fila, const char *descricao);

#endif
//TRABALHO_FINAL_ESTRUTURA_DE_DADOS_COMANDO_H
