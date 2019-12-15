/*
 * Created by Aaron Gorodetzky on 12/10/2019
 */

#include <EmberLib/Util/EmberString.h>
#include <stdlib.h>

/*******************************************************************************
 * Static Helper Functions
 ******************************************************************************/
static EmberStringError error_val;

static char lowercase(char c)
{
    if(c < 'A' || c > 'Z')
    {
        return c;
    }
    return (char) (c + 32);
}

static int is_whitespace(char c)
{
    if(c == ' ' || c == '\t' || c == '\n' || c == '\v')
    {
        return 1;
    }
    return 0;
}

/*******************************************************************************
 * String creation and destruction functions
 ******************************************************************************/

EmberString *create_estring_from_cstr(const char *str, size_t max_buffer)
{
    EmberString *new_str = (EmberString *) malloc(sizeof(EmberString));
    if(!str)
    {
        error_val = EMBER_STRING_NULL_ARG;
        new_str->c_str = malloc(sizeof(char));
        new_str->c_str[0] = '\0';
        new_str->len = 0;
        return new_str;
    }

    size_t index; //Declare outside of loop for reuse
    size_t size = 0;
    for(index = 0; index < max_buffer && str[index] != '\0'; index++)
    {
        size++;
    }

    if(index == max_buffer && str[index] != '\0')
    {
        error_val = EMBER_STRING_TRUNCATED;
    }

    //Make sure to +1 for the null byte at the end
    new_str->c_str = (char *) malloc(sizeof(char) * size + 1);
    for(index = 0; index < size && *str != '\0'; index++)
    {
        new_str->c_str[index] = str[index];
    }
    new_str->c_str[index] = '\0';
    new_str->len = index; //Note that len does not include the null byte
    return new_str;
}

void destroy_estring(EmberString *str)
{
    if(str)
    {
        free(str->c_str);
        str->c_str = NULL;
    }
    free(str);
}

/*******************************************************************************
 * Error Handling
 ******************************************************************************/

EmberStringError ember_string_error(void)
{
    return error_val;
}

void clear_ember_string_error(void)
{
    error_val = EMBER_STRING_NO_ERR;
}

/*******************************************************************************
 * Utility Functions
 ******************************************************************************/

EmberString *estring_substring(EmberString *str, size_t start, size_t end)
{
    if(!str || !str->c_str)
    {
        error_val = EMBER_STRING_NULL_ARG;
        return NULL;
    }
    if(end < start || end > str->len || start < 0)
    {
        error_val = EMBER_STRING_OUT_OF_BOUNDS;
        return NULL;
    }

    EmberString *ret = malloc(sizeof(EmberString));
    ret->len = end-start;
    ret->c_str = malloc(sizeof(char)*ret->len);

    for(size_t i = 0; i < ret->len; i++)
    {
        ret->c_str[i] = str->c_str[start+i];
    }
    ret->c_str[ret->len] = '\0';

    return ret;
}

EmberString *estring_concat(EmberString *str, EmberString *other)
{
    if(str == NULL)
    {
        error_val = EMBER_STRING_NULL_ARG;
        if(!other)
        {
            return create_estring_from_cstr("", 0);
        }
        return create_estring_from_cstr(other->c_str, other->len);
    }
    if(other == NULL)
    {
        error_val = EMBER_STRING_NULL_ARG;
        return create_estring_from_cstr(str->c_str, str->len);
    }

    EmberString *result = malloc(sizeof(EmberString));
    result->len = str->len + other->len;
    result->c_str = malloc(sizeof(char) * (result->len + 1));

    for(size_t i = 0; i < str->len; i++)
    {
        result->c_str[i] = str->c_str[i];
    }
    for(size_t i = str->len; i < other->len+str->len; i++)
    {
        result->c_str[i] = other->c_str[i-str->len];
    }
    result->c_str[result->len] = '\0';
    return result;
}

#include <stdio.h>
EmberString *estring_strip(EmberString *str)
{
    //Sanity check
    if(!str || !str->c_str)
    {
        error_val = EMBER_STRING_NULL_ARG;
        return NULL;
    }
    if(str->len == 0)
    {
        EmberString *ret = malloc(sizeof(EmberString));
        ret->c_str = malloc(sizeof(char));
        ret->c_str[0] = '\0';
        ret->len = 0;
        return ret;
    }

    size_t left = 0;
    size_t right = str->len-1;

    for(; left < str->len && is_whitespace(str->c_str[left]); left++);
    for(; right > left && is_whitespace(str->c_str[right]); right--);

    return estring_substring(str, left, right+1);
}

int estring_compare(const EmberString *str, const EmberString *other)
{
    size_t min_len = str->len < other->len ? str->len : other->len;
    for(size_t index = 0; index < min_len; index++)
    {
        char str_lower_char = lowercase(str->c_str[index]);
        char other_lower_char = lowercase(other->c_str[index]);
        if(str_lower_char < other_lower_char)
        {
            return -1;
        }
        else if(str_lower_char > other_lower_char)
        {
            return 1;
        }
    }

    //Only difference is length
    if(str->len < other->len)
    {
        return -1;
    }
    else if(str->len > other->len)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


