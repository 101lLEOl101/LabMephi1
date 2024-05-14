//
// Created by Lenya on 09.05.2024.
//

#ifndef LABMEPHI1_DOUBLE_FIELD_IMPL_H
#define LABMEPHI1_DOUBLE_FIELD_IMPL_H

#include "field_info_matrix.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void to_string_double(void *val, char **result){
    double value = *((double*)(val));
    size_t size = sizeof(char) * (double) log10(abs(value) + 1);
    *result = malloc(size);
    sprintf(*result, "%f ", value);
}

void sum_double(void *val1, void *val2, void *res){
    double *value1 = val1;
    double *value2 = val2;
    double *result = res;
    *result = *value1 + *value2;
}

void sub_double(void *val1, void *val2, void *res){
    double *value1 = val1;
    double *value2 = val2;
    double *result = res;
    *result = *value1 - *value2;
}

void get_zero_double(void *result){
    double *res = result;
    *res = 0;
}

void multiply_double(void *val1, void *val2, void *res){
    double *value1 = val1;
    double *value2 = val2;
    double *result = res;
    *result = *value1 * *value2;
}

void random_double(void *result){
    double *value = result;
    *value = (double)(rand() % 9 + 1);
}

void scan_double(void *result){
    double *value = result;
    scanf("%lf", value);
}

Field_info *fieldInfo_double = NULL;

Field_info *get_double_field_info(){
    if(fieldInfo_double == NULL){
        create_Field_info(sizeof(double) * 8, &fieldInfo_double);
        fieldInfo_double->random = random_double;
        fieldInfo_double->scan = scan_double;
        fieldInfo_double->get_zero = get_zero_double;
        fieldInfo_double->multiply = multiply_double;
        fieldInfo_double->sub = sub_double;
        fieldInfo_double->sum = sum_double;
        fieldInfo_double->to_string = to_string_double;
        fieldInfo_double->random = random_double;
    }
    return fieldInfo_double;
}

#endif //LABMEPHI1_DOUBLE_FIELD_IMPL_H
