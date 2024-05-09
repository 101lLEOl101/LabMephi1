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

void to_string(void *val, char **result){
    Complex *value = val;
    size_t size = sizeof(char) * ((size_t) ceil(log10(abs(value->real) + 1)) + (size_t) ceil(log10(abs(value->imagine) + 1)) + 12);
    *result = malloc(size);
    sprintf(*result, "%6.2lf + %.2lfi", value->real, value->imagine);
}

void sum(void *val1, void *val2, void *res){
    Complex *value1 = val1, *value2 = val2, *result = res;
    result->real = value1->real + value2->real;
    result->imagine = value1->imagine + value2->imagine;
}

void sub(void *val1, void *val2, void *res){
    Complex *value1 = val1, *value2 = val2, *result = res;
    result->real = value1->real - value2->real;
    result->imagine = value1->imagine - value2->imagine;
}

void multiply(void *val1, void *val2, void *res){
    Complex *value1 = val1, *value2 = val2, *result = res;
    result->real = value1->real * value2->real - value1->imagine * value2->imagine;
    result->imagine = value1->real * value2->imagine + value1->imagine * value2->real;
}

void random(void *result){
    Complex *value = result;
    value->real = (double)((rand() % 100)/10);
    value->imagine = (double)((rand() % 100)/10);
}

void scan(void *result){
    Complex *value = result;
    scanf("%lf %lf", &value->real, &value->imagine);
}

Field_info *fieldInfo_complex = NULL;

Field_info *get_complex_field_info(){
    if(fieldInfo_complex == NULL){
        create_Field_info(sizeof(Complex) * 8, &fieldInfo_complex);
        fieldInfo_complex->random = random;
        fieldInfo_complex->scan = scan;
        fieldInfo_complex->multiply = multiply;
        fieldInfo_complex->sub = sub;
        fieldInfo_complex->sum = sum;
        fieldInfo_complex->to_string = to_string;
        fieldInfo_complex->random = random;
    }
    return fieldInfo_complex;
}

#endif //LABMEPHI1_COMPLEX_FIELD_IMPL_H
