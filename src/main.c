#include <stdio.h>
#include <stddef.h>
#include <malloc.h>

#define arraylist(TYPE)\
struct {\
    TYPE *ptr;\
    TYPE *array;\
    size_t element_size;\
    size_t length;\
    size_t capacity;\
}

#define init_arraylist_with_capacity(AL_STRUCT_PTR, CAPACITY)\
do {\
    size_t __al_temp_cap = (CAPACITY)\
    AL_STRUCT->array = malloc(__al_temp_cap * sizeof(*AL_STRUCT->ptr));\
    AL_STRUCT->length = 0;\
    AL_STRUCT->capacity = __al_temp_cap;\
} while(0)


#define init_arraylist(ARRAYLIST_STRUCT)\
init_arraylist_with_capacity(ARRAYLIST_STRUCT, 1)



int main(void)
{
    arraylist(int) *array = malloc(sizeof(arraylist(int)));
    init_arraylist(array);
    return 0;
}
