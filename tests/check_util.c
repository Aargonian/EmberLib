//
// Created by Aaron Helton on 11/24/19.
//
#include <stdio.h>
#include "check_util.h"

void init_test_struct(check_struct *cs, size_t i)
{
    cs->_test_char = (char) i;
    cs->_test_unsigned_char = (unsigned char) i;
    cs->_test_short = i;
    cs->_test_unsigned_short = i;
    cs->_test_int = i;
    cs->_test_unsigned_int = 9;
    cs->_test_long = i;
    cs->_test_unsigned_long = i;
    cs->_test_long_long = i;
    cs->_test_unsigned_long_long = i;
    cs->_test_float = (float) i;
    cs->_test_double = (double) i;
    cs->_test_long_double = (long double) i;
    cs->_test_str = "a";
    cs->_test_void_ptr = (void *) i;
}

int struct_equal(check_struct *cs, check_struct *other, char *msg)
{
    if(cs->_test_char != other->_test_char)
    {
        snprintf(msg, __EL_MAX_MESSAGE_LENGTH,
                 "cs->_test_char = %c, other->_test_char = %c\n", cs->_test_char, other->_test_char);
        return 0;
    }
    if(cs->_test_int != other->_test_int)
    {
        printf("cs->_test_int = %d, other->_test_int = %d\n", cs->_test_int, other->_test_int);
        return 0;
    }
    if(cs->_test_long != other->_test_long)
    {
        printf("cs->_test_long = %ld, other->_test_long = %ld\n", cs->_test_long, other->_test_long);
        return 0;
    }

    //Handle strings with special care
    if(cs->_test_str == NULL)
    {
        if(other->_test_str != NULL)
        {
            snprintf(msg, __EL_MAX_MESSAGE_LENGTH, "cs->_test_str = NULL, other->_test_str = %s\n", other->_test_str);
            return 0;
        }
    }
    else if(other->_test_str == NULL)
    {
        snprintf(msg, __EL_MAX_MESSAGE_LENGTH, "cs->_test_str = %s, other->_test_str = NULL\n", cs->_test_str);
        return 0;
    }
    else if(strcmp(cs->_test_str, other->_test_str) != 0)
    {
        printf("cs->_test_str = %s, other->_test_str = %s\n", cs->_test_str, other->_test_str);
        return 0;
    }
    return 1;
}
