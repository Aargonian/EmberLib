#include <arraylist_new.h>
#include <stdio.h>

int main(void)
{
    double x = 3.4;
    int *array = init_arraylist(int);
    for(int i = 0; i < 5; i++)
    {
        arraylist_push(array, x);
    }
    return 0;
}
