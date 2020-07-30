/*
 * Created by Aaron Helton on 11/22/19
 */
#include <EmberLib/Util/EmberList.h>
#include <EmberLib/Util/BitArray.h>
#include <EmberLib/IO/EmberFile.h>
#include <stdio.h>

void print_bitarray(BitArray *array)
{
    for(uint32 i = 0; i < ebitarray_size(array); i++)
    {
        printf("%d", ebitarray_get(array, i) ? 1 : 0);
    }
    printf("\n");
}

int main(void)
{
    BitArray *array = ebitarray_create(32);
    printf("Current Array: ");
    print_bitarray(array);

    ebitarray_set(array, 1, 1);
    printf("After setting bit pos 1 to 1: ");
    print_bitarray(array);

    ebitarray_set(array, 1, 0);
    printf("After setting bit pos 1 to 1: ");
    print_bitarray(array);

    ebitarray_set(array, 1, 20);
    printf("After setting bit pos 1 to 20: ");
    print_bitarray(array);

    ebitarray_set_range(array, 10, 20, 1);
    printf("After setting bits 10-20 to 1: ");
    print_bitarray(array);

    ebitarray_set_range(array, 10, 20, 0);
    printf("After setting bits 10-20 to 0: ");
    print_bitarray(array);

    ebitarray_destroy(array);
    return 0;
}
