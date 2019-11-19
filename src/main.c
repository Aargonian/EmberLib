#include <arraylist_new.h>
#include <stdio.h>

typedef struct _vec4 {
    unsigned long long x;
    unsigned long long y;
    unsigned long long z;
    unsigned long long w;
} vec4;

unsigned long long my_pow(int base, int power)
{
    unsigned long long val = base;
    if(power == 0)
        return 1;
    if(power == 1)
        return base;
    for(int i = 0; i < power-1; i++)
        val = val * base;
    return val;
}

int main(void)
{
    int *array = init_arraylist(int);
    for(size_t i = 0; i < 100; i++)
    {
        arraylist_push(array, i);
        if(arraylist_err)
        {
            printf("ArrayList Error Found: %d\n", arraylist_err);
            printf("Attempted to access: %zu\n", i);
            clear_arraylist_err()
        }
    }
    for(size_t i = 0; i < 105; i++)
    {
        printf("ArrayList Value At %zu: %d\n", i, arraylist_get(array, i, -1));
        if(arraylist_err)
        {
            printf("ArrayList Error Found: %d\n", arraylist_err);
            printf("Attempted to access: %zu\n", i);
            clear_arraylist_err()
        }
    }
    destroy_arraylist(array);
}
