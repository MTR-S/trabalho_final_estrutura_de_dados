//
// Created by Casa on 10/02/2025.
//

#include "../include/comando.h"
#include "../include/myregex.h"
#include "../include/utils.h"
#include "../include/pessoa.h"
#include "../include/pet.h"
#include "../include/tipoDePet.h"


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../include/myregex.h"

void inicializar_fila(Fila_comando **fila) {
    *fila = (Fila_comando *)malloc(sizeof(Fila_comando));
    if (*fila == NULL) {
        printf("Erro ao alocar memória para a fila.\n");
        exit(1);
    }
    (*fila)->inicio = NULL;
    (*fila)->final = NULL;
}

void inserir_comandoSQL(Fila_comando *fila, const char* descricao) {
    if (!validar_comando(descricao)) return;

    Comando *new_cmd = (Comando*)malloc(sizeof(Comando));
    strcpy(new_cmd->descrição, descricao);
    new_cmd->proximo = NULL;

    if (fila->final) {
        fila->final->proximo = new_cmd;
    }else {
        fila->inicio = new_cmd;
    }
    fila->final = new_cmd;
}

void inserir_comandoC(Fila_comando **fila, const char *descricao) {
    Comando *new_cmd = (Comando*)malloc(sizeof(Comando));
    strcpy(new_cmd->descrição, descricao);
    new_cmd->proximo = NULL;

    if ((*fila)->final) {
        (*fila)->final->proximo = new_cmd;
    }else {
        (*fila)->inicio = new_cmd;
    }
    (*fila)->final = new_cmd;
}


int validar_comando(const char* comando) {
    char comando_lower[255];
    strncpy(comando_lower, comando, sizeof(comando_lower) - 1);
    comando_lower[sizeof(comando_lower) - 1] = '\0';

    for (int i = 0; comando_lower[i] != '\0'; ++i) {
        comando_lower[i] = (char)tolower(comando_lower[i]);
    }

    if (strstr(comando_lower, "insert into") == comando_lower) {
        const char *pattern = "^insert into[[:space:]]+(tipo_pet|pet|pessoa)[[:space:]]*\\([^)]*\\)[[:space:]]+values[[:space:]]*\\([^)]*\\)[[:space:]]*;?$";
        return (validar_sintaxe(comando_lower, pattern));
    }
    if (strstr(comando_lower, "update") == comando_lower){
        const char *pattern =  "^[[:space:]]*update[[:space:]]+(tipo_pet|pet|pessoa)[[:space:]]+set[[:space:]]+"
    "(([[:space:]]*(nome|codigo|telefone|endereco|data_nascimento|codigo_pes|codigo_tipo)[[:space:]]*="
    "[[:space:]]*('[^']*'|[0-9]+)[[:space:]]*,?)+)[[:space:]]+"
    "where[[:space:]]+codigo[[:space:]]*=[[:space:]]*[0-9]+[[:space:]]*;$";
        return (validar_sintaxe(comando_lower, pattern));
    }
    if ( strstr(comando_lower, "delete from") == comando_lower) {
        const char *pattern = "^delete from[[:space:]]+(tipo_pet|pet|pessoa)[[:space:]]+where[[:space:]]+(nome|codigo|telefone|endereco|data_nascimento|codigo_pes|codigo_tipo)[[:space:]]*=[[:space:]]*('[^']*'|[0-9]+)[[:space:]]*;$";
        return (validar_sintaxe(comando_lower, pattern));

    }
    if ( strstr(comando_lower, "select * from") == comando_lower ) {
        const char *pattern = "^select[[:space:]]+\\*[[:space:]]+from[[:space:]]+(pet|tipo_pet|pessoa)([[:space:]]+where[[:space:]]+(nome|codigo|telefone|endereco|data_nascimento|codigo_pes|codigo_tipo)[[:space:]]*=[[:space:]]*('[^']*'|[0-9]+))?([[:space:]]+order[[:space:]]+by[[:space:]]+(nome|codigo)[[:space:]]*(asc|desc)?)?[[:space:]]*;$";
        return (validar_sintaxe(comando_lower, pattern));
    }

    return 0;
}

