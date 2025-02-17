#include <stdio.h>
#include <stdlib.h>
#include "include/pessoa.h"
#include "include/tipoDePet.h"
#include "include/pet.h"
#include "include/arquivo.h"
#include "include/comando.h"




int main() {
    /*
    //----------------- FLOW DO PROGRAMA ----------------
    Fila_comando *fila = NULL;
    inicializar_fila(&fila);
    Fila_comando *fila_pet = NULL;
    Fila_comando *fila_pessoa = NULL;
    Fila_comando *fila_tipo_pet = NULL;
    inicializar_fila(&fila_pet);
    inicializar_fila(&fila_pessoa);
    inicializar_fila(&fila_tipo_pet);
    ListaDePessoas *pessoas = criaListaDePessoas();
    pessoas->quantidade = extrairQuantidadeNoArquivo(pessoas->cabeca, sizeof(Pessoa), "/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/dados_pessoa.bin");
    pessoas->cabeca = extrairDoArquivoPessoa("/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/dados_pessoa.bin");

    ListaDePet *pets  = criaListaDePet();
    pets->quantidade = extrairQuantidadeNoArquivo(pets->cabeca, sizeof(Pet), "/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/dados_pet.bin");
    pets->cabeca = extrairDoArquivoPet("/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/dados_pet.bin");

    ListaDeTipoDePets *tipos_de_pets = criaListaDeTiposDePet();
    tipos_de_pets->quantidade = extrairQuantidadeNoArquivo(tipos_de_pets->cabeca, sizeof(TipoDePet), "/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/dados_tipoDePet.bin");
    tipos_de_pets->cabeca = extrairDoArquivoTipoDePet("/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/dados_tipoDePet.bin");


    const char *arquivo = "/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/comandos.txt";
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
    executar_cmd_pet(&fila_pet, &pets, &pessoas, &tipos_de_pets);

    destruir_fila(fila);
    inserirNoArquivoPessoa(pessoas->cabeca, "/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/dados_pessoa.bin");
    inserirNoArquivoTipoDePet(tipos_de_pets->cabeca, "/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/dados_tipoDePet.bin");
    inserirNoArquivoPet(pets->cabeca, "/home/matheus/Projects/trabalho_final/trabalho_final_estrutura_de_dados/data/dados_pet.bin");
    //----------------- FLOW DO PROGRAMA ----------------
    */

    //--------- ESTRUTURAS DE DADOS FUNCIONAIS ------------
    // Criação das listas:
    ListaDePessoas * listaDeNovasPessoas = criaListaDePessoas();
    ListaDeTipoDePets * listaDeNovosTiposDePet = criaListaDeTiposDePet();
    ListaDePet * listaDeNovosPets = criaListaDePet();

    //--> Insert Into Listas:
    // 1) Pessoas:
    Pessoa * novaPessoa = criaPessoa(7, "bia", 2, "14/01/2003", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa);
    Pessoa * novaPessoa2 = criaPessoa(2, "zion", 2, "12/01/2005", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa2);
    Pessoa * novaPessoa4 = criaPessoa(6, "ana", 2, "14/01/2002", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa4);
    Pessoa * novaPessoa5 = criaPessoa(11, "carlos", 2, "22/01/1998", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa5);
    // 2) Tipo de Pet:
    TipoDePet * novoTipoDePet = criaTipoDePet();
    // 3) Pet:
    /*
    char * a = "rua dr ratisbona"; int codigo = 5;

    printf("--> Antes de excluir:\n");
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, a, 0, CODIGO);

    inserirNoArquivo(listaDeNovasPessoas->cabeca, sizeof(Pessoa), listaDeNovasPessoas->quantidade, "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");

    printf("--> Depois de excluir:\n");
    deletePessoa(&listaDeNovasPessoas, CODIGO, &codigo, );
    Pessoa *camposAtualizados = criaPessoa(-1, "matheus de sousa", 997912055, "", "", 0, listaDeNovasPessoas);
    int valor = 1;
    updatePessoas(&listaDeNovasPessoas, camposAtualizados, CODIGO, &valor);
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, a, 0, CODIGO);
    printf("Agora utilizando o OrderBy:\n");
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, a, 1, DATA);
    //--------- ESTRUTURAS DE DADOS FUNCIONAIS ------------
    */
    return 0;
}
