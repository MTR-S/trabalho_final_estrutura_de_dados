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
    Pessoa * novaPessoa = criaPessoa(7, "bia", 427912055, "14/01/2003", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa);
    Pessoa * novaPessoa2 = criaPessoa(2, "zion", 677912055, "12/01/2005", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa2);
    Pessoa * novaPessoa4 = criaPessoa(6, "ana", 897912055, "14/01/2002", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa4);
    Pessoa * novaPessoa5 = criaPessoa(11, "carlos", 527912055, "22/01/1998", "rua dr ratisbona", 1, listaDeNovasPessoas);
    insertIntoListaPessoas(&listaDeNovasPessoas, novaPessoa5);

    // ARQUIVO - Testando Inserir e Extrair do Arquivo Pessoa
    inserirNoArquivoPessoa(listaDeNovasPessoas->cabeca, "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\t2\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");
    ListaDePessoas * pessoasExtraidasDoArquivo = criaListaDePessoas();
    pessoasExtraidasDoArquivo->cabeca = extrairDoArquivoPessoa("C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\t2\\trabalho_final_estrutura_de_dados\\data\\dados_pessoa.bin");
    printf("ANTES DE EXTRAIR PESSOA\n");
    selectListaPessoas(&pessoasExtraidasDoArquivo, ENDERECO, "endereco", 1, NOME);
    printf("DEPOIS DE EXTRAIR PESSOA\n");

    // 2) Tipo de Pet:
    TipoDePet * novoTipoDePet = criaTipoDePet(65, "cachorro", 1, listaDeNovosTiposDePet);
    insertIntoTipoDePet(&listaDeNovosTiposDePet, novoTipoDePet);
    TipoDePet * novoTipoDePet2 = criaTipoDePet(95, "gato", 1, listaDeNovosTiposDePet);
    insertIntoTipoDePet(&listaDeNovosTiposDePet, novoTipoDePet2);
    TipoDePet * novoTipoDePet3 = criaTipoDePet(15, "peixe", 1, listaDeNovosTiposDePet);
    insertIntoTipoDePet(&listaDeNovosTiposDePet, novoTipoDePet3);
    TipoDePet * novoTipoDePe4 = criaTipoDePet(35, "zebra", 1, listaDeNovosTiposDePet);
    insertIntoTipoDePet(&listaDeNovosTiposDePet, novoTipoDePe4);
    TipoDePet * novoTipoDePe5 = criaTipoDePet(105, "ema", 1, listaDeNovosTiposDePet);
    insertIntoTipoDePet(&listaDeNovosTiposDePet, novoTipoDePe5);

    // ARQUIVO -Testando Inserir e Extrair do Arquivo Tipo de Pet
    inserirNoArquivoTipoDePet(listaDeNovosTiposDePet->cabeca, "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\t2\\trabalho_final_estrutura_de_dados\\data\\dados_tipoDePet.bin");
    ListaDeTipoDePets * tiposDePetsExtraidosDoArquivo = criaListaDeTiposDePet();
    tiposDePetsExtraidosDoArquivo->cabeca = extrairDoArquivoTipoDePet("C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\t2\\trabalho_final_estrutura_de_dados\\data\\dados_tipoDePet.bin");
    printf("ANTES DE EXTRAIR TIPO DE PET\n");
    selectListaTipoDePet(&tiposDePetsExtraidosDoArquivo, CODIGO_TIPO_DE_PET, "&codigo", 1, CODIGO_TIPO_DE_PET);
    printf("DEPOIS DE EXTRAIR TIPO DE PET\n");

    // 3) Pet:
    Pet * novoPet = criaPet(41, 7, "bilu", 65, 1, listaDeNovosPets, listaDeNovasPessoas, listaDeNovosTiposDePet);
    insertIntoListaDePet(&listaDeNovosPets, novoPet);
    Pet * novoPet2 = criaPet(10, 6, "rex", 95, 1, listaDeNovosPets, listaDeNovasPessoas, listaDeNovosTiposDePet);
    insertIntoListaDePet(&listaDeNovosPets, novoPet2);
    Pet * novoPet3 = criaPet(200, 6, "princesa", 15, 1, listaDeNovosPets, listaDeNovasPessoas, listaDeNovosTiposDePet);
    insertIntoListaDePet(&listaDeNovosPets, novoPet3);
    Pet * novoPet4 = criaPet(2, 11, "lola", 35, 1, listaDeNovosPets, listaDeNovasPessoas, listaDeNovosTiposDePet);
    insertIntoListaDePet(&listaDeNovosPets, novoPet4);

    // ARQUIVO - Testanto Inserir e Extrair do Arquivo Pet
    inserirNoArquivoPet(listaDeNovosPets->cabeca, "C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\t2\\trabalho_final_estrutura_de_dados\\data\\dados_pet.bin");
    ListaDePet * petsExtraidosDoArquivo = criaListaDePet();
    petsExtraidosDoArquivo->cabeca = extrairDoArquivoPet("C:\\Users\\Casa\\IFCE-EngenhariaComputacao-S3\\t2\\trabalho_final_estrutura_de_dados\\data\\dados_pet.bin");
    printf("ANTES DE EXTRAIR PET\n");
    selectListaDePet(&petsExtraidosDoArquivo, CODIGO_PET, "&codigo_pes", 1, CODIGO_PES_PET);
    printf("DEPOIS DE EXTRAIR PET\n");

    //--> Select Listas:
    // 1) Pessoas:
    char * endereco = "rua dr ratisbona";
    printf("\n\n** SELECT - PESSOA **\n");
    printf("--> Sem Order By - SELECT * from pessoas WHERE endereco = rua dr ratisbona:\n");
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, endereco, 0, ENDERECO);
    printf("--> Com Order By - SELECT * from pessoas order by nome:\n");
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, endereco, 1, NOME);

    // 2) Tipo De Pet:
    int codigo = 95;
    printf("\n\n** SELECT - TIPO DE PET **\n");
    printf("--> Com Order By - SELECT * from tipoDePet order by codigo:\n");
    selectListaTipoDePet(&listaDeNovosTiposDePet, CODIGO_TIPO_DE_PET, &codigo, 1, CODIGO_TIPO_DE_PET);

    // 3) Pet:
    int codigo_pes = 95;
    printf("\n\n** SELECT - PET **\n");
    printf("--> Com Order By - SELECT * from pet order by codigo_pes:\n");
    selectListaDePet(&listaDeNovosPets, CODIGO_PET, &codigo_pes, 1, CODIGO_PES_PET);

    //--> Update Listas:
    //1) Pessoas:
    printf("\n\n** UPDATE - PESSOA **\n");
    printf("--> Update pessoa set nome = carlos almeida, telefone = 22452701 where nome = carlos:\n");
    char * nome = "carlos";
    Pessoa * pessoaComCamposAtualizados = criaPessoa(-1, "carlos almeida", 22452701, "", "", 0, listaDeNovasPessoas);
    updatePessoas(&listaDeNovasPessoas, pessoaComCamposAtualizados, NOME, nome);
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, endereco, 1, NOME);

    //2) Tipo de Pet:
    printf("\n\n** UPDATE - TIPO DE PET **\n");
    printf("--> Update tipoDepet set nome = cavalo com listra where codigo = 35:\n");
    int codigo_tipo_pet = 35;

    TipoDePet * tipoDePetCamposAtualizados = criaTipoDePet(-1, "cavalo com listra", 0, listaDeNovosTiposDePet);
    updateTipoDePet(&listaDeNovosTiposDePet, tipoDePetCamposAtualizados, CODIGO_TIPO_DE_PET, &codigo_tipo_pet);
    selectListaTipoDePet(&listaDeNovosTiposDePet, CODIGO_TIPO_DE_PET, &codigo, 1, NOME_TIPO_DE_PET);

    //3) Pet:
    printf("\n\n** UPDATE - PET **\n");
    printf("--> Update pet set codigo_pes = 11 where codigo = 7:\n");
    int codigo_pet_pes = 7;
    Pet * petCamposAtualizados = criaPet(-1, 11, "", -1, 0, listaDeNovosPets, listaDeNovasPessoas, listaDeNovosTiposDePet);
    updatePet(&listaDeNovosPets, petCamposAtualizados, CODIGO_PES_PET, &codigo_pet_pes, listaDeNovasPessoas, listaDeNovosTiposDePet);
    selectListaDePet(&listaDeNovosPets, CODIGO_PES_PET, &codigo_pet_pes, 1, NOME_PET);

    //--> Delete Listas:
    // 1) Pessoas:
    printf("\n\n** DELETE - PESSOA **\n");
    printf("--> Delete from pessoa where nome = bia:\n");
    char * nome_deletado = "bia";
    deletePessoa(&listaDeNovasPessoas, NOME, nome_deletado, listaDeNovosPets);
    selectListaPessoas(&listaDeNovasPessoas, ENDERECO, endereco, 1, NOME);

    // 2) Tipo de Pet:
    printf("\n\n** DELETE - TIPO DE PET **\n");
    printf("--> Delete from tipoDePet where nome = ema:\n");
    char * nome__tipoDepet_deletado = "ema";
    deleteTipoDePet(&listaDeNovosTiposDePet, NOME_TIPO_DE_PET,nome__tipoDepet_deletado);
    selectListaTipoDePet(&listaDeNovosTiposDePet, CODIGO_TIPO_DE_PET, &codigo, 1, NOME_TIPO_DE_PET);

    // 3) Pet:
    printf("\n\n** DELETE - PET **\n");
    printf("--> Delete from pet where codigo_pes = 6:\n");
    int codigo_pes_deletado = 6;
    deletePet(&listaDeNovosPets, CODIGO_PES_PET, &codigo_pes_deletado);
    selectListaDePet(&listaDeNovosPets, CODIGO_PES_PET, &codigo_pet_pes, 1, NOME_PET);
    //--------- ESTRUTURAS DE DADOS FUNCIONAIS ------------

    return 0;
}
