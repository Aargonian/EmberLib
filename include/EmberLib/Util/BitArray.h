#ifndef EMBER_BIT_FIELD_H
#define EMBER_BIT_FIELD_H

#include <EmberLib/Util/EmberDefines.h>

typedef struct BitArrayImpl BitArray;

/*
 * Creates a managed bit array of (size) bytes. Bytes will be of native machine size.
 */
BitArray *ebitarray_create(uint32 size);

/*
 * Sets a range of bits to the same value
 */
int8 ebitarray_set_range(BitArray *array, uint32 start, uint32 end, ebool value);

/*
 * Set a particular bit in the array
 */
int8 ebitarray_set(BitArray *array, uint32 index, ebool value);

/*
 * Destroy the bitarray
 */
void ebitarray_destroy(BitArray *array);

/*
 * Retrieve the value of a particular bit
 */
ebool ebitarray_get(BitArray *array, uint32 index);

/*
 * Retrieve the size of the array
 */
uint32 ebitarray_size(BitArray *array);

#endif//EMBER_BIT_FIELD_H
