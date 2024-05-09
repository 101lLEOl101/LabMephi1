//
// Created by Lenya on 09.05.2024.
//

#ifndef LABMEPHI1_USER_INTERFACE_H
#define LABMEPHI1_USER_INTERFACE_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix_realization.h"

typedef struct {
    size_t size;
    char **commands;
} Command_array;

typedef struct {
    Matrix *matrix;
    char *name;
    char *type;
    bool is_empty;
} Matrix_interface;

typedef struct {
    size_t size;
    Matrix_interface **matrixs;
} Matrix_array;

bool is_first = 0;
Matrix_array *matrixArr = NULL;

size_t choose_command(Command_array *commandArray){

}

void start_user_interface(){
    if(!is_first){
        is_first = 1;
        printf("Welcome to matrix realization!");
        matrixArr = malloc(sizeof(Matrix_array));
        matrixArr->size = 0;
        matrixArr->matrixs = malloc(sizeof(Matrix_interface));
    }
}

#endif //LABMEPHI1_USER_INTERFACE_H
