/*
 * Created by Aaron Helton on 11/22/19
 */
#include <EmberLib/Util/EmberList.h>
#include <EmberLib/Util/BitArray.h>
#include <EmberLib/IO/EmberFile.h>
#include <stdio.h>

/* TEMPORARY */
#include <stdlib.h>
#include <time.h>

void print_bitarray(BitArray *array)
{
    for(uint32 i = 0; i < ebitarray_size(array); i++)
    {
        printf("%d", ebitarray_get(array, i) ? 1 : 0);
    }
    printf("\n");
}

#include <EmberLib/Util/EmberTimer.h>
int main(void)
{
    for(int i = 0; i < 3; i++)
    {
        srand(771996);

        double start = get_time();
        for(int i = 0; i < 10000000; i++)
        {
            BitArray *array = ebitarray_create(1024);

            // set a random bit some random number of times
            int times = 100;
            for(int j = 0; j < times; j++)
            {
                uint32 index = rand() % 32;
                uint8 value = rand() & 1;
                ebitarray_set(array, index, value);
            }

            ebitarray_destroy(array);
            array = NULL;
        }
        double end = get_time();

        printf("Elapsed Time: %f\n", end - start);
    }
}
