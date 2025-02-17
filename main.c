#include <stdio.h>
#include <stdlib.h>

#include "include/pessoa.h"
#include "include/tipoDePet.h"
#include "include/pet.h"
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
/*
    ListaDePessoas * listaDeNovasPessoas = criaListaDePessoas();

    Pessoa * novaPessoa = criaPessoa(7, "bia", 2, "14/01/2003", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa);
    Pessoa * novaPessoa2 = criaPessoa(2, "zion", 2, "12/01/2005", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa2);
    Pessoa * novaPessoa4 = criaPessoa(6, "ana", 2, "14/01/2002", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa4);
    Pessoa * novaPessoa5 = criaPessoa(11, "carlos", 2, "22/01/1998", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa5);

    char * a = "rua dr ratisbona"; int codigo = 5;
    //printf("Antes de excluir:\n");
    //selectListaPessoas(&listaDeNovasPessoas, ENDERECO, a);
    inserirNoArquivo(listaDeNovasPessoas->cabeca, sizeof(Pessoa), listaDeNovasPessoas->quantidade, "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");
    //printf("Depois de excluir:\n");
    //deletePessoa(&listaDeNovasPessoas, CODIGO, &codigo);
    Pessoa *camposAtualizados = criaPessoa(-1, "matheus de sousa", 997912055, "", "", 0, listaDeNovasPessoas);
    int valor = 1;
    updatePessoas(&listaDeNovasPessoas, camposAtualizados, CODIGO, &valor);
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, a, 0, CODIGO);
    printf("Agora utilizando o OrderBy:\n");
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, a, 1, DATA);
*/


    char * end = "rua dr ratisbona";
   ListaDePessoas * listaDeNovasPessoas = criaListaDePessoas();

    Pessoa * novaPessoa = criaPessoa(100, "bia", 2, "14/01/2003", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa);
    Pessoa * novaPessoa1 = criaPessoa(80, "bia", 2, "14/01/2003", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa1);

    inserirNoArquivoPessoa(listaDeNovasPessoas->cabeca, "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");

    // extraindo do arquivo
    ListaDePessoas * listaDeNovasPessoas2 = criaListaDePessoas();
    listaDeNovasPessoas2->quantidade = extrairQuantidadeNoArquivo(listaDeNovasPessoas2->cabeca, sizeof(Pessoa), "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");
    listaDeNovasPessoas2->cabeca = extrairDoArquivoPessoa("C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");

    selectListaPessoas(&listaDeNovasPessoas2, ENDERECO, end, 0, DATA);

    //fim




*/
    Fila_comando *fila = NULL;
    inicializar_fila(&fila);
    Fila_comando *fila_pet = NULL;
    Fila_comando *fila_pessoa = NULL;
    Fila_comando *fila_tipo_pet = NULL;
    inicializar_fila(&fila_pet);
    inicializar_fila(&fila_pessoa);
    inicializar_fila(&fila_tipo_pet);

    const char *arquivo = "/home/vinicius/CLionProjects/trabalho_final_estrutura_de_dados/data/comandos.txt";
    carregar_comando_arquivo(&fila, arquivo);
 //   imprimir_fila(fila);
    criar_fila_tipos(fila, &fila_pessoa,  &fila_pet, &fila_tipo_pet);
    printf("\n---------------------------------------------------------\n");
    imprimir_fila(fila_pet);
    printf("\n---------------------------------------------------------\n");
    imprimir_fila(fila_pessoa);
    printf("\n---------------------------------------------------------\n");
    imprimir_fila(fila_tipo_pet);
    destruir_fila(fila);

    return 0;
}
