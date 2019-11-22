#include <arraylist_new.h>
#include <stdio.h>

int main(void)
{
    char *s = "What";
    double x = 3.4;
    int *array = init_arraylist(int);
    for(int i = 0; i < 5; i++)
    {
        arraylist_push(array, s);
    }
    return 0;
}
