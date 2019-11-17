#include <arraylist_new.h>
#include <stdio.h>

typedef struct _point {
    int x;
    int y;
} point;

int main(void)
{
    point *array = init_arraylist(point);
    printf("Information of Note:\n");
    printf("Size Of Point: %zu\n", sizeof(point));
    printf("Size Of Size_T: %zu\n", sizeof(size_t));
    for(int i = 0; i < 100; i++)
    {
        point b = {i, 2*i};
        arraylist_push(array, b);
        point z = arraylist_get(array, i);
        printf("Point at %d: [%d, %d]\n", i, z.x, z.y);
        printf("Memory Footprint: %zu\n", arraylist_memory_footprint(array));
    }
    destroy_arraylist(array);
    return 0;
}
