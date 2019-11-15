#include <arraylist.h>
#include <string.h>

create_arraylist_type(int)
int main1(void)
{
    arraylist(int) *test = create_arraylist(int, 1);
    for(int i = 0; i < 100; i++)
    {
        test->append(test, i);
        printf("Array Capacity: %zu", test->cap);
        printf(", Array Size: %zu", test->len);
        printf(", Item At %d: %d\n", i, test->data[i]);
    }
    destroy_arraylist(int, test);
    return 0;
}

/*
 * We encapsulate this macro in a false do/while loop so that the variable names are hidden from any outside scope. This
 * should prevent any name clashes.
 */

#define init_array(TYPE, ARRAY)\
size_t len = 0;\
size_t cap = 1;\
size_t element_size = sizeof(TYPE);\
size_t *__al_temp_arr = malloc(sizeof(size_t) * 3 + element_size * cap);\
__al_temp_arr[0] = len;\
__al_temp_arr[1] = cap;\
__al_temp_arr[2] = element_size;\
(ARRAY) = (TYPE *)(__al_temp_arr+3)

#define array_capacity(ARRAY) *(((size_t *)(ARRAY))-2)
#define array_length(ARRAY) *(((size_t *)(ARRAY))-3)

#define array_push(ARRAY, VALUE) \
(ARRAY) = preprocess_al_push(ARRAY);\
(ARRAY)[array_length(ARRAY)] = (VALUE);\
size_t *temp = (size_t *)(ARRAY);\
temp = temp-3;\
temp[0] += 1

void destroy_array(void *array)
{
    free(((size_t *)array)-3);
}

void *preprocess_al_push(void *array)
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
	printf("ARRAY ADDR: %x\n", array);
	printf("ARRAY2 ADDR: %x\n", (new_arr+3));
	free(array);
	array = NULL;
        return (void *)(new_arr+3);
    }
    return array;
}

int main2(void)
{
    int *array = NULL;
    init_array(int, array);
    for(int i = 0; i < 100; i++)
    {
        array_push(array, i);
        printf("Array Capacity: %zu, Array Size: %zu, Item at %d: %d\n", array_capacity(array), array_length(array),
                                                                                  i, array[i]);
    }
    destroy_array(array);
    return 0;
}

int main(int argc, char **argv)
{
    //main1();
    main2();
}
