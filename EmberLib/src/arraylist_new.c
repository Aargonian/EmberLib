/*
 * Created by Aaron Helton on 11/15/19
 */
#include <arraylist_new.h>
#include <stdlib.h>
#include <string.h>

int arraylist_err = 0;

void *__al_process_delete(void *arraylist, size_t index)
{
    if(index < 0 || index >= arraylist_length(arraylist))
    {
        arraylist_err = AL_ERR_OUT_OF_BOUNDS;
        return arraylist;
    }
    size_t len = arraylist_length(arraylist);

    /*
     * Unsigned char is the smallest addressable size on any system. Every other
     * datatype must be some multiple of char. As such, we'll treat the
     * arraylist as an array of char, that way our pointer arithmetic works.
     */
    unsigned char *iter_array = arraylist;
    for(size_t i = index; i < len - 1; i++)
    {
        memcpy(iter_array + (i * arraylist_element_size(arraylist)),
               iter_array + ((i + 1) * arraylist_element_size(arraylist)),
               arraylist_element_size(arraylist));
    }

    /*
     * Temporarily create the "real" version of the array so we can update
     * values without too much bit fiddling
     */
    size_t *real_array = arraylist;
    real_array -= 3;
    real_array[0] -= 1;

    /*
     * If we fall below 1/4th of our capacity, it's time to halve the array to
     * save some memory.
     */
    if(real_array[0] <= real_array[1] / 4)
    {
        size_t new_size = arraylist_element_size(arraylist) *
                          (arraylist_capacity(arraylist) / 2) +
                          sizeof(size_t) * 3;
        size_t *new_arr = malloc(new_size);
        new_arr[0] = real_array[0];
        new_arr[1] = real_array[1] / 2;
        new_arr[2] = real_array[2];

        memcpy(new_arr + 3, real_array + 3, real_array[2] * real_array[0]);
        free(real_array);
        return new_arr + 3;
    }
    return arraylist;
}

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
        /* Double the array size you maggot */
        arr[1] *= 2;
        size_t new_size = arr[2] * arr[1] + sizeof(size_t) * 3;
        size_t *new_arr = malloc(new_size);
        new_arr[0] = arr[0];
        new_arr[1] = arr[1];
        new_arr[2] = arr[2];

        /* Copy the old elements */
        memcpy((void *) (new_arr + 3), array, arr[0] * arr[2]);

        /* Free the old data */
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