void carregar_comando_arquivo(Fila_comando **fila, const char* arquivo) {
    FILE *file = fopen(arquivo, "r");
    if (!file) {
        printf("erro ao abrir o arquivo!\n");
        perror("Detalhes do erro");
        return ;
    }
    char linha[1000];
    while (fgets(linha, sizeof(linha), file)!= NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        inserir_comandoSQL(*fila, linha);
    }
    fclose(file);

}

void imprimir_fila(Fila_comando *fila) {
    Comando *aux = fila->inicio;
    if (fila->inicio == NULL) {
        printf("A fila de comandos está vazia!\n");
        return;
    }
    while (aux) {
        printf("%s\n", aux->descrição);
        aux = aux->proximo;
    }
}
void destruir_fila(Fila_comando *fila) {
    Comando *aux = fila->inicio;
    while (aux) {
        Comando *temp = aux;
        aux = aux->proximo;
        free(temp);
    }
    fila->inicio = fila->final = NULL;
}
void criar_fila_tipos(Fila_comando *fila, Fila_comando **fila_pessoa, Fila_comando **fila_pet, Fila_comando **fila_tipo_pet) {
    Comando *aux = fila->inicio;
    int codigo, codigo_cli, codigo_tipo;
    char nome[255], fone[255], dn[20], description[100];

    while (aux) {
        char comando_lower[100];
        strncpy(comando_lower, aux->descrição, sizeof(comando_lower) - 1);
        comando_lower[sizeof(comando_lower) - 1] = '\0';

        // Converter para minúsculas
        for (int i = 0; comando_lower[i] != '\0'; ++i) {
            comando_lower[i] = (char)tolower(comando_lower[i]);
        }

        char descricao[512]; // Buffer para armazenar o comando formatado

        // ---- INSERT INTO PET ----
        if (strstr(comando_lower, "insert into pet") == comando_lower) {

            //normalizar_aspas(aux->descrição);
            if (sscanf(aux->descrição, "insert into pet(codigo, codigo_cli, nome, codigo_tipo) values(%d, %d, %*['‘’]%254[^'‘’]%*['‘’], %d);",
                       &codigo, &codigo_cli, nome, &codigo_tipo) == 4) {

                snprintf(descricao, sizeof(descricao), "inserir_pet(%d, %d, '%s', %d)", codigo, codigo_cli, nome, codigo_tipo);
                inserir_comandoC(fila_pet, descricao);
            } else {
                printf("Erro ao extrair valores do comando INSERT INTO PET!\n");
            }
        }
        // ---- INSERT INTO PESSOA ----

        else if (strstr(comando_lower, "insert into pessoa") == comando_lower) {
            int codigo_pessoa = -1;
            char nome_pessoa[255] = "", fone_pessoa[20] = "", endereco[255] = "", data_nascimento[11] = "";
            int offset = 0;

            // Todos os campos presentes (aceitando aspas simples e curvas)
            if (sscanf(aux->descrição, "insert into pessoa(codigo, nome, fone, endereco, data_nascimento) values(%d, %*['‘’]%254[^'‘’]%*['‘’], %*['‘’]%19[^'‘’]%*['‘’], %*['‘’]%254[^'‘’]%*['‘’], %*['‘’]%10[^'‘’]%*['‘’]);%n",
                       &codigo_pessoa, nome_pessoa, fone_pessoa, endereco, data_nascimento, &offset) == 5) {
                snprintf(descricao, sizeof(descricao), "inserir_pessoa(%d, '%s', '%s', '%s', '%s')", codigo_pessoa, nome_pessoa, fone_pessoa, endereco, data_nascimento);
                       }
            // Sem endereço
            else if (sscanf(aux->descrição, "insert into pessoa(codigo, nome, fone, data_nascimento) values(%d, %*['‘’]%254[^'‘’]%*['‘’], %*['‘’]%19[^'‘’]%*['‘’], %*['‘’]%10[^'‘’]%*['‘’]);%n",
                            &codigo_pessoa, nome_pessoa, fone_pessoa, data_nascimento, &offset) == 4) {
                snprintf(descricao, sizeof(descricao), "inserir_pessoa(%d, '%s', '%s', '%s')", codigo_pessoa, nome_pessoa, fone_pessoa, data_nascimento);
                            }
            // Sem telefone e endereço
            else if (sscanf(aux->descrição, "insert into pessoa(codigo, nome, data_nascimento) values(%d, %*['‘’]%254[^'‘’]%*['‘’], %*['‘’]%10[^'‘’]%*['‘’]);%n",
                            &codigo_pessoa, nome_pessoa, data_nascimento, &offset) == 3) {
                snprintf(descricao, sizeof(descricao), "inserir_pessoa(%d, '%s', '%s')", codigo_pessoa, nome_pessoa, data_nascimento);
                            }
            // Se faltar código, nome ou data, a inserção falha
            else {
                printf("Erro: Código, nome e data de nascimento são obrigatórios para INSERT INTO pessoa!\n");
                return;
            }

            inserir_comandoC(fila_pessoa, descricao);
        }


        // ---- INSERT INTO TIPO_PET ----
        //delete from pet where codigo = 3 ;
        if (strstr(comando_lower, "insert into tipo_pet")== comando_lower) {
            if (sscanf(aux->descrição, "insert into tipo_pet(codigo, descricao) values(%d, %*['‘’]%254[^'‘’]%*['‘’]);",&codigo,  &description)==2) {
                snprintf(descricao, sizeof(descricao), "inserir_tipo_pet(%d, %s)", codigo, description);
                inserir_comandoC(fila_tipo_pet, descricao);
            }
        }

        // ---- DELETE FROM PET | PESSOA | TIPO_PET ----
        if (strstr(comando_lower, "delete from") == comando_lower) {
            char tabela[50], campo[50], valor[50];

            if (sscanf(aux->descrição, "delete from %49s where %49s = %49[^;];", tabela, campo, valor) == 3) {
                // Verifica qual tabela está sendo referenciada e formata corretamente
                if (strcmp(tabela, "pet") == 0) {
                    snprintf(descricao, sizeof(descricao), "deletar_pet(%s, %s)", campo, valor);
                    inserir_comandoC(fila_pet, descricao);
                } else if (strcmp(tabela, "pessoa") == 0) {
                    snprintf(descricao, sizeof(descricao), "deletar_pessoa(%s, %s)", campo, valor);
                    inserir_comandoC(fila_pessoa, descricao);
                } else if (strcmp(tabela, "tipo_pet") == 0) {
                    snprintf(descricao, sizeof(descricao), "deletar_tipo_pet(%s, %s)", campo, valor);
                    inserir_comandoC(fila_tipo_pet, descricao);
                } else {
                    printf("Erro: tabela '%s' não reconhecida no DELETE FROM.\n", tabela);
                }
            } else {
                printf("Erro ao extrair valores do comando DELETE FROM!\n");
            }
        } else if (strstr(comando_lower, "update") == comando_lower) {
            char tabela[50], campo_set[50], valor_set[50], campo_where[50], valor_where[50];

            if (sscanf(aux->descrição, "update %49s set %49s =  %*['‘’]%49[^'‘’]%*['‘’] where %49s = %49[^;];",
                       tabela, campo_set, valor_set, campo_where, valor_where) == 5) {
                // Verifica a tabela e formata o comando corretamente
                if (strcmp(tabela, "pet") == 0) {
                    snprintf(descricao, sizeof(descricao), "atualizar_pet('%s', '%s', '%s', '%s')", campo_set, valor_set, campo_where, valor_where);
                    inserir_comandoC(fila_pet, descricao);
                } else if (strcmp(tabela, "pessoa") == 0) {
                    snprintf(descricao, sizeof(descricao), "atualizar_pessoa('%s', '%s', '%s', '%s')", campo_set, valor_set, campo_where, valor_where);
                    inserir_comandoC(fila_pessoa, descricao);
                } else if (strcmp(tabela, "tipo_pet") == 0) {
                    snprintf(descricao, sizeof(descricao), "atualizar_tipo_pet('%s', '%s', '%s', '%s')", campo_set, valor_set, campo_where, valor_where);
                    inserir_comandoC(fila_tipo_pet, descricao);
                } else {
                    printf("Erro: tabela '%s' não reconhecida no UPDATE.\n", tabela);
                }
                       } else {
                           printf("Erro ao extrair valores do comando UPDATE!\n");
                       }
        }else if (strstr(comando_lower, "select * from") == comando_lower) {
            char tabela[50], coluna[50] = "", ordem[10] = "";
            int codigo = -1;  // Inicializa com um valor inválido

            // Caso 1: SELECT * FROM tabela WHERE coluna = valor;
            if (sscanf(aux->descrição, "select * from %49s where %49s = %d;", tabela, coluna, &codigo) == 3) {   //select * from pet order by codigo; select * from pet order by nome;
                snprintf(descricao, sizeof(descricao), "selecionar_%s(%s, %d)", tabela, coluna, codigo);
                if (strcmp(tabela, "pessoa") == 0) {
                    inserir_comandoC(fila_pessoa, descricao);
                }else if (strcmp(tabela, "pet")==0) {
                    inserir_comandoC(fila_pet, descricao);
                }else if (strcmp(tabela, "tipo_pet") == 0) {
                    inserir_comandoC(fila_tipo_pet, descricao);
                }
            }

            // Caso 2: SELECT * FROM tabela ORDER BY coluna (opcionalmente com ASC/DESC)
            else if (sscanf(aux->descrição, "select * from %49s order by %49s %9s;", tabela, coluna, ordem) >= 2) {
                if (strlen(ordem) > 0) {  // Apenas inclui ordem se ela foi especificada
                    snprintf(descricao, sizeof(descricao), "selecionar_%s_orderby(%s, %s)", tabela, coluna, ordem);
                } else {
                    snprintf(descricao, sizeof(descricao), "selecionar_%s_orderby(%s)", tabela, coluna);
                }
                if (strcmp(tabela, "pessoa") == 0) {
                    inserir_comandoC(fila_pessoa, descricao);
                }else if (strcmp(tabela, "pet")==0) {
                    inserir_comandoC(fila_pet, descricao);
                }else if (strcmp(tabela, "tipo_pet") == 0) {
                    inserir_comandoC(fila_tipo_pet, descricao);
                }
            }

            // Caso 3: SELECT * FROM tabela (sem WHERE ou ORDER BY)
            else if (sscanf(aux->descrição, "select * from %49s;", tabela) == 1) {
                snprintf(descricao, sizeof(descricao), "selecionar_%s()", tabela);
                if (strcmp(tabela, "pessoa") == 0) {
                    inserir_comandoC(fila_pessoa, descricao);
                }else if (strcmp(tabela, "pet")==0) {
                    inserir_comandoC(fila_pet, descricao);
                }else if (strcmp(tabela, "tipo_pet") == 0) {
                    inserir_comandoC(fila_tipo_pet, descricao);
                }
            }

            else {
                printf("Erro ao extrair valores do SELECT!\n");
            }
        }


        aux = aux->proximo; // Avançar para o próximo comando na fila
    }
}
void executar_cmd_pessoa(Fila_comando **pessoa, ListaDePessoas **pessoas, ListaDePet **pets) {
    Comando *aux = (*pessoa)->inicio;
    Pessoa *new_pessoa;

    while (aux) {
        if (strstr(aux->descrição, "inserir_pessoa") == aux->descrição) {
            char codigo[255] = "", nome[255]="", fone[30] = "", endereco[255] = "", dt[11]="";
            int cod, telefone = 0;  // Inicializa telefone como 0 caso não seja informado

            // Tenta capturar todos os argumentos (caso completo)
            int num_args = sscanf(aux->descrição, "inserir_pessoa(%254[^,], '%254[^']', '%29[^']', '%254[^']', '%10[^']')",
                                  codigo, nome, fone, endereco, dt);

            if (num_args == 4) {
                // Tenta verificar qual campo está ausente (fone ou endereço)
                char temp_fone[30], temp_endereco[255];

                int check_fone = sscanf(aux->descrição, "inserir_pessoa(%254[^,], '%254[^']', '%29[^']', '%10[^']')",
                                        codigo, nome, temp_fone, dt);

                if (check_fone == 4) {
                    endereco[0] = '\0';  // Endereço está ausente
                    strcpy(fone, temp_fone);
                } else {
                    int check_endereco = sscanf(aux->descrição, "inserir_pessoa(%254[^,], '%254[^']', '%254[^']', '%10[^']')",
                                                codigo, nome, temp_endereco, dt);

                    if (check_endereco == 4) {
                        fone[0] = '\0';  // Telefone está ausente
                        strcpy(endereco, temp_endereco);
                    }
                }
            }

            if (num_args == 3) {
                // Caso só tenha código, nome e data
                int check_data = sscanf(aux->descrição, "inserir_pessoa(%254[^,], '%254[^']', '%10[^']')",
                                        codigo, nome, dt);
                if (check_data == 3) {
                    fone[0] = '\0';
                    endereco[0] = '\0';
                }

            }

            if (num_args >= 3) {  // Pelo menos código, nome e data são obrigatórios
                cod = atoi(codigo);

                // Se telefone foi informado, converte para int
                if (fone[0] != '\0') {
                    telefone = atoi(fone);
                }

                new_pessoa = criaPessoa(cod, nome, telefone, dt, endereco, 0, *pessoas);
                *pessoas = insertIntoListaPessoas(pessoas, new_pessoa);
            } else {
                printf("Erro ao processar comando: %s\n", aux->descrição);
            }
        }if (strstr(aux->descrição, "deletar_pessoa")== aux->descrição) {
            char campo[100] = "", valor[100] = "";
            if (sscanf(aux->descrição, "deletar_pessoa(%99[^,], '%99[^']')", campo, valor) == 2 ||
    sscanf(aux->descrição, "deletar_pessoa(%99[^,], %99s)", campo, valor) == 2){
                if (strcmp(campo, "codigo")==0) {
                    int valor_int = atoi(valor);
                    *pessoas = deletePessoa(pessoas, CODIGO, &valor_int, *pets);
                }if (strcmp(campo, "nome")==0) {
                    *pessoas = deletePessoa(pessoas, NOME, valor, *pets);
                }if (strcmp(campo, "data_nascimento")==0) {
                    *pessoas = deletePessoa(pessoas, DATA, valor, *pets);
                }if (strcmp(campo, "telefone")==0) {
                    int fone_int = atoi(valor);
                    *pessoas = deletePessoa(pessoas, TELEFONE, &fone_int, *pets);
                }

            }
        }if (strstr(aux->descrição, "selecionar_pessoa")==aux->descrição) {
            char campo_sel[50]="", valor_sel[100] ="";
            if ( sscanf(aux->descrição, "selecionar_pessoa(%49[^,], %99[^,])", campo_sel, valor_sel) == 2) {
                int valor_sel_int = atoi(valor_sel);
                selectListaPessoas(pessoas, CODIGO, &valor_sel_int, 0, CODIGO);
            }
        }if (strstr(aux->descrição, "atualizar_pessoa") == aux->descrição) {
            char campo_up[100], codigo[255], valor[255], var[255];

            if (sscanf(aux->descrição, "atualizar_pessoa(%99[^,], %254[^,], %254[^,], %254[^,])", campo_up, valor, var, codigo) == 4) {
                int codigo_int = atoi(codigo);

                // Caso: Atualizar telefone
                if (strcmp(campo_up, "telefone") == 0) {
                    int telefone = atoi(valor);
                    Pessoa *dados_atualizados = criaPessoa(-1, "", telefone, "", "", 1, *pessoas);
                    updatePessoas(pessoas, dados_atualizados, TELEFONE, &telefone);

                    // Caso: Atualizar nome
                } else if (strcmp(campo_up, "'nome'") == 0) {
                    Pessoa *dados_atualizados = criaPessoa(-1, valor, -1, "", "", 1, *pessoas);
                    //Pessoa * criaPessoa(int codigo, char * nome, int telefone, char * data, char * endereco, int restringirCampos, ListaDePessoas * listaDePessoas)
                    updatePessoas(pessoas, dados_atualizados, NOME, valor);

                    // Caso: Atualizar data de nascimento
                } else if (strcmp(campo_up, "data_nascimento") == 0) {
                    Pessoa *dados_atualizados = criaPessoa(-1, "", -1, valor, "", 1, *pessoas);
                    updatePessoas(pessoas, dados_atualizados, DATA, valor);

                    // Caso: Atualizar endereço
                } else if (strcmp(campo_up, "endereco") == 0) {
                    Pessoa *dados_atualizados = criaPessoa(-1, "", -1, "", valor, 1, *pessoas);
                    updatePessoas(pessoas, dados_atualizados, ENDERECO, valor);
                }
            }
        }

        aux = aux->proximo;
    }
}

