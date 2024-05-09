//
// Created by Lenya on 09.05.2024.
//

#ifndef LABMEPHI1_FIELD_INFO_MATRIX_H
#define LABMEPHI1_FIELD_INFO_MATRIX_H

#include <stdlib.h>

typedef struct {
    size_t size_of_field;
    void (*to_string)(void*, char**);
    void (*sum)(void*, void*, void*);
    void (*sub)(void*, void*, void*);
    void (*multiply)(void*, void*, void*);
    void (*random)(void*);
    void (*scan)(void*);
} Field_info;

void create_Field_info(size_t size, Field_info **ret){
    Field_info *fieldInfo = malloc(sizeof(Field_info));
    fieldInfo->size_of_field = size;
    fieldInfo->to_string = NULL;
    fieldInfo->sum=NULL;
    fieldInfo->sub=NULL;
    fieldInfo->multiply=NULL;
    fieldInfo->random=NULL;
    fieldInfo->scan=NULL;
    *ret = fieldInfo;
}

#endif //LABMEPHI1_FIELD_INFO_MATRIX_H
