//
// Created by Lenya on 09.05.2024.
//

#ifndef LABMEPHI1_MATRIX_REALIZATION_H
#define LABMEPHI1_MATRIX_REALIZATION_H

#include "field_info_matrix.h"
#include <stdio.h>

typedef struct {
    size_t length;
    void *matrix;
    Field_info *fieldInfo;
} Matrix;

void create_matrix(size_t length, Field_info *fieldInfo, Matrix **matrix){
    Matrix *new_matrix = (Matrix *) malloc(sizeof(Matrix));
    new_matrix->length = length;
    new_matrix->fieldInfo = fieldInfo;
    void *matr = malloc((fieldInfo->size_of_field) * length * length);
    new_matrix->matrix = matr;
    *matrix = new_matrix;
}

void set_matrix_value(void* value, size_t i, size_t j, Matrix *matrix){
    size_t size = matrix->fieldInfo->size_of_field;
    char *fiel = value;
    char *matr = (matrix->matrix + size / 8 * (i * matrix->length + j));
    for(size_t l = 0; l < size / 8; l++){
        *(matr + l) = *(fiel + l);
    }
}

void get_matrix_value(size_t i, size_t j, Matrix *matrix, void **ret){
    size_t size = matrix->fieldInfo->size_of_field;
    *ret = matrix->matrix + size/8 * (i * matrix->length + j);
}

void print_all_matrix(Matrix *matrix){
    char *str;
    void *value;
    for(size_t i = 0; i < matrix->length; i++){
        for(size_t j = 0; j < matrix->length; j++){
            get_matrix_value(i, j, matrix, &value);
            matrix->fieldInfo->to_string(value, &str);
            printf("%5s", str);
        }
        printf("\n");
    }
    printf("\n");
}

void sum_matrixs(Matrix *matrix1, Matrix *matrix2, Matrix **result_matrix){
    if(matrix1->length != matrix2->length){
        printf("Matrix have different sizes");
        return;
    }
    size_t length = matrix1->length;
    Field_info *fieldInfo = matrix1->fieldInfo;
    create_matrix(length, fieldInfo, result_matrix);
    void *value1 = malloc(fieldInfo->size_of_field);
    void *value2 = malloc(fieldInfo->size_of_field);
    void *result_value = malloc(fieldInfo->size_of_field);
    for(size_t i = 0; i < length; i++){
        for(size_t j = 0; j < length; j++){
            get_matrix_value(i, j, matrix1, &value1);
            get_matrix_value(i, j, matrix2, &value2);
            fieldInfo->sum(value1, value2, result_value);
            set_matrix_value(result_value, i, j, *result_matrix);
        }
    }
}

void sub_matrixs(Matrix *matrix1, Matrix *matrix2, Matrix **result_matrix){
    if(matrix1->length != matrix2->length){
        printf("Matrix have different sizes");
        return;
    }
    size_t length = matrix1->length;
    Field_info *fieldInfo = matrix1->fieldInfo;
    create_matrix(length, fieldInfo, result_matrix);
    void *value1 = malloc(fieldInfo->size_of_field);
    void *value2 = malloc(fieldInfo->size_of_field);
    void *result_value = malloc(fieldInfo->size_of_field);
    for(size_t i = 0; i < length; i++){
        for(size_t j = 0; j < length; j++){
            get_matrix_value(i, j, matrix1, &value1);
            get_matrix_value(i, j, matrix2, &value2);
            fieldInfo->sub(value1, value2, result_value);
            set_matrix_value(result_value, i, j, *result_matrix);
        }
    }
}

void multiply_matrixs(Matrix *matrix1, Matrix *matrix2, Matrix **result_matrix){
    if(matrix1->length != matrix2->length){
        printf("wrong sizes matrixs");
        return;
    }
    size_t length = matrix1->length;
    Field_info *fieldInfo = matrix1->fieldInfo;
    create_matrix(length, fieldInfo, result_matrix);
    void *value1 = malloc(fieldInfo->size_of_field);
    void *value2 = malloc(fieldInfo->size_of_field);
    void *multiply_value = malloc(fieldInfo->size_of_field);
    void *result_value = malloc(fieldInfo->size_of_field);
    for(size_t i = 0; i < length; i++){
        for(size_t j = 0; j < length; j++){
            fieldInfo->get_zero(result_value);
            for(size_t l = 0; l < length; l++) {
                get_matrix_value(i, l, matrix1, &value1);
                get_matrix_value(l, j, matrix2, &value2);
                fieldInfo->multiply(value1, value2, multiply_value);
                fieldInfo->sum(result_value, multiply_value, result_value);
            }
            set_matrix_value(result_value, i, j, *result_matrix);
        }
    }
}

void multiply_matrix_scal(Matrix *matrix, void* scal, Matrix **result_matrix){
    size_t length = matrix->length;
    Field_info *fieldInfo = matrix->fieldInfo;
    create_matrix(length, fieldInfo, result_matrix);
    void *value = malloc(fieldInfo->size_of_field);
    void *result_value = malloc(fieldInfo->size_of_field);
    for(size_t i = 0; i < length; i++){
        for(size_t j = 0; j < length; j++){
            get_matrix_value(i, j, matrix, &value);
            fieldInfo->multiply(scal, value, result_value);
            set_matrix_value(result_value, i, j, *result_matrix);
        }
    }
}

void fill_matrix_random(Matrix *matrix){
    size_t length = matrix->length;
    Field_info *fieldInfo = matrix->fieldInfo;
    void *fiel = malloc(fieldInfo->size_of_field);
    for(size_t i = 0, j = 1; i < length && j < length; i++, j++){
        fieldInfo->random(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    for(size_t i = 0, j = 0; i < length && j < length; i++, j++){
        fieldInfo->random(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    for(size_t i = 1, j = 0; i < length && j < length; i++, j++){
        fieldInfo->random(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    for(size_t i = 0; i < length; i++){
        for(size_t j = 0; j < length; j++){
            if(i != j && i - 1 != j && j - 1 != i){
                set_matrix_value(fieldInfo->get_zero, i, j, matrix);
            }
        }
    }
}

void fill_matrix_scan(Matrix *matrix){
    size_t length = matrix->length;
    Field_info *fieldInfo = matrix->fieldInfo;
    void *fiel = malloc(fieldInfo->size_of_field);
    printf("Fill the line above the center line:\n");
    for(size_t i = 0, j = 1; i < length && j < length; i++, j++){
        fieldInfo->scan(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    printf("Fill the center line:\n");
    for(size_t i = 0, j = 0; i < length && j < length; i++, j++){
        fieldInfo->scan(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    printf("Fill the line below the center line:\n");
    for(size_t i = 1, j = 0; i < length && j < length; i++, j++){
        fieldInfo->scan(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    for(size_t i = 0; i < length; i++){
        for(size_t j = 0; j < length; j++){
            if(i != j && i - 1 != j && j - 1 != i){
                set_matrix_value(fieldInfo->get_zero, i, j, matrix);
            }
        }
    }
}

#endif //LABMEPHI1_MATRIX_REALIZATION_H
