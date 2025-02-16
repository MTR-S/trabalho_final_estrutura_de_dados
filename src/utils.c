//
// Created by vinicius on 14/02/25.
//

#include "../include/utils.h"
void normalizar_aspas(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '‘' || str[i] == '’') {
            str[i] = '\'';
        }
    }
}
