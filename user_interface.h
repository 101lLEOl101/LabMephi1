//
// Created by Lenya on 09.05.2024.
//

#ifndef LABMEPHI1_USER_INTERFACE_H
#define LABMEPHI1_USER_INTERFACE_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix_realization.h"
#include "double_field_impl.h"
#include "complex_field_impl.h"

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

bool is_first = 1;
Matrix_array *matrixArr = NULL;
Command_array *type_command = NULL;
Command_array *start_operation_command = NULL;
Command_array *main_operation_command = NULL;

void start_user_interface();

void print_command_array(Command_array *commandArray) {
    printf("%d - %s\n", 0, "back");
    for(size_t i = 0; i < commandArray->size; i++){
        printf("%zu - %s\n", i + 1, commandArray->commands[i]);
    }
}

void create_command_array(size_t size, Command_array **result_command_array){
    Command_array *commandArray = malloc(sizeof(Command_array));
    commandArray->size = size;
    commandArray->commands = malloc(sizeof(char**) * size);
    *result_command_array = commandArray;
}

Command_array *get_type_command(){
    create_command_array(2, &type_command);
    char **commands = type_command->commands;
    commands[0] = "double";
    commands[1] = "complex";
    return type_command;
}

Command_array *get_start_operation_command(){
    create_command_array(2, &start_operation_command);
    char **commands = start_operation_command->commands;
    commands[0] = "create matrix";
    commands[1] = "choose matrix";
    return start_operation_command;
}

Command_array *get_main_operation_command(){
    create_command_array(7, &main_operation_command);
    char **commands = main_operation_command->commands;
    commands[0] = "print matrix";
    commands[1] = "fill matrix by random";
    commands[2] = "fill matrix by scan";
    commands[3] = "sum matrixs";
    commands[4] = "subtract matrixs";
    commands[5] = "multiply matrixs";
    commands[6] = "multiply matrix by scalar";
    return main_operation_command;
}

void add_matrix(Matrix_interface *matrix){
    size_t size = matrixArr->size + 1;
    matrixArr->size = size;
    matrixArr->matrixs = realloc(matrixArr->matrixs, sizeof(Matrix_array) * size);
    matrixArr->matrixs[size - 1] = matrix;
}

void free_matrix_interface(Matrix_interface *matrixInterface){
    if(matrixInterface == NULL){
        return;
    }
    if(matrixInterface->matrix != NULL){
        if(matrixInterface->matrix->matrix != NULL) {
            free(matrixInterface->matrix->matrix);
        }
        free(matrixInterface->matrix);
    }
    if(matrixInterface->name != NULL){
        free(matrixInterface->name);
    }
    free(matrixInterface);
}

size_t choose_command(Command_array *commandArray){
    int command_number = 0;
    do{
        print_command_array(commandArray);
        scanf("%d", &command_number);
        while (getchar() != '\n') {
        }
    } while(command_number < 0 || command_number > commandArray->size);
    return command_number;
}


void create_matrix_interface(){
    printf("write name of the matrix:\n");
    char *name = malloc(sizeof(char) * 21);
    scanf("%s", name);
    Matrix_interface *matrixInterface = malloc(sizeof(Matrix_interface));
    matrixInterface->is_empty = 1;
    matrixInterface->name = name;
    size_t len;
    printf("write length of matrix:\n");
    scanf("%zu", &len);
    printf("choose type of matrix:\n");
    size_t type = choose_command(get_type_command());
    Field_info *fieldInfo;
    switch (type) {
        case 0:
            break;
        case 1:
            matrixInterface->type = "double";
            fieldInfo = get_double_field_info();
            create_matrix(len, fieldInfo, &matrixInterface->matrix);
            add_matrix(matrixInterface);
            break;
        case 2:
            matrixInterface->type = "complex";
            fieldInfo = get_complex_field_info();
            create_matrix(len, fieldInfo, &matrixInterface->matrix);
            add_matrix(matrixInterface);
            break;
    }
    start_user_interface();
}



size_t choose_matrix_from_array(){
    if(matrixArr->size == 0){
        printf("No one matrix in array\n");
        start_user_interface();
        return -1;
    }
    int matrix_number;
    do{
        printf("choose matrix:\n");
        for(size_t i = 0; i < matrixArr->size; i++){
            printf("%zu type - \"%s\", name - \"%s\"\n", i+1, matrixArr->matrixs[i]->type, matrixArr->matrixs[i]->name);
        }
        scanf("%d", &matrix_number);
    } while (matrix_number < 0 || matrix_number > matrixArr->size);
    return matrix_number - 1;
}


