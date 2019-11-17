/*
 * Created By Aaron Helton on 11/15/2019
 */
#ifndef EMBERLIB_ARRAYLIST_NEW_H
#define EMBERLIB_ARRAYLIST_NEW_H

#include <stdlib.h>
#include <string.h>

#define ARRAYLIST_DEFAULT_CAPACITY 1

/* Function Definitions */
void *__preprocess_al_push(void *arraylist);
void *__create_generic_array(size_t element_size, size_t elements);

/*
 * Small utility macros for the other macros, plus the error definitions
 */
#define arraylist_capacity(ARRAY) *(((size_t *)(ARRAY))-2)
#define arraylist_length(ARRAY) *(((size_t *)(ARRAY))-3)
#define arraylist_element_size(ARRAY) *(((size_t *)(ARRAY))-1)
#define arraylist_memory_footprint(ARRAY) ((arraylist_element_size(ARRAY)*arraylist_capacity(ARRAY)) + 3*sizeof(size_t))

int arraylist_err = 0;
#define AL_ERR_OUT_OF_BOUNDS 1
#define clear_arraylist_err() arraylist_err = 0;

#define init_arraylist_with_capacity(TYPE, ARRAY, CAPACITY) (TYPE *)__create_generic_array(sizeof(TYPE), CAPACITY)
#define init_arraylist(TYPE) init_arraylist_with_capacity(TYPE, ARRAY, ARRAYLIST_DEFAULT_CAPACITY)

#define arraylist_push(ARRAY, VALUE) \
do {\
    ARRAY = __preprocess_al_push(ARRAY);\
    (ARRAY)[arraylist_length(ARRAY)] = (VALUE);\
    size_t *__al_temp = (size_t *)(ARRAY);\
    __al_temp = __al_temp-3;\
    __al_temp[0] += 1;\
} while(0)

#define arraylist_set(ARRAY, INDEX, VALUE) \
do {\
    size_t __i = (size_t)INDEX;\
    if(__i < 0 || __i >= arraylist_length(ARRAY)) {\
        arraylist_err = AL_ERR_OUT_OF_BOUNDS;\
    } else {\
        (ARRAY)[__i] = (VALUE);\
    }\
} while(0)

#define arraylist_get(ARRAY, INDEX) \
    (((size_t)(INDEX) < 0 || (size_t)(INDEX) >= arraylist_length(ARRAY)) ? ARRAY[0] : ARRAY[INDEX])

void destroy_arraylist(void *array)
{
    free(((size_t *)array)-3);
}

void *__preprocess_al_push(void *array)
{
    size_t *arr = (size_t *)(array);
    arr = arr-3;
    if(arr[0] == arr[1])
    {
        //Double the array size you maggot
        arr[1] *= 2;
        size_t new_size = arr[2]*arr[1] + sizeof(size_t)*3;
        size_t *new_arr = malloc(new_size);
        new_arr[0] = arr[0];
        new_arr[1] = arr[1];
        new_arr[2] = arr[2];

        //Copy the old elements
        memcpy((void *)(new_arr+3), array, arr[0]*arr[2]);

        //Free the old data
        free(arr);
        return (void *)(new_arr+3);
    }
    return array;
}

void *__create_generic_array(size_t element_size, size_t elements)
{
    size_t size = element_size * elements + sizeof(size_t) * 3;
    size_t *new_arr = malloc(size);
    new_arr[0] = 0;
    new_arr[1] = elements;
    new_arr[2] = element_size;
    memset(new_arr + 3, 0, size - 3 * sizeof(size_t));
    return (void *) (new_arr + 3);
}

#endif //EMBERLIB_ARRAYLIST_NEW_H