void executar_cmd_pet(Fila_comando **pet, ListaDePet **pets, ListaDePessoas **pessoas, ListaDeTipoDePets **tipo_de_pets) {
Comando *aux = (*pet)->inicio;
    Pet *new_pet;
    while (aux) {
        if (strstr(aux->descrição, "inserir_pet")==aux->descrição) {
            int codigo, codigo_cli, codigo_tipo;
            char nome[255];
            if (sscanf(aux->descrição, "inserir_pet(%d, %d, '%254[^']', %d)", &codigo, &codigo_cli, nome, &codigo_tipo)== 4) {
                new_pet = criaPet(codigo, codigo_cli, nome, codigo_tipo, 0, *pets, *pessoas, *tipo_de_pets);
                *pets = insertIntoListaDePet(pets, new_pet);
            }
        }if (strstr(aux->descrição, "deletar_pet")== aux->descrição) {
            char campo[100] = "", valor[100] = "";
            if (sscanf(aux->descrição,  "deletar_pet(%99[^,], '%99[^']')", campo, valor)==2 ||sscanf(aux->descrição,  "deletar_pet(%99[^,], %99s)", campo, valor)==2 ) {
                if (strcmp(campo, "codigo")==0) {
                    int valor_int = atoi(valor);
                    deletePet(pets, CODIGO_PET, &valor_int);
                }else if (strcmp(campo, "codigo_pes") == 0) {
                    int valor_int = atoi(valor);
                    deletePet(pets, CODIGO_PES_PET, &valor_int);
                } else if (strcmp(campo, "nome") == 0) {
                    deletePet(pets, NOME_PET, valor);
                } else if (strcmp(campo, "codigo_tipo") == 0) {
                    int valor_int = atoi(valor);
                   *pets = deletePet(pets, CODIGO_TIPO_PET, &valor_int);
                }
            }
        }if (strstr(aux->descrição, "selecionar_pet")== aux->descrição) {
            char campo[100] = "", valor[100] = "";
            if (sscanf(aux->descrição, "selecionar_pet(%99[^,], '%99[^']')", campo, valor)==2 || sscanf(aux->descrição,  "selecionar_pet(%99[^,], %99s)", campo, valor)==2) {
                if (strcmp(campo, "nome")==0) {
                    selectListaDePet(pets, NOME_PET, valor, 0,NOME_PET);
                }if (strcmp(campo, "codigo")==0) {
                    int valor_int = atoi(valor);
                    selectListaDePet(pets, CODIGO_PET, &valor_int, 0,NOME_PET);
                }if (strcmp(campo, "codigo_pes")==0) {
                    int valor_int = atoi(valor);
                    selectListaDePet(pets, CODIGO_PES_PET, &valor_int, 0,NOME_PET);
                }if (strcmp(campo, "codigo_tipo")==0) {
                    int valor_int = atoi(valor);
                    selectListaDePet(pets, CODIGO_TIPO_PET, &valor_int, 0,NOME_PET);
                }
            }else if (sscanf(aux->descrição, "selecionar_pet_orderby(%99[^,];)", campo, valor)==2) {



            }
    }if (strstr(aux->descrição, "atualizar_pet") == aux->descrição) {
        char campo[100], valor[100], codigo[100], valor_cod[100];
            if (sscanf("atualizar_pet('%99[^']', '%99[^']', '%99[^']', '%99[^']')", campo, valor, codigo, valor_cod)== 4 ||sscanf("atualizar_pet('%99[^']', %99s, '%99[^']', '%99[^']')", campo, valor, codigo, valor_cod)== 4  ) {
               // Pet *new_pet = criaPet(-1, valor_cod, valor, -1, 1);
                //pets = updatePet(pets, )
            }
        }
        aux = aux->proximo;
    }
}

