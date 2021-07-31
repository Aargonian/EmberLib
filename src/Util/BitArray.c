#include <stdlib.h>
#include <string.h>

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

/*
 * @brief Unsafe version of the ebitarray_set that assumes the index is in-bounds and the bitval is 1 or 0.
 */
void ebitarray_set_unsafe(BitArray *array, uint32 index, ebool bitval)
{
    uint32 byte = index >> 3; /* index/8 */
    uint8 pos = index & 0x07; /* index%8 */
    array->data[byte] ^= (-bitval ^ array->data[byte]) & (0x01u << pos);
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

//TODO: Real error codes plz?
//TODO: Alter this for machines where bytes are != 8 num_bits
int8 ebitarray_set_range(BitArray *array, uint32 start, uint32 end, ebool value)
{
    // Sanity Check
    if(!array) return -1;
    if(end > array->num_bits) return -2;

    value = (value != 0); // Force value to 1 or 0
    while(start % 8 != 0 && start <= end)
    {
        ebitarray_set_unsafe(array, start++, value);
    }

    //Start is guaranteed to be byte aligned
    const uint32 start_byte = start >> 3; // start/8
    const uint32 end_byte = end >> 3; // end/8
    uint8 byte_val = value ? 0xFFu : 0x00u;
    memset(array->data + start_byte, byte_val, end_byte-start_byte);
    while(start <= end)
    {
        ebitarray_set_unsafe(array, start++, value);
    }
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
