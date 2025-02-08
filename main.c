#include <stdio.h>
#include <stdlib.h>

#include "include/pessoa.h"
#include "include/arquivo.h"

int main() {
    struct tm dataDeNascimento;
    dataDeNascimento.tm_mday = 14;
    dataDeNascimento.tm_year = 2005;
    dataDeNascimento.tm_mon = 1;

    //inserindo no arquivo
    ListaDePessoas * listaDeNovasPessoas = criaListaDePessoas();

    Pessoa * novaPessoa = criaPessoa(1, "matheus", 1, dataDeNascimento, "rua dr ratisbona");
    inserePessoaNaListaDeNovos(&listaDeNovasPessoas, novaPessoa);
    Pessoa * novaPessoa2 = criaPessoa(2, "matheus", 2, dataDeNascimento, "rua dr ratisbona");
    inserePessoaNaListaDeNovos(&listaDeNovasPessoas, novaPessoa2);
    Pessoa * novaPessoa3 = criaPessoa(3, "matheus", 3, dataDeNascimento, "rua dr ratisbona");

    inserePessoaNaListaDeNovos(&listaDeNovasPessoas, novaPessoa3);

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
