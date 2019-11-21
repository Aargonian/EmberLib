#include <arraylist_new.h>
#include <stdio.h>

int main(void)
{
    double x = 3.4;
    int *array = init_arraylist(int);
    arraylist_push(array, x);
    int index = -2;
    arraylist_get(array, index, -1);
    destroy_arraylist(array);
    return 0;
}
