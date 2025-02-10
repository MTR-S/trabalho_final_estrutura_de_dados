#include <stdio.h>
#include "include/comando.h"


int main() {
    Fila_comando *fila = NULL;
    inicializar_fila(&fila);

    const char *arquivo = "/home/vinicius/CLionProjects/trabalho_final_estrutura_de_dados/data/teste.txt";
    carregar_comando_arquivo(&fila, arquivo);
    imprimir_fila(fila);

destruir_fila(fila);
    return 0;
}
