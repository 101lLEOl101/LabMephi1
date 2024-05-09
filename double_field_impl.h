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

void to_string(void *val, char **result){
    double value = *((double*)(val));
    size_t size = sizeof(char) * (double) log10(abs(value) + 1);
    *result = malloc(size);
    sprintf(*result, "%d", value);
}

void sum(void *val1, void *val2, void *res){
    double *value1 = val1;
    double *value2 = val2;
    double *result = res;
    *result = *value1 + *value2;
}

void sub(void *val1, void *val2, void *res){
    double *value1 = val1;
    double *value2 = val2;
    double *result = res;
    *result = *value1 - *value2;
}

void multiply(void *val1, void *val2, void *res){
    double *value1 = val1;
    double *value2 = val2;
    double *result = res;
    *result = *value1 * *value2;
}

void random(void *result){
    double *value = result;
    *value = (rand() % 100) / 10;
}

void scan(void *result){
    double *value = result;
    scanf("%lf", &value);
}

Field_info *fieldInfo_double = NULL;

Field_info *get_complex_field_info(){
    if(fieldInfo_double == NULL){
        create_Field_info(sizeof(double) * 8, &fieldInfo_double);
        fieldInfo_double->random = random;
        fieldInfo_double->scan = scan;
        fieldInfo_double->multiply = multiply;
        fieldInfo_double->sub = sub;
        fieldInfo_double->sum = sum;
        fieldInfo_double->to_string = to_string;
        fieldInfo_double->random = random;
    }
    return fieldInfo_double;
}

#endif //LABMEPHI1_DOUBLE_FIELD_IMPL_H
