#include <stdio.h>
#include <stdlib.h>

#include "include/pessoa.h"
#include "include/arquivo.h"
#include "include/comando.h"

int main() {
    Fila_comando *fila = NULL;
    inicializar_fila(&fila);

    const char *arquivo = "/home/vinicius/CLionProjects/trabalho_final_estrutura_de_dados/data/teste.txt";
    carregar_comando_arquivo(&fila, arquivo);
    imprimir_fila(fila);

    destruir_fila(fila);
    struct tm dataDeNascimento;
    dataDeNascimento.tm_mday = 14;
    dataDeNascimento.tm_year = 2005;
    dataDeNascimento.tm_mon = 1;

    //inserindo no arquivo
    ListaDePessoas * listaDeNovasPessoas = criaListaDePessoas();

    Pessoa * novaPessoa = criaPessoa(1, "matheus", 2, dataDeNascimento, "rua dr ratisbona");
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa);
    Pessoa * novaPessoa2 = criaPessoa(2, "matheus", 2, dataDeNascimento, "rua dr ratisbona");
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa2);
    Pessoa * novaPessoa4 = criaPessoa(4, "matheus", 2, dataDeNascimento, "rua dr ratisbona");
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa4);

    char * a = "matheus";
    selectListaPessoas(&listaDeNovasPessoas, NOME, a);
    inserirNoArquivo(listaDeNovasPessoas->cabeca, sizeof(Pessoa), listaDeNovasPessoas->quantidadeTotalDePessoas, "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");
    // fim

    // extraindo do arquivo
    ListaDePessoas * listaDeNovasPessoas2 = criaListaDePessoas();

    listaDeNovasPessoas2->quantidadeTotalDePessoas = extrairQuantidadeNoArquivo(listaDeNovasPessoas2->cabeca, sizeof(Pessoa), "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");

    listaDeNovasPessoas2->cabeca = (Pessoa *) malloc(sizeof(Pessoa) * listaDeNovasPessoas2->quantidadeTotalDePessoas);
    listaDeNovasPessoas2->cabeca = extrairDoArquivo(listaDeNovasPessoas2->cabeca, sizeof(Pessoa), "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin", listaDeNovasPessoas2->quantidadeTotalDePessoas);
    //fim

    return 0;
}
