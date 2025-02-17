#include <stdio.h>
#include <stdlib.h>
#include "include/pessoa.h"
#include "include/tipoDePet.h"
#include "include/pet.h"
#include "include/arquivo.h"
#include "include/comando.h"




int main() {

    Fila_comando *fila = NULL;
    inicializar_fila(&fila);
    Fila_comando *fila_pet = NULL;
    Fila_comando *fila_pessoa = NULL;
    Fila_comando *fila_tipo_pet = NULL;
    inicializar_fila(&fila_pet);
    inicializar_fila(&fila_pessoa);
    inicializar_fila(&fila_tipo_pet);

    ListaDePessoas *pessoas = criaListaDePessoas();
    pessoas->quantidade = extrairQuantidadeNoArquivo(pessoas->cabeca, sizeof(Pessoa), "data/dados_pessoa.bin");
    pessoas->cabeca = extrairDoArquivoPessoa("data/dados_pessoa.bin");

    ListaDePet *pets  = criaListaDePet();
    pets->quantidade = extrairQuantidadeNoArquivo(pets->cabeca, sizeof(Pet), "data/dados_pet.bin");
    pets->cabeca = extrairDoArquivoPet("data/dados_pet.bin");

    ListaDeTipoDePets *tipos_de_pets = criaListaDeTiposDePet();
    tipos_de_pets->quantidade = extrairQuantidadeNoArquivo(tipos_de_pets->cabeca, sizeof(TipoDePet), "data/dados_tipoDePet.bin");
    tipos_de_pets->cabeca = extrairDoArquivoTipoDePet("data/dados_tipoDePet.bin");


    const char *arquivo = "/home/vinicius/CLionProjects/trabalho_final_estrutura_de_dados/data/comandos.txt";
    carregar_comando_arquivo(&fila, arquivo);
    criar_fila_tipos(fila, &fila_pessoa,  &fila_pet, &fila_tipo_pet);

    printf("\n---------------------------------------------------------\n");
    imprimir_fila(fila_pet);
    printf("\n---------------------------------------------------------\n");
    imprimir_fila(fila_pessoa);
    printf("\n---------------------------------------------------------\n");
    imprimir_fila(fila_tipo_pet);
    printf("\n---------------------------------------------------------\n");


    executar_cmd_pessoa(&fila_pessoa, &pessoas, &pets);
    //void executar_cmd_pessoa(Fila_comando **pessoa, ListaDePessoas **pessoas, ListaDePet **pets)
    executar_cmd_tipo_pet(&fila_tipo_pet, &tipos_de_pets);
    executar_cmd_pet(&fila_pet, &pets);

    destruir_fila(fila);
    inserirNoArquivoPessoa(pessoas->cabeca, "data/dados_pessoa.bin");
    inserirNoArquivoTipoDePet(tipos_de_pets->cabeca, "data/dados_tipoDePet.bin");
    inserirNoArquivoPet(pets->cabeca, "data/dados_pet.bin");

    return 0;
}
