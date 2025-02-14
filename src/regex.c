//
// Created by vinicius on 11/02/25.
//

#include "regex.h"
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>


int validar_sintaxe(const char *comando, const char *expressao) {
    regex_t regex;
    int ret =0;
    ret = regcomp(&regex, expressao, REG_ICASE | REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Erro: não foi possível compilar a expressão regular.\n");
        exit(1);
    }
    ret = regexec(&regex, comando, 0, NULL,0);
    regfree(&regex);
    return (ret == 0);
}

