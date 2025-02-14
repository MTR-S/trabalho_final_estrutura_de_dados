#include <stdio.h>
#include <stdlib.h>

#include "include/pessoa.h"
#include "include/arquivo.h"
#include "include/comando.h"

/*
    Quando coletar os parametros da funcao SQL (Funções INSERT INTO e UPDATE)
    Verificar quais os campos presentes,
    Criar uma struct com os campos presentes com os valores passados
    Os campos que nao foram passados valores vao ser NULL
    Passar para as funções de struct a struct criada
 */


int main() {
    /*
    Fila_comando *fila = NULL;
    inicializar_fila(&fila);

    const char *arquivo = "./data/comandos.txt";
    carregar_comando_arquivo(&fila, arquivo);
    imprimir_fila(fila);

    destruir_fila(fila);


    //inserindo no arquivo
    ListaDePessoas * listaDeNovasPessoas = criaListaDePessoas();

    Pessoa * novaPessoa = criaPessoa(1, "matheus", 2, "14/01/2005", "rua dr ratisbona");
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa);
    Pessoa * novaPessoa2 = criaPessoa(2, "matheus", 2, "14/01/2005", "rua dr ratisbona");
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa2);
    Pessoa * novaPessoa4 = criaPessoa(4, "matheus", 2, "14/01/2005", "rua dr ratisbona");
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa4);
    Pessoa * novaPessoa5 = criaPessoa(5, "matheus", 2, "14/01/2005", "rua dr ratisbona");
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa5);

    char * a = "rua dr ratisbona"; int codigo = 5;
    printf("Antes de excluir:\n");
    selectListaPessoas(&listaDeNovasPessoas, NOME, a);
    inserirNoArquivo(listaDeNovasPessoas->cabeca, sizeof(Pessoa), listaDeNovasPessoas->quantidadeTotalDePessoas, "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");
    printf("Depois de excluir:\n");
    deletePessoa(&listaDeNovasPessoas, CODIGO, &codigo);
    Pessoa *camposAtualizados = criaPessoa(-1, "matheus de sousa", 997912055, "", "");
    int valor = 1;
    updatePessoas(&listaDeNovasPessoas, camposAtualizados, CODIGO, &valor);
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, a);
    // fim

    // extraindo do arquivo
    ListaDePessoas * listaDeNovasPessoas2 = criaListaDePessoas();

    listaDeNovasPessoas2->quantidadeTotalDePessoas = extrairQuantidadeNoArquivo(listaDeNovasPessoas2->cabeca, sizeof(Pessoa), "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");

    listaDeNovasPessoas2->cabeca = (Pessoa *) malloc(sizeof(Pessoa) * listaDeNovasPessoas2->quantidadeTotalDePessoas);
    listaDeNovasPessoas2->cabeca = extrairDoArquivo(listaDeNovasPessoas2->cabeca, sizeof(Pessoa), "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin", listaDeNovasPessoas2->quantidadeTotalDePessoas);
    //fim
*/
    Fila_comando *fila = NULL;
    inicializar_fila(&fila);

    const char *arquivo = "/home/vinicius/CLionProjects/trabalho_final_estrutura_de_dados/data/comandos.txt";
    carregar_comando_arquivo(&fila, arquivo);
    imprimir_fila(fila);
    extrair_arg_insert();

    destruir_fila(fila);
    return 0;
}
