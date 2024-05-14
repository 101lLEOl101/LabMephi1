//
// Created by Lenya on 15.05.2024.
//

#ifndef LABMEPHI1_TEST_COMPLEX_H
#define LABMEPHI1_TEST_COMPLEX_H

#include <assert.h>
#include "matrix_realization.h"
#include "complex_field_impl.h"

void create_matrix_test_complex(){
    Matrix *matrix = NULL;
    Field_info *fieldInfo = get_complex_field_info();
    create_matrix(2, fieldInfo, &matrix);
    assert(matrix != NULL);
    assert(2 == matrix->length);
    assert(matrix->matrix != NULL);
    free(matrix->matrix);
    free(matrix);
}

void set_get_matrix_test_complex() {
    Matrix *matrix = NULL;
    Field_info *fieldInfo = get_complex_field_info();
    create_matrix(2, fieldInfo, &matrix);
    Complex value = {5.5, 1.7};
    set_matrix_value(&value, 0, 0, matrix);

    Complex *retrievedValue = NULL;
    get_matrix_value(0, 0, matrix, (void**)&retrievedValue);
    assert(5.5 == retrievedValue->real);
    assert(1.7 == retrievedValue->imagine);
    free(matrix->matrix);
    free(matrix);
}

void sum_matrix_test_complex() {
    Matrix *matrix1 = NULL, *matrix2 = NULL, *result_matrix = NULL;
    Field_info *fieldInfo = get_complex_field_info();
    create_matrix(2, fieldInfo, &matrix1);
    create_matrix(2, fieldInfo, &matrix2);

    Complex values1[2][2] = {{{1.0, 5.0}, {2.0, 1.0}}, {{3.0, 2.0}, {4.0, 1.0}}};
    Complex values2[2][2] = {{{6.0, 1.0}, {7.0, 3.0}}, {{2.0, 4.0}, {8.0, 3.0}}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            set_matrix_value(&values1[i][j], i, j, matrix1);
            set_matrix_value(&values2[i][j], i, j, matrix2);
        }
    }

    sum_matrixs(matrix1, matrix2, &result_matrix);

    Complex *resultValue = NULL;
    get_matrix_value(0, 0, result_matrix, (void**)&resultValue);
    assert(7.0 == resultValue->real);
    assert(6.0 == resultValue->imagine);
    free(matrix1->matrix);
    free(matrix1);
    free(matrix2->matrix);
    free(matrix2);
    free(result_matrix->matrix);
    free(result_matrix);
}

void sub_matrix_test_complex() {
    Matrix *matrix1 = NULL, *matrix2 = NULL, *result_matrix = NULL;
    Field_info *fieldInfo = get_complex_field_info();
    create_matrix(2, fieldInfo, &matrix1);
    create_matrix(2, fieldInfo, &matrix2);

    Complex values1[2][2] = {{{1.0, 5.0}, {2.0, 1.0}}, {{3.0, 2.0}, {4.0, 1.0}}};
    Complex values2[2][2] = {{{6.0, 1.0}, {7.0, 3.0}}, {{2.0, 4.0}, {8.0, 3.0}}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            set_matrix_value(&values1[i][j], i, j, matrix1);
            set_matrix_value(&values2[i][j], i, j, matrix2);
        }
    }

    sub_matrixs(matrix1, matrix2, &result_matrix);

    Complex *resultValue = NULL;
    get_matrix_value(0, 0, result_matrix, (void**)&resultValue);
    assert(-5.0 == resultValue->real);
    assert(4.0 == resultValue->imagine);

    free(matrix1->matrix);
    free(matrix1);
    free(matrix2->matrix);
    free(matrix2);
    free(result_matrix->matrix);
    free(result_matrix);
}

void multiply_matrix_test_complex() {
    Matrix *matrix1 = NULL, *matrix2 = NULL, *result_matrix = NULL;
    Field_info *fieldInfo = get_complex_field_info();
    create_matrix(2, fieldInfo, &matrix1);
    create_matrix(2, fieldInfo, &matrix2);

    Complex values1[2][2] = {{{1.0, 5.0}, {2.0, 1.0}}, {{3.0, 2.0}, {4.0, 1.0}}};
    Complex values2[2][2] = {{{6.0, 1.0}, {7.0, 3.0}}, {{2.0, 4.0}, {8.0, 3.0}}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            set_matrix_value(&values1[i][j], i, j, matrix1);
            set_matrix_value(&values2[i][j], i, j, matrix2);
        }
    }

    multiply_matrixs(matrix1, matrix2, &result_matrix);

    Complex *resultValue = NULL;
    get_matrix_value(0, 1, result_matrix, (void**)&resultValue);
    assert(5.0 == resultValue->real);
    assert(52.0 == resultValue->imagine);

    free(matrix1->matrix);
    free(matrix1);
    free(matrix2->matrix);
    free(matrix2);
    free(result_matrix->matrix);
    free(result_matrix);
}

void multiply_scal_matrix_test_complex() {
    Matrix *matrix = NULL, *result_matrix = NULL;
    Field_info *fieldInfo = get_complex_field_info();
    create_matrix(2, fieldInfo, &matrix);

    Complex values[2][2] = {{{1.0, 5.0}, {2.0, 1.0}}, {{3.0, 2.0}, {4.0, 1.0}}};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            set_matrix_value(&values[i][j], i, j, matrix);
        }
    }
    Complex scal = {2.0, 1.0};
    multiply_matrix_scal(matrix, &scal, &result_matrix);

    Complex *resultValue = NULL;
    get_matrix_value(0, 0, result_matrix, (void**)&resultValue);
    assert(-3.0 == resultValue->real);
    assert(11.0 == resultValue->imagine);

    free(matrix->matrix);
    free(matrix);
    free(result_matrix->matrix);
    free(result_matrix);
}

void maintest_complex(){
    create_matrix_test_complex();
    set_get_matrix_test_complex();
    sum_matrix_test_complex();
    sub_matrix_test_complex();
    multiply_matrix_test_complex();
    multiply_scal_matrix_test_complex();
}

#endif //LABMEPHI1_TEST_COMPLEX_H