void main_operation(){
    size_t matrix_number1 = choose_matrix_from_array(), matrix_number2;
    Matrix_interface *matrixInterface1 = matrixArr->matrixs[matrix_number1], *matrixInterface2, *matrixInterfaceResult;
    size_t command_number = choose_command(get_main_operation_command());
    char *name;
    void* scal = malloc(matrixInterface1->matrix->fieldInfo->size_of_field);
    if(command_number > 3){
        matrixInterfaceResult = malloc(sizeof(Matrix_interface));
        char *number = malloc(sizeof(char) * 3);
        name = malloc(sizeof(char) * 10);
        name[0] = '\0';
        number[0] = (char) ((matrixArr->size + 1) / 10 + 48);
        number[1] = (char) (matrixArr->size + 1 + 48);
        number[2] = '\0';
        strcat(name, "matrix - ");
        strcat(name, number);
        if(command_number != 7) {
            matrix_number2 = choose_matrix_from_array();
            matrixInterface2 = matrixArr->matrixs[matrix_number2];
            if (matrixInterface1->is_empty) {
                printf("first matrix is empty\n");
                free(number);
                free(name);
                start_user_interface();
                return;
            } else if (matrixInterface2->is_empty) {
                printf("second matrix is empty\n");
                free(number);
                free(name);
                start_user_interface();
                return;
            } else if (matrixInterface1->type != matrixInterface2->type) {
                printf("Different types of matrixs\n");
                free(number);
                free(name);
                start_user_interface();
                return;
            }
        }
        if(command_number == 7){
            printf("write scalar:\n");
            matrixInterface1->matrix->fieldInfo->scan(scal);
        }
    }
    switch (command_number) {
        case 1:
            if(matrixInterface1->is_empty){
                printf("matrix is empty\n");
            }
            else{
                print_all_matrix(matrixInterface1->matrix);
            }
            break;
        case 2:
            fill_matrix_random(matrixInterface1->matrix);
            matrixInterface1->is_empty = 0;
            break;
        case 3:
            fill_matrix_scan(matrixInterface1->matrix);
            matrixInterface1->is_empty = 0;
            break;
        case 4:
            sum_matrixs(matrixInterface1->matrix, matrixInterface2->matrix, &matrixInterfaceResult->matrix);
            matrixInterfaceResult->type = matrixInterface1->type;
            matrixInterfaceResult->is_empty = 0;
            matrixInterfaceResult->name = name;
            add_matrix(matrixInterfaceResult);
            break;
        case 5:
            sub_matrixs(matrixInterface1->matrix, matrixInterface2->matrix, &matrixInterfaceResult->matrix);
            matrixInterfaceResult->type = matrixInterface1->type;
            matrixInterfaceResult->is_empty = 0;
            matrixInterfaceResult->name = name;
            add_matrix(matrixInterfaceResult);
            break;
        case 6:
            multiply_matrixs(matrixInterface1->matrix, matrixInterface2->matrix, &matrixInterfaceResult->matrix);
            matrixInterfaceResult->type = matrixInterface1->type;
            matrixInterfaceResult->is_empty = 0;
            matrixInterfaceResult->name = name;
            add_matrix(matrixInterfaceResult);
            break;
        case 7:
            multiply_matrix_scal(matrixInterface1->matrix, scal, &matrixInterfaceResult->matrix);
            matrixInterfaceResult->type = matrixInterface1->type;
            matrixInterfaceResult->is_empty = 0;
            matrixInterfaceResult->name = name;
            add_matrix(matrixInterfaceResult);
            break;
        case 0:
            break;
    }
    start_user_interface();
}

void start_user_interface(){
    bool is_f = is_first;
    if(is_first){
        is_first = 0;
        printf("Welcome to matrix realization!\n");
        matrixArr = malloc(sizeof(Matrix_array));
        matrixArr->size = 0;
        matrixArr->matrixs = malloc(sizeof(Matrix_interface));
    }
    size_t command_number = choose_command(get_start_operation_command());
    switch (command_number) {
        case 1:
            create_matrix_interface();
            break;
        case 2:
            main_operation();
            break;
        case 0:
            if(matrixArr != NULL) {
                for (size_t i = 0; i < matrixArr->size; i++) {
                    free_matrix_interface(matrixArr->matrixs[i]);
                }
                free(matrixArr);
            }
            if(main_operation_command != NULL) {
                free(main_operation_command);
            }
            if(start_operation_command != NULL) {
                free(start_operation_command);
            }
            if(type_command != NULL) {
                free(type_command);
            }
            exit(0);
    }
}

#endif //LABMEPHI1_USER_INTERFACE_H
