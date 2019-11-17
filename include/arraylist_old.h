//
// Created by Aargo on 11/8/2019.
//

#ifndef OPENGLLIB_ARRAYLIST_H
#define OPENGLLIB_ARRAYLIST_H

#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_CAPACITY 1

#define create_arraylist_type(TYPE) \
typedef struct array_of_##TYPE{\
    void (*append)(struct array_of_##TYPE *lst, TYPE obj);\
    size_t len;\
    size_t cap;\
    TYPE * data;\
} arraylist_##TYPE; \
\
void append_##TYPE(arraylist_##TYPE *lst, TYPE obj) \
{\
    if(lst->len == lst->cap)\
    {\
        lst->cap *= 2;\
        TYPE *new_data = malloc(sizeof(TYPE)*lst->cap);\
        for(size_t i = 0; i < lst->len; i++)\
        {\
            new_data[i] = lst->data[i];\
        }\
        free(lst->data);\
        lst->data = new_data;\
    }\
    lst->data[lst->len] = obj;\
    lst->len++;\
}\
\
arraylist_##TYPE *create_arraylist_##TYPE(size_t capacity)\
{\
    arraylist_##TYPE *arr = malloc(sizeof(arraylist_##TYPE));\
    arr->len = 0;\
    arr->cap = capacity > 0 ? capacity : DEFAULT_CAPACITY;\
    arr->data = malloc(sizeof(TYPE)*DEFAULT_CAPACITY);\
    arr->append = append_##TYPE;\
    return arr;\
}\
\
void destroy_arraylist_##TYPE(arraylist_##TYPE *lst)\
{\
    if(lst) \
    {\
        if(lst->data)\
        {\
            free(lst->data);\
            lst->data = NULL;\
        }\
        free(lst);\
    }\
}

#define arraylist(TYPE) arraylist_##TYPE
#define create_arraylist(TYPE, CAPACITY) create_arraylist_##TYPE(CAPACITY)
#define destroy_arraylist(TYPE, LST) destroy_arraylist_##TYPE(LST)

// Below is an example of trying to make a native array. This has some benefits and some drawbacks.
#define create_array(TYPE, CAPACITY) \
(\
        (TYPE) *arr = malloc(sizeof(TYPE) * (CAPACITY)),\
        arr[0] = 0,\
        arr[1] = (CAPACITY),\
        arr = arr[2]\
)

#endif //OPENGLLIB_ARRAYLIST_H
