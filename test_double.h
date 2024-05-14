//
// Created by Lenya on 15.05.2024.
//

#ifndef LABMEPHI1_TEST_DOUBLE_H
#define LABMEPHI1_TEST_DOUBLE_H

#include <assert.h>
#include "matrix_realization.h"
#include "double_field_impl.h"

void create_matrix_test_double(){
    Matrix *matrix = NULL;
    Field_info *fieldInfo = get_double_field_info();
    create_matrix(2, fieldInfo, &matrix);
    assert(matrix != NULL);
    assert(2 == matrix->length);
    assert(matrix->matrix != NULL);
    free(matrix->matrix);
    free(matrix);
}

void set_get_matrix_test_double() {
    Matrix *matrix = NULL;
    Field_info *fieldInfo = get_double_field_info();
    create_matrix(2, fieldInfo, &matrix);
    double value = 5.5;
    set_matrix_value(&value, 0, 0, matrix);

    double *retrievedValue = NULL;
    get_matrix_value(0, 0, matrix, (void**)&retrievedValue);
    assert(5.5 == *retrievedValue);

    free(matrix->matrix);
    free(matrix);
}

void sum_matrix_test_double() {
    Matrix *matrix1 = NULL, *matrix2 = NULL, *result_matrix = NULL;
    Field_info *fieldInfo = get_double_field_info();
    create_matrix(2, fieldInfo, &matrix1);
    create_matrix(2, fieldInfo, &matrix2);

    double values1[2][2] = {{1.0, 2.0}, {3.0, 4.0}};
    double values2[2][2] = {{2.0, 0.0}, {1.0, 2.0}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            set_matrix_value(&values1[i][j], i, j, matrix1);
            set_matrix_value(&values2[i][j], i, j, matrix2);
        }
    }

    sum_matrixs(matrix1, matrix2, &result_matrix);

    double *resultValue = NULL;
    get_matrix_value(0, 0, result_matrix, (void**)&resultValue);
    assert(3.0 == *resultValue);

    free(matrix1->matrix);
    free(matrix1);
    free(matrix2->matrix);
    free(matrix2);
    free(result_matrix->matrix);
    free(result_matrix);
}

void sub_matrix_test_double() {
    Matrix *matrix1 = NULL, *matrix2 = NULL, *result_matrix = NULL;
    Field_info *fieldInfo = get_double_field_info();
    create_matrix(2, fieldInfo, &matrix1);
    create_matrix(2, fieldInfo, &matrix2);

    double values1[2][2] = {{1.0, 2.0}, {3.0, 4.0}};
    double values2[2][2] = {{2.0, 0.0}, {1.0, 2.0}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            set_matrix_value(&values1[i][j], i, j, matrix1);
            set_matrix_value(&values2[i][j], i, j, matrix2);
        }
    }

    sub_matrixs(matrix1, matrix2, &result_matrix);

    double *resultValue = NULL;
    get_matrix_value(0, 0, result_matrix, (void**)&resultValue);
    assert(-1.0 == *resultValue);

    free(matrix1->matrix);
    free(matrix1);
    free(matrix2->matrix);
    free(matrix2);
    free(result_matrix->matrix);
    free(result_matrix);
}

void multiply_matrix_test_double() {
    Matrix *matrix1 = NULL, *matrix2 = NULL, *result_matrix = NULL;
    Field_info *fieldInfo = get_double_field_info();
    create_matrix(2, fieldInfo, &matrix1);
    create_matrix(2, fieldInfo, &matrix2);

    double values1[2][2] = {{1.0, 2.0}, {3.0, 4.0}};
    double values2[2][2] = {{2.0, 0.0}, {1.0, 2.0}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            set_matrix_value(&values1[i][j], i, j, matrix1);
            set_matrix_value(&values2[i][j], i, j, matrix2);
        }
    }

    multiply_matrixs(matrix1, matrix2, &result_matrix);

    double *resultValue = NULL;
    get_matrix_value(0, 1, result_matrix, (void**)&resultValue);
    assert(4.0 == *resultValue);

    free(matrix1->matrix);
    free(matrix1);
    free(matrix2->matrix);
    free(matrix2);
    free(result_matrix->matrix);
    free(result_matrix);
}

void multiply_scal_matrix_test_double() {
    Matrix *matrix = NULL, *result_matrix = NULL;
    Field_info *fieldInfo = get_double_field_info();
    create_matrix(2, fieldInfo, &matrix);

    double values[2][2] = {{1.0, 2.0}, {3.0, 4.0}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            set_matrix_value(&values[i][j], i, j, matrix);
        }
    }
    double scal = 2.0;
    multiply_matrix_scal(matrix, &scal, &result_matrix);

    double *resultValue = NULL;
    get_matrix_value(0, 0, result_matrix, (void**)&resultValue);
    assert(2.0 == *resultValue);

    free(matrix->matrix);
    free(matrix);
    free(result_matrix->matrix);
    free(result_matrix);
}

void maintest_double(){
    create_matrix_test_double();
    set_get_matrix_test_double();
    sum_matrix_test_double();
    sub_matrix_test_double();
    multiply_matrix_test_double();
    multiply_scal_matrix_test_double();
}

#endif //LABMEPHI1_TEST_DOUBLE_H