void executar_cmd_tipo_pet(Fila_comando **tipo_pet, ListaDeTipoDePets **tipos_de_pets) {
    Comando *aux = (*tipo_pet)->inicio;
    TipoDePet *new_tipo_de_pet;
    while (aux) {
        if (strstr(aux->descrição, "inserir_tipo_pet")== aux->descrição) {
            int codigo = -1;
            char descricao[255] ="";
            if (sscanf(aux->descrição, "inserir_tipo_pet(%d, %254s)", &codigo, descricao)== 2) {
                new_tipo_de_pet = criaTipoDePet(codigo, descricao, 1, *tipos_de_pets);
               *tipos_de_pets = insertIntoTipoDePet(tipos_de_pets, new_tipo_de_pet);

            }
        }if (strstr(aux->descrição, "deletar_tipo_pet") == aux->descrição) {
            char campo[100] = "";
            char valor[100] = "";

            if (strstr(aux->descrição, "deletar_tipo_pet") == aux->descrição) {
                char campo[100] = "";
                char valor[100] = "";

                // Captura do comando no formato deletar_tipo_pet(campo, 'valor') ou deletar_tipo_pet(campo, valor)
                if (sscanf(aux->descrição, "deletar_tipo_pet(%99[^,], '%99[^']')", campo, valor) == 2 ||
                    sscanf(aux->descrição, "deletar_tipo_pet(%99[^,], %99s)", campo, valor) == 2) {

                    // Removendo espaços extras no campo
                    while (*campo == ' ') memmove(campo, campo + 1, strlen(campo));

                    if (strcmp(campo, "nome") == 0) {
                        *tipos_de_pets = deleteTipoDePet(tipos_de_pets, NOME_TIPO_DE_PET, valor);
                    } else if (strcmp(campo, "codigo_tipo") == 0) {
                        int valor_int = atoi(valor);
                        *tipos_de_pets = deleteTipoDePet(tipos_de_pets, CODIGO_TIPO_DE_PET, &valor_int);
                    }
                    }
            }



        }if (strstr(aux->descrição, "selecionar_tipo_pet_orderby") == aux->descrição) {
            char campo[100] = "";

            if (sscanf(aux->descrição, "selecionar_tipo_pet_orderby(%99[^)])", campo) == 1) {
                while (*campo == ' ') memmove(campo, campo + 1, strlen(campo)); // Remove espaços extras

                if (strcmp(campo, "codigo") == 0) {
                    selectListaTipoDePet(tipos_de_pets, CODIGO_TIPO_DE_PET, campo, 0, CODIGO_TIPO_DE_PET);
                } else if (strcmp(campo, "nome") == 0) {
                    selectListaTipoDePet(tipos_de_pets, NOME_TIPO_DE_PET, campo, 0, CODIGO_TIPO_DE_PET);
                }
            }
        } else if (strstr(aux->descrição, "selecionar_tipo_pet") == aux->descrição) {
            char campo[100] = "", valor[100] = "";

            if (sscanf(aux->descrição, "selecionar_tipo_pet(%99[^,], %99[^)])", campo, valor) == 2) {
                while (*campo == ' ') memmove(campo, campo + 1, strlen(campo)); // Remove espaços extras

                if (strcmp(campo, "codigo") == 0) {
                    int valor_int = atoi(valor);
                    selectListaTipoDePet(tipos_de_pets, CODIGO_TIPO_DE_PET, &valor_int, 0, CODIGO_TIPO_DE_PET);
                } else if (strcmp(campo, "nome") == 0) {
                    selectListaTipoDePet(tipos_de_pets, NOME_TIPO_DE_PET, valor, 0, CODIGO_TIPO_DE_PET);
                }
            }

    }if (strstr(aux->descrição, "atualizar_tipo_pet") == aux->descrição) {

        }



        aux = aux->proximo;
    }
}





#include <stdio.h>

