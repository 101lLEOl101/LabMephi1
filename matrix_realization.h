//
// Created by Lenya on 09.05.2024.
//

#ifndef LABMEPHI1_MATRIX_REALIZATION_H
#define LABMEPHI1_MATRIX_REALIZATION_H

#include "field_info_matrix.h"

typedef struct {
    size_t width;
    size_t height;
    void *matrix;
    Field_info *fieldInfo;
} Matrix;

void create_matrix(size_t width, size_t height, Field_info *fieldInfo, Matrix **matrix){
    Matrix *new_matrix = (Matrix *) malloc(sizeof(Matrix));
    new_matrix->width = width;
    new_matrix->height = height;
    new_matrix->fieldInfo = fieldInfo;
    void *matr = malloc((fieldInfo->size_of_field) * width * height);
    new_matrix->matrix = matr;
    *matrix = new_matrix;
}

void set_matrix_value(void* value, size_t i, size_t j, Matrix *matrix){
    size_t size = matrix->fieldInfo->size_of_field;
    char *fiel = value;
    char *matr = (matrix->matrix + size / 8 * (i * matrix->width + j));
    for(size_t l = 0; l < size / 8; l++){
        *(matr + l) = *(fiel + l);
    }
}

void get_matrix_value(size_t i, size_t j, Matrix *matrix, void **ret){
    size_t size = matrix->fieldInfo->size_of_field;
    *ret = matrix->matrix + size/8 * (i * matrix->width + j);
}

void print_all_matrix(Matrix *matrix){
    char *str;
    void *value;
    for(size_t i = 0; i < matrix->height; i++){
        for(size_t j = 0; j < matrix->width; j++){
            get_matrix_value(i, j, matrix, &value);
            matrix->fieldInfo->to_string(value, str);
            printf("%5s", str);
        }
        printf("\n");
    }
    printf("\n");
}

void sum_matrixs(Matrix *matrix1, Matrix *matrix2, Matrix **result_matrix){
    if(matrix1->width != matrix2->width || matrix1->height != matrix2->height){
        printf("Matrix have different sizes");
        return;
    }
    size_t width = matrix1->width, height = matrix1->height;
    Field_info *fieldInfo = matrix1->fieldInfo;
    create_matrix(width, height, fieldInfo, result_matrix);
    void *value1 = malloc(fieldInfo->size_of_field);
    void *value2 = malloc(fieldInfo->size_of_field);
    void *result_value = malloc(fieldInfo->size_of_field);
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            get_matrix_value(i, j, matrix1, &value1);
            get_matrix_value(i, j, matrix2, &value2);
            fieldInfo->sum(value1, value2, result_value);
            set_matrix_value(result_value, i, j, *result_matrix);
        }
    }
}

void sub_matrixs(Matrix *matrix1, Matrix *matrix2, Matrix **result_matrix){
    if(matrix1->width != matrix2->width || matrix1->height != matrix2->height){
        printf("Matrix have different sizes");
        return;
    }
    size_t width = matrix1->width, height = matrix1->height;
    Field_info *fieldInfo = matrix1->fieldInfo;
    create_matrix(width, height, fieldInfo, result_matrix);
    void *value1 = malloc(fieldInfo->size_of_field);
    void *value2 = malloc(fieldInfo->size_of_field);
    void *result_value = malloc(fieldInfo->size_of_field);
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            get_matrix_value(i, j, matrix1, &value1);
            get_matrix_value(i, j, matrix2, &value2);
            fieldInfo->sub(value1, value2, result_value);
            set_matrix_value(result_value, i, j, *result_matrix);
        }
    }
}

void multiply_matrixs(Matrix *matrix1, Matrix *matrix2, Matrix **result_matrix){
    if(matrix1->width != matrix2->height){
        printf("wrong sizes matrixs");
        return;
    }
    size_t width = matrix1->height, height = matrix2->width;
    Field_info *fieldInfo = matrix1->fieldInfo;
    create_matrix(width, height, fieldInfo, result_matrix);
    void *value1 = malloc(fieldInfo->size_of_field);
    void *value2 = malloc(fieldInfo->size_of_field);
    void *multiply_value = malloc(fieldInfo->size_of_field);
    void *result_value = malloc(fieldInfo->size_of_field);
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            get_matrix_value(i, j, matrix1, &value1);
            get_matrix_value(i, j, matrix2, &value2);
            fieldInfo->multiply(value1, value2, multiply_value);
            fieldInfo->sub(result_value, multiply_value, result_value);
            set_matrix_value(result_value, i, j, *result_matrix);
        }
    }
}

void fill_matrix_random(Matrix *matrix){
    size_t width = matrix->width, height = matrix->height;
    Field_info *fieldInfo = matrix->fieldInfo;
    void *fiel = malloc(fieldInfo->size_of_field);
    for(size_t i = 0, j = 1; i < height && j < width; i++, j++){
        fieldInfo->random(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    for(size_t i = 0, j = 0; i < height && j < width; i++, j++){
        fieldInfo->random(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    for(size_t i = 1, j = 0; i < height && j < width; i++, j++){
        fieldInfo->random(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
}

void fill_matrix_scan(Matrix *matrix){
    size_t width = matrix->width, height = matrix->height;
    Field_info *fieldInfo = matrix->fieldInfo;
    void *fiel = malloc(fieldInfo->size_of_field);
    printf("Fill the line above the center line");
    for(size_t i = 0, j = 1; i < height && j < width; i++, j++){
        fieldInfo->scan(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    printf("Fill the center line");
    for(size_t i = 0, j = 0; i < height && j < width; i++, j++){
        fieldInfo->scan(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
    printf("Fill the line below the center line");
    for(size_t i = 1, j = 0; i < height && j < width; i++, j++){
        fieldInfo->scan(fiel);
        set_matrix_value(fiel, i, j, matrix);
    }
}

#endif //LABMEPHI1_MATRIX_REALIZATION_H
