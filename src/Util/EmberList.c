/*
 * Created by Aaron Helton on 11/15/19
 */
#include <EmberLib/Util/EmberList.h>
#include <stdlib.h>
#include <string.h>

int emberlist_err = 0;

void *INTERNAL_el_process_delete(void *emberlist, size_t index)
{
    if(index < 0 || index >= emberlist_length(emberlist))
    {
        emberlist_err = EL_ERR_OUT_OF_BOUNDS;
        return emberlist;
    }
    size_t len = emberlist_length(emberlist);

    /*
     * Unsigned char is the smallest addressable size on any system. Every other
     * datatype must be some multiple of char. As such, we'll treat the
     * emberlist as an array of char, that way our pointer arithmetic works.
     */
    unsigned char *list_iter = emberlist;
    for(size_t i = index; i < len - 1; i++)
    {
        memcpy(list_iter + (i * emberlist_element_size(emberlist)),
               list_iter + ((i + 1) * emberlist_element_size(emberlist)),
               emberlist_element_size(emberlist));
    }

    /*
     * Temporarily create the "real" version of the array so we can update
     * values without too much bit fiddling
     */
    size_t *real_list = emberlist;
    real_list -= 3;
    real_list[0] -= 1;

    /*
     * If we fall below 1/4th of our capacity, it's time to halve the array to
     * save some memory.
     */
    if(real_list[0] <= real_list[1] / 4)
    {
        size_t new_size = emberlist_element_size(emberlist) *
                          (emberlist_capacity(emberlist) / 2) +
                          sizeof(size_t) * 3;
        size_t *new_list = malloc(new_size);
        new_list[0] = real_list[0];
        new_list[1] = real_list[1] / 2;
        new_list[2] = real_list[2];

        memcpy(new_list + 3, real_list + 3, real_list[2] * real_list[0]);
        free(real_list);
        return new_list + 3;
    }
    return emberlist;
}

void INTERNAL_el_destroy_emberlist(void *list)
{
    free(((size_t *) list) - 3);
}

int INTERNAL_el_check_bounds(size_t index, size_t max)
{
    if(index >= max)
    {
        emberlist_err = EL_ERR_OUT_OF_BOUNDS;
        return 0;
    }
    return 1;
}

void *INTERNAL_preprocess_el_push(void *emberlist)
{
    size_t *list = (size_t *) (emberlist);
    list = list - 3;
    if(list[0] == list[1])
    {
        /* Double the list size */
        list[1] *= 2;
        size_t new_size = list[2] * list[1] + sizeof(size_t) * 3;
        size_t *new_list = malloc(new_size);
        new_list[0] = list[0];
        new_list[1] = list[1];
        new_list[2] = list[2];

        /* Copy the old elements */
        memcpy((void *) (new_list + 3), emberlist, list[0] * list[2]);

        /* Free the old data */
        free(list);
        return (void *) (new_list + 3);
    }
    return emberlist;
}

void *INTERNAL_create_generic_list(size_t element_size, size_t elements)
{
    size_t size = element_size * elements + sizeof(size_t) * 3;
    size_t *new_list = malloc(size);
    new_list[0] = 0;
    new_list[1] = elements;
    new_list[2] = element_size;
    memset(new_list + 3, 0, size - 3 * sizeof(size_t));
    return (void *) (new_list + 3);
}

