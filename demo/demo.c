/*
 * Created by Aaron Helton on 11/22/19
 */
#include <EmberLib/Util/EmberList.h>
#include <stdio.h>

int main(void)
{
    int *array = emberlist_create(int);
    for(int i = 0; i < 100; i++)
    {
        emberlist_push(array, i);
        printf("Arraylist Length: %zu | ", emberlist_length(array));
        printf("Arraylist Capacity: %zu | ", emberlist_capacity(array));
        printf("Arraylist Memory: %zu\n", emberlist_memory_footprint(array));
    }
    emberlist_destroy(array);
}
