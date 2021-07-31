#include <stdlib.h>

#include <EmberLib/Util/BitArray.h>

struct BitArrayImpl
{
    unsigned char *data;
    uint32 num_bits;
};

BitArray *ebitarray_create(uint32 size)
{
    //Round up size to the nearest multiple of 8
    if(size % 8 != 0)
    {
        size += 8 - (size % 8);
    }
    BitArray *array = malloc(sizeof(BitArray));
    array->num_bits = size;
    array->data = malloc(sizeof(char) * (size/8));
    for(uint32 i = 0; i < size/8; i++)
    {
        array->data[i] = 0;
    }
    return array;
}

void ebitarray_destroy(BitArray *array)
{
    if(array)
    {
        if(array->data)
        {
            free(array->data);
            array->data = NULL;
        }
        free(array);
    }
}

//TODO: Real error codes plz?
int8 ebitarray_set_range(BitArray *array, uint32 start, uint32 end, ebool value)
{
    //TODO: Alter this for machines where bytes are != 8 num_bits
    int8 failure = 0;
    if(!array) return -1;
    if(end > array->num_bits) return -2;
    while(start % 8 != 0 && start <= end)
    {
        failure = ebitarray_set(array, start++, value);
        if(failure)
            return failure;
    }

    //Start is guaranteed to be byte aligned
    uint32 byte = start/8;
    uint8 byte_val = value ? 0xFFu : 0x00u;
    while(end - start >= 8)
    {
        array->data[byte++] = byte_val;
        start+=8;
    }
    while(start <= end && !failure)
    {
        failure = ebitarray_set(array, start++, value);
    }
    return failure;
}

/*
 * @brief Unsafe version of the ebitarray_set that assumes the index is in-bounds and the bitval is 1 or 0.
 */
void ebitarray_set_unsafe(BitArray *array, uint32 index, ebool bitval)
{
    uint32 byte = index >> 3; /* index/8 */
    uint8 pos = index & 0x07; /* index%8 */
    array->data[byte] ^= (-bitval ^ array->data[byte]) & (0x01u << pos);
    /*
     *  The above should be equivalent to the following code, but faster. It should also work equivalently on a one or two's compliment system
     *  TODO: Benchmark the above code with the following and possibly change depending on compiler/system
     *    if(value)
     *        array->data[byte] |= (1u << pos);
     *    else
     *        array->data[byte] &= (0xFF - (1u << pos));
     */
}

/*
 * @brief Set a bit in the BitArray to 0 or 1. Bounds checking is enabled.
 */
int8 ebitarray_set(BitArray *array, uint32 index, ebool value)
{
    if(index >= array->num_bits)
        return -1;
    value = (value != 0); // Force value to 1 or 0
    ebitarray_set_unsafe(array, index, value);
    return 0;
}

ebool ebitarray_get(BitArray *array, uint32 index)
{
    uint32 byte = index >> 3; /* index/8 */
    uint8 pos = index & 0x07; /* index%8 */
    return array->data[byte] & (1u << pos);
}

uint32 ebitarray_size(BitArray *array)
{
    return array->num_bits;
}
