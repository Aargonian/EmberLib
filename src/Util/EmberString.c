/*
 * Created by Aaron Gorodetzky on 12/10/2019
 */

#include <EmberLib/Util/EmberString.h>
#include <stdlib.h>

static EmberStringError error_val;

EmberStringError ember_string_error(void)
{
    return error_val;
}

void clear_ember_string_error(void)
{
    error_val = EMBER_STRING_NO_ERR;
}

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
        if(str->c_str)
        {
            free(str->c_str);
            str->c_str = NULL;
        }
        str->c_str = 0;
    }
    free(str);
}

static int is_whitespace(char c)
{
    if(c == ' ' || c == '\t' || c == '\n' || c == '\v')
    {
        return 1;
    }
    return 0;
}

EmberString *strip_estring(EmberString *str)
{
    //Sanity check
    if(!str || !str->c_str || str->len == 0)
    {
        return str;
    }
    //Strip the left side
    size_t lstrip_index = 0;
    for(size_t index = 0; index < str->len; index++)
    {
        if(is_whitespace(str->c_str[index]))
        {
            lstrip_index++;
        }
        else
        {
            break;
        }
    }

    //Find right side strip index
    size_t rstrip_index = str->len;
    for(size_t index = str->len - 1; index >= 0; index--)
    {
        if(is_whitespace(str->c_str[index]))
        {
            rstrip_index--;
        }
        else
        {
            break;
        }
    }

    if(lstrip_index == rstrip_index)
    {
        free(str->c_str);
        str->c_str = NULL;
        str->len = 0;
    }
    else
    {
        size_t chop_off = lstrip_index + (str->len - rstrip_index);
        char *new = malloc(sizeof(char) * (str->len - chop_off + 1));
        for(size_t index = lstrip_index; index < rstrip_index; index++)
        {
            new[index - lstrip_index] = str->c_str[index];
        }
        new[rstrip_index - lstrip_index] = '\0';
        free(str->c_str);
        str->c_str = new;
        str->len -= chop_off;
    }
    return str;
}

/*
 * This function takes advantage of the fact that in ASCII, a-z and A-Z are
 * always 32 values apart. This will NOT work for other character sets, but few
 * systems use anything other than ASCII and Unicode. This happens to work with
 * Unicode characters as well, but that is merely a happy accident of the spec.
 *
 * If compiling on a EBCDIC system or anything else that uses a different
 * default character encoding, you'll need to either chance this code or
 * re-encode all text.
 */
static char lowercase(char c)
{
    if(c < 'A' || c > 'Z')
    {
        return c;
    }
    return (char) (c + 32);
}

int compare_estring(const EmberString *str, const EmberString *other)
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