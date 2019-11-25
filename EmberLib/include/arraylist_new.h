/*
 * Created By Aaron Helton on 11/15/2019
 */
#ifndef EMBERLIB_ARRAYLIST_NEW_H
#define EMBERLIB_ARRAYLIST_NEW_H

#include <stdlib.h>
#include <string.h>

#define ARRAYLIST_DEFAULT_CAPACITY 1

int __al_check_bounds(size_t index, size_t max);
void *__al_process_delete(void *arraylist, size_t index);
void *__preprocess_al_push(void *arraylist);

/*******************************************************************************
 * Small utility macros for the other macros, plus the error definitions
 ******************************************************************************/
#define arraylist_capacity(ARRAY)\
    *(((size_t *)(ARRAY))-2)
#define arraylist_length(ARRAY)\
    *(((size_t *)(ARRAY))-3)
#define arraylist_element_size(ARRAY)\
    *(((size_t *)(ARRAY))-1)
#define arraylist_memory_footprint(ARRAY)\
    ((arraylist_element_size(ARRAY)*arraylist_capacity(ARRAY)) + 3*sizeof(size_t))

extern int arraylist_err;
#define AL_ERR_OUT_OF_BOUNDS 1
#define clear_arraylist_err() arraylist_err = 0

/*******************************************************************************
 *  Creation And Destruction Macros and Functions
 ******************************************************************************/
void *__create_generic_array(size_t element_size, size_t elements);
void __al_destroy_arraylist(void *array);

#define init_arraylist_with_capacity(TYPE, CAPACITY)\
    (TYPE *)__create_generic_array(sizeof(TYPE), CAPACITY)

#define init_arraylist(TYPE)\
    init_arraylist_with_capacity(TYPE, ARRAYLIST_DEFAULT_CAPACITY)

/*
 * This is a convenience function for arraylists consisting of malloced ptrs.
 * If you use this function, it's assumed you intentionally malloced every
 * element in your array.
 */
#define arraylist_free_all(ARRAY) \
do {\
    size_t __al_len = arraylist_length(ARRAY);\
    for(size_t __al_i = 0; __al_i < __al_len; __al_i++)\
    {\
        if(ARRAY[__al_i]) \
        {\
            free(ARRAY[__al_i]);\
        }\
    }\
} while(0)

#define destroy_arraylist(ARRAY)\
do {\
__al_destroy_arraylist(ARRAY);\
ARRAY = NULL;\
} while(0)

/*******************************************************************************
 * Utility Functions
 ******************************************************************************/

#define arraylist_push(ARRAY, VALUE) \
do {\
    ARRAY = __preprocess_al_push(ARRAY);\
    (ARRAY)[arraylist_length(ARRAY)] = (VALUE);\
    size_t *__al_temp = (size_t *)(ARRAY);\
    __al_temp = __al_temp-3;\
    __al_temp[0] += 1;\
} while(0)

#define arraylist_delete(ARRAY, INDEX)\
    ARRAY = __al_process_delete(ARRAY, INDEX)

#define arraylist_set(ARRAY, INDEX, VALUE) \
do {\
    size_t __i = (size_t)INDEX;\
    if(__i < 0 || __i >= arraylist_length(ARRAY)) {\
        arraylist_err = AL_ERR_OUT_OF_BOUNDS;\
    } else {\
        (ARRAY)[__i] = (VALUE);\
    }\
} while(0)

#define arraylist_get(ARRAY, INDEX, DEFAULT_VAL)\
(__al_check_bounds(INDEX, arraylist_length(ARRAY)) ? ARRAY[INDEX] : DEFAULT_VAL)

#endif //EMBERLIB_ARRAYLIST_NEW_H
