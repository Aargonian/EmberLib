/*
 * Created by Aaron Helton on 11/22/19
 */
#include <EmberLib/arraylist_new.h>
#include <stdio.h>

int main(void)
{
    int *array = init_arraylist(int);
    for(int i = 0; i < 100; i++)
    {
        arraylist_push(array, i);
        printf("Arraylist Length: %zu | ", arraylist_length(array));
        printf("Arraylist Capacity: %zu | ", arraylist_capacity(array));
        printf("Arraylist Memory: %zu\n", arraylist_memory_footprint(array));
    }
    destroy_arraylist(array);
}
