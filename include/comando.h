//
// Created by vinicius on 07/02/25.
//

#ifndef COMANDO_H
#define COMANDO_H

typedef struct Comandos {
    char descrição [500];
    struct Comandos *proximo;
}Comando;

int carregar_comando_arquivo(Comando *cmd, const char* arquivo );

#endif //COMANDO_H
