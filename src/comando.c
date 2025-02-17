//
// Created by Casa on 10/02/2025.
//

#include "../include/comando.h"
#include "../include/regex.h"
#include "utils.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "regex.h"

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
    "(([[:space:]]*(nome|codigo|fone|endereco|dt|codigo_pes|codigo_tipo)[[:space:]]*="
    "[[:space:]]*('[^']*'|[0-9]+)[[:space:]]*,?)+)[[:space:]]+"
    "where[[:space:]]+codigo[[:space:]]*=[[:space:]]*[0-9]+[[:space:]]*;$";
        return (validar_sintaxe(comando_lower, pattern));
    }
    if ( strstr(comando_lower, "delete from") == comando_lower) {
        const char *pattern = "^delete from[[:space:]]+(tipo_pet|pet|pessoa)[[:space:]]+where[[:space:]]+(nome|codigo|fone|endereco|dt|codigo_pes|codigo_tipo)[[:space:]]*=[[:space:]]*('[^']*'|[0-9]+)[[:space:]]*;$";
        return (validar_sintaxe(comando_lower, pattern));

    }
    if ( strstr(comando_lower, "select * from") == comando_lower ) {
        const char *pattern = "^select[[:space:]]+\\*[[:space:]]+from[[:space:]]+(pet|tipo_pet|pessoa)([[:space:]]+where[[:space:]]+(nome|codigo|fone|endereco|dt|codigo_pes|codigo_tipo)[[:space:]]*=[[:space:]]*('[^']*'|[0-9]+))?([[:space:]]+order[[:space:]]+by[[:space:]]+(nome|codigo)[[:space:]]*(asc|desc)?)?[[:space:]]*;$";
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

            if (sscanf(aux->descrição, "update %49s set %49s = %49[^ ] where %49s = %49[^;];",
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
                snprintf(descricao, sizeof(descricao), "selecionar_%s(%d)", tabela, codigo);
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




#include <stdio.h>

