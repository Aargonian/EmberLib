#include <arraylist_new.h>

int arraylist_err = 0;

void __al_destroy_arraylist(void *array)
{
    free(((size_t *) array) - 3);
}

int __al_check_bounds(size_t index, size_t max)
{
    if(index >= max)
    {
        arraylist_err = AL_ERR_OUT_OF_BOUNDS;
        return 0;
    }
    return 1;
}

void *__preprocess_al_push(void *array)
{
    size_t *arr = (size_t *) (array);
    arr = arr - 3;
    if(arr[0] == arr[1])
    {
        //Double the array size you maggot
        arr[1] *= 2;
        size_t new_size = arr[2] * arr[1] + sizeof(size_t) * 3;
        size_t *new_arr = malloc(new_size);
        new_arr[0] = arr[0];
        new_arr[1] = arr[1];
        new_arr[2] = arr[2];

        //Copy the old elements
        memcpy((void *) (new_arr + 3), array, arr[0] * arr[2]);

        //Free the old data
        free(arr);
        return (void *) (new_arr + 3);
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

