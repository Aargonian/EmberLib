#include <arraylist_new.h>
#include <stdio.h>

int main(void)
{
    char **array = NULL;
    init_arraylist(char *, array);
    for(int i = 0; i < 95+32; i++)
    {
        char *c = malloc(sizeof(char)*2);
        *c = (char)i;
        *(c+1) = '\0';
        arraylist_push(array, c);
        printf("Array Capacity: %zu, ", arraylist_capacity(array));
        printf("Array Size: %zu, ", arraylist_length(array));
        printf("Item at %d: %s\n", i, arraylist_get(array, i));
    }
    for(int i = 0; i < arraylist_length(array); i++)
    {
        free(arraylist_get(array, i));
    }
    char *test_str = "What The Fuck?\0";
    for(int i = -2; i < 3; i++)
    {
        printf("BEFORE ENTERING LOOP IS ARRAY ERR SET? %d\n", arraylist_err != 0);
        printf("ATTEMPTING TO INSERT %s INTO INDEX %d\n", test_str, i);
        arraylist_set(array, i, test_str);
        printf("ARRAY ERR SET? %d\n", arraylist_err != 0);
        printf("VALUE AT %d? %s\n", i, arraylist_get(array, i));
        printf("VALUE AT 0? %s\n", arraylist_get(array, 0) == '\0' ? NULL : arraylist_get(array, 0));
        printf("\n");
        clear_arraylist_err();
    }
    destroy_arraylist(array);
    return 0;
}
