//
// Created by Lenya on 09.05.2024.
//

#ifndef LABMEPHI1_COMPLEX_FIELD_IMPL_H
#define LABMEPHI1_COMPLEX_FIELD_IMPL_H

#include "field_info_matrix.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double real;
    double imagine;
} Complex;

Complex *create_complex(double real, double imagine){
    Complex *complex = malloc(sizeof(Complex));
    complex->real = real;
    complex->imagine = imagine;
    return complex;
}

void to_string_complex(void *val, char **result){
    Complex *value = val;
    size_t size = sizeof(char) * ((size_t) ceil(log10(abs(value->real) + 1)) + (size_t) ceil(log10(abs(value->imagine) + 1)) + 12);
    *result = malloc(size);
    sprintf(*result, "%6.2lf + %.2lfi ", value->real, value->imagine);
}

void sum_complex(void *val1, void *val2, void *res){
    Complex *value1 = val1, *value2 = val2, *result = res;
    result->real = value1->real + value2->real;
    result->imagine = value1->imagine + value2->imagine;
}

void sub_complex(void *val1, void *val2, void *res){
    Complex *value1 = val1, *value2 = val2, *result = res;
    result->real = value1->real - value2->real;
    result->imagine = value1->imagine - value2->imagine;
}

void get_zero_complex(void *result){
    Complex *res = result;
    res->imagine = 0;
    res->real = 0;
}

void multiply_complex(void *val1, void *val2, void *res){
    Complex *value1 = val1, *value2 = val2, *result = res;
    result->real = value1->real * value2->real - value1->imagine * value2->imagine;
    result->imagine = value1->real * value2->imagine + value1->imagine * value2->real;
}

void random_complex(void *result){
    Complex *value = result;
    value->real = (double)(rand() % 9 + 1);
    value->imagine = (double)(rand() % 9 + 1);
}

void scan_complex(void *result){
    Complex *value = result;
    scanf("%lf %lf", &value->real, &value->imagine);
}

Field_info *fieldInfo_complex = NULL;

Field_info *get_complex_field_info(){
    if(fieldInfo_complex == NULL){
        create_Field_info(sizeof(Complex) * 8, &fieldInfo_complex);
        fieldInfo_complex->random = random_complex;
        fieldInfo_complex->scan = scan_complex;
        fieldInfo_complex->get_zero = get_zero_complex;
        fieldInfo_complex->multiply = multiply_complex;
        fieldInfo_complex->sub = sub_complex;
        fieldInfo_complex->sum = sum_complex;
        fieldInfo_complex->to_string = to_string_complex;
        fieldInfo_complex->random = random_complex;
    }
    return fieldInfo_complex;
}

#endif //LABMEPHI1_COMPLEX_FIELD_IMPL_H
