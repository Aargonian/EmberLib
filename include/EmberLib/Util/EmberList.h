/*
 * Created By Aaron Helton on 11/15/2019
 */
#ifndef EMBERLIB_EMBERLIST_H
#define EMBERLIB_EMBERLIST_H

#include <stdlib.h>


/*******************************************************************************
 * Small utility macros for the other macros, plus the error definitions
 ******************************************************************************/
#define emberlist_capacity(LIST)\
    *(((size_t *)(LIST))-2)
#define emberlist_length(LIST)\
    *(((size_t *)(LIST))-3)
#define emberlist_element_size(LIST)\
    *(((size_t *)(LIST))-1)
#define emberlist_memory_footprint(LIST)\
    ((emberlist_element_size(LIST)*emberlist_capacity(LIST))+3*sizeof(size_t))

extern int emberlist_err;
#define EL_ERR_OUT_OF_BOUNDS 1
#define clear_emberlist_err() emberlist_err = 0

/*******************************************************************************
 *  Creation And Destruction Macros and Functions
 ******************************************************************************/
void *INTERNAL_create_generic_list(size_t element_size, size_t elements);
void INTERNAL_el_destroy_emberlist(void *list);

#define emberlist_create_with_capacity(TYPE, CAPACITY)\
    (TYPE *)INTERNAL_create_generic_list(sizeof(TYPE), CAPACITY)

#define EMBERLIST_DEFAULT_CAPACITY 1
#define emberlist_create(TYPE)\
    emberlist_create_with_capacity(TYPE, EMBERLIST_DEFAULT_CAPACITY)

/*
 * This is a convenience function for emberlists consisting of malloced ptrs.
 * If you use this function, it's assumed you intentionally malloced every
 * element in your list.
 */
#define emberlist_free_all(LIST) \
do {\
    size_t el_len = emberlist_length(LIST);\
    for(size_t el_i = 0; el_i < el_len; el_i++)\
    {\
        if(LIST[el_i]) \
        {\
            free(LIST[el_i]);\
        }\
    }\
} while(0)

#define emberlist_destroy(LIST)\
do {\
INTERNAL_el_destroy_emberlist(LIST);\
LIST = NULL;\
} while(0)

/*******************************************************************************
 * Utility Functions
 ******************************************************************************/
int INTERNAL_el_check_bounds(size_t index, size_t max);
void *INTERNAL_el_process_delete(void *emberlist, size_t index);
void *INTERNAL_preprocess_el_push(void *emberlist);

#define emberlist_push(LIST, VALUE) \
do {\
    LIST = INTERNAL_preprocess_el_push(LIST);\
    (LIST)[emberlist_length(LIST)] = (VALUE);\
    size_t *__el_temp = (size_t *)(LIST);\
    __el_temp = __el_temp-3;\
    __el_temp[0] += 1;\
} while(0)

#define emberlist_delete(LIST, INDEX)\
    LIST = INTERNAL_el_process_delete(LIST, INDEX)

#define emberlist_set(LIST, INDEX, VALUE) \
do {\
    size_t __i = (size_t)INDEX;\
    if(__i < 0 || __i >= emberlist_length(LIST)) {\
        emberlist_err = EL_ERR_OUT_OF_BOUNDS;\
    } else {\
        (LIST)[__i] = (VALUE);\
    }\
} while(0)

#define arraylist_get(LIST, INDEX, DEFAULT_VAL)\
(INTERNAL_el_check_bounds(INDEX, emberlist_length(LIST)) ? LIST[INDEX] : DEFAULT_VAL)

#endif //EMBERLIB_EMBERLIST_H
