/*
 * Created by Aaron Gorodetzky on 12/10/2019
 *
 * EmberString is used to make using standard, ascii-based character arrays much
 * easier to handle than just raw char *. The functions and structures
 * defined here are not intended to be used for Unicode characters or any other
 * character set.
 */

#ifndef EMBERLIB_EMBERSTRING_H
#define EMBERLIB_EMBERSTRING_H

#include <stdlib.h>

/*
 * EmberString definition.
 */
typedef struct EmberString
{
    char *c_str;
    size_t len;
} EmberString;

/*******************************************************************************
 * Construction and Destruction Functions
 ******************************************************************************/

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

/*******************************************************************************
 * Error Handling Definitions and Functions
 ******************************************************************************/
/**
 * Simple enum defining the various errors that can be set by string functions.
 */
typedef enum EmberStringError
{
    EMBER_STRING_NO_ERR = 0,
    EMBER_STRING_NULL_ARG,
    EMBER_STRING_INVALID_LEN,
    EMBER_STRING_TRUNCATED,
    EMBER_STRING_OUT_OF_BOUNDS,
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

/*******************************************************************************
 * Utility Functions
 ******************************************************************************/

/**
 * Returns a substring of the passed string from inclusive start to exclusive
 * end. If the end index is less than the start index, or either index is
 * negative or exceeds the bounds of the array then a NULL ptr will be returned
 * and ember_string_error will be set to EMBER_STRING_OUT_OF_BOUNDS. If the
 * EmberString passed is NULL then it will also return a NULL ptr and set
 * EMBER_STRING_NULL_ARG.
 *
 * @param str The string to create the substring from.
 * @param start The (inclusive) start index of the substring.
 * @param end The (exclusive) end index of the substring.
 * @return A substring containing the same characters of the original string
 *         from start to end, or NULL if an error is encountered.
 */
EmberString *estring_substring(const EmberString *str, size_t start,
                               size_t end);
#endif //EMBERLIB_EMBERSTRING_H

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

/**
 * Creates a modified version of the original EmberString, with the
 * whitespace on the left and right-hand side of the string removed.
 * @param str The EmberString toember_substring strip whitespace from
 * @return A modified version of the input string with whitespaced trimmed.
 */
EmberString *estring_strip(EmberString *str);

/**
 * Compares two EmberStrings to determine correct alphabetical ordering.
 * Uppercase characters are considered less than uppercase characters.
 * @param str The first string to compare
 * @param other The other string to compare
 * @return -1 if the first argument is less than, 1 if greater, 0 if equal
 */
int estring_compare_with_case(const EmberString *str, const EmberString *other);

/**
 * Compares two EmberStrings to determine correct alphabetical ordering. Case
 * does not matter.
 * @param str The first string to compare
 * @param other The other string to compare
 * @return -1 if the first argument is less than, 1 if greater, 0 if equal
 */
int estring_compare(const EmberString *str, const EmberString *other);
