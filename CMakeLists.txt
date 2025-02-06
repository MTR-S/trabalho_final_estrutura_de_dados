cmake_minimum_required(VERSION 3.26)
project(trabalho_final_estrutura_de_dados C)

set(CMAKE_C_STANDARD 99)

add_executable(trabalho_final_estrutura_de_dados main.c
        src/pessoa.c
        include/pessoa.h)
