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
    vec4 **array = init_arraylist(vec4 *);
    for(int i = 0; i < 100; i++)
    {
        vec4 *b = malloc(sizeof(vec4));
        b->x = i;
        b->y = i*2;
        b->z = i*i;
        b->w = my_pow(i, i);

        arraylist_push(array, b);
        vec4 *z = arraylist_get(array, i);
        printf("Vec4 at %d: [%llu, %llu, %llu, %llu]\n", i, z->x, z->y, z->z, z->w);
        printf("Memory Footprint: %zu\n", arraylist_memory_footprint(array));
    }
    printf("Information of Note:\n");
    printf("Size Of Vec4: %zu\n", sizeof(vec4));
    printf("Size of Pointer To Vec4: %zu\n", sizeof(vec4 *));
    printf("Size Of Size_T: %zu\n", sizeof(size_t));
    printf("Size if we just use pointers: %zu\n", sizeof(vec4 *)*arraylist_length(array) + sizeof(size_t)*3);
    printf("Size if we use struct: %zu\n", sizeof(vec4)*arraylist_length(array) + sizeof(size_t)*3);
    destroy_arraylist(array);
    return 0;
}
