/*
 * Created by Aaron Gorodetzky on 12/10/2019
 */

#ifndef EMBERLIB_EMBERSTRING_H
#define EMBERLIB_EMBERSTRING_H

#include <stdlib.h>


/**
 * EmberString is used to make using stanard, ascii-based character arrays much
 * easier to handle than just raw char *. This structure is not intended for use
 * with Unicode characters.
 */
typedef struct EmberString
{
    char *c_str;
    size_t len;
} EmberString;

/**
 * Takes as input a standard C-style string and converts it to an EmberString.
 * The function will return if either a Null byte is encountered, or the
 * max_buffer is encountered.
 *
 * @param str The c-str to turn into an EmberString.
 * @param max_buffer
 * @return an EmberString containing the c_str and the length.
 */
EmberString *create_estring_from_cstr(const char *str, size_t max_len);

/**
 * Free the allocated data from an EmberString. NULL is an acceptable input.
 * @param str The EmberString to free.
 */
void destroy_estring(EmberString *str);

/**
 * Creates a modified version of the original EmberString, with the
 * whitespace on the left and right-hand side of the string removed.
 * @param str The EmberString to strip whitespace from
 * @return A modified version of the input string with whitespaced trimmed.
 */
EmberString *strip_estring(EmberString *str);

/**
 * Compares two EmberStrings to determine correct alphabetical ordering.
 * @param str The first string to compare
 * @param other The other string to compare
 * @return -1 if the first argument is less than, 1 if greater, 0 if equal
 */
int compare_estring(const EmberString *str, const EmberString *other);

/**
 * Concatenates two EmberStrings into a new EmberString. If one or both strings
 * are NULL, ember_string_error will be set to EMBER_STRING_NULL_ARG. In the
 * case of null arguments, if only one string is null, it will return a new
 * EmberString that is essentially just the non-null string. If both strings are
 * NULL, it will return a valid, but empty, EmberString.
 *
 * @param str The first string to concatenate.
 * @param other The second string to concatenate.
 * @return A string that is the concatenation of both input strings.
 */
EmberString *estring_concat(EmberString *str, EmberString *other);

/*
 * Error Handling Stuff
 */

/**
 * Simple enum defining the various errors that can be set by string functions.
 */
typedef enum EmberStringError {
    EMBER_STRING_NO_ERR = 0,
    EMBER_STRING_NULL_ARG,
    EMBER_STRING_INVALID_LEN,
    EMBER_STRING_TRUNCATED,
} EmberStringError;

/**
 * Returns any error that may have been set by the library by a previous string
 * operations. Valid errors can be seen in the EmberStringError enum.
 * @return Any error code in EmberStringError, or EMBER_STRING_NO_ERR.
 */
EmberStringError ember_string_error(void);

/**
 * Clears any currently set errors in EmberStringError.
 */
void clear_ember_string_error(void);

#endif //EMBERLIB_EMBERSTRING_H
