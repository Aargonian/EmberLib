#include <stdlib.h>

#include <EmberLib/Util/BitArray.h>

struct BitArrayImpl
{
    char *data;
    uint32 bits;
};

BitArray *ebitarray_create(uint32 size)
{
    //Round up size to the nearest multiple of 8
    if(size % 8 != 0)
    {
        size += 8 - (size % 8);
    }
    BitArray *array = malloc(sizeof(BitArray));
    array->bits = size;
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
    //TODO: Alter this for machines where bytes are != 8 bits
    uint8 failure = 0;
    if(end > array->bits) return -1;
    if(!array) return -2;
    while(!(start % 8 == 0) && start != end)
    {
        if((failure = ebitarray_set(array, start++, value)))
        {
            return failure;
        }
    }
    //Start is guaranteed to be byte aligned
    uint32 byte = start/8;
    uint8 byte_val = value ? 0xFFu : 0x00u;
    while(end - start >= 8)
    {
        array->data[byte++] = byte_val;
        start+=8;
    }
    while(start != end && !failure)
    {
        failure = ebitarray_set(array, start++, value);
    }
    return failure;
}

int8 ebitarray_set(BitArray *array, uint32 index, ebool value)
{
    if(index >= array->bits) return -1;
    uint32 byte = index/8;
    uint8 pos = index%8;

    if(value)
        array->data[byte] |= (1u << pos);
    else
        array->data[byte] &= (0xFF - (1u << pos));
    return 0;
}

ebool ebitarray_get(BitArray *array, uint32 index)
{
    uint32 byte = index/8;
    uint8 bit = index%8;
    return array->data[byte] & (1u << bit);
}

uint32 ebitarray_size(BitArray *array)
{
    return array->bits;
}
