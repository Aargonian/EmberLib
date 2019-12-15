/*
 * Created by Aaron Helton on 11/22/19
 */
#include <EmberLib/Util/EmberString.h>
#include <stdlib.h>
#include <check.h>

START_TEST(test_ember_string_from_cstr)
{
    char *TEST_STR_1 = "Test_String_One";
    char *TEST_STR_2 = "TEST STRING TOO LONG";
    char *TEST_STR_TRUNCATED = "TEST STRIN";
    size_t TEST_STR_TRUNCATED_LEN = 10;
    size_t TEST_STR_1_LEN = 15;

    EmberString *str = create_estring_from_cstr(TEST_STR_1, TEST_STR_1_LEN);

    /*
     * We should be able to create a string from a standard c-string with no
     * issues. The length should include all characters minus the null byte.
     * The two strings should have no differences.
     */
    ck_assert_ptr_nonnull(str);
    ck_assert_ptr_nonnull(str->c_str);
    ck_assert_uint_eq(str->len, TEST_STR_1_LEN);
    ck_assert_str_eq(TEST_STR_1, str->c_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(str);

    /*
     * Attempt to use a buffer that is far too large. The resulting length
     * should be no more than the length of the string, regardless. Null padding
     * does not occur.
     */
    str = create_estring_from_cstr(TEST_STR_1, TEST_STR_1_LEN*1000);
    ck_assert_ptr_nonnull(str);
    ck_assert_ptr_nonnull(str->c_str);
    ck_assert_uint_eq(str->len, TEST_STR_1_LEN);
    ck_assert_str_eq(TEST_STR_1, str->c_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(str);

    /*
     * Attempt to create an "empty" EmberString.
     */
    str = create_estring_from_cstr("", 0);
    ck_assert_ptr_nonnull(str);
    ck_assert_ptr_nonnull(str->c_str);
    ck_assert_uint_eq(str->len, 0);
    ck_assert_str_eq(str->c_str, "");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(str);

    /*
     * Attempt to create a string with a NULL ptr. The string should
     * technically be a valid, but empty, string. This should set an error
     * EMBER_STRING_NULL_ARG.
     */
    str = create_estring_from_cstr(NULL, 0);
    ck_assert_ptr_nonnull(str);
    ck_assert_ptr_nonnull(str->c_str);
    ck_assert_uint_eq(str->len, 0);
    ck_assert_str_eq(str->c_str, "");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NULL_ARG);
    clear_ember_string_error();
    destroy_estring(str);

    /*
     * Attempt to create a string, but with a buffer length smaller than the
     * total string length. This should truncate the string, but it should still
     * end with a NULL byte, and the length should equal the max buffer length.
     */
    str = create_estring_from_cstr(TEST_STR_2, TEST_STR_TRUNCATED_LEN);
    ck_assert_ptr_nonnull(str);
    ck_assert_ptr_nonnull(str->c_str);
    ck_assert_uint_eq(str->len, TEST_STR_TRUNCATED_LEN);
    ck_assert_str_eq(str->c_str, TEST_STR_TRUNCATED);
    ck_assert_str_ne(str->c_str, TEST_STR_2);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_TRUNCATED);
    clear_ember_string_error();
    destroy_estring(str);
}
END_TEST

START_TEST(test_ember_string_concat)
{
    EmberString *str1 = create_estring_from_cstr("String1", 7);
    EmberString *str2 = create_estring_from_cstr("String2", 7);
    EmberString *empty = create_estring_from_cstr("", 0);
    EmberString *null_str = NULL;

    EmberString *result = estring_concat(str1, str2);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_nonnull(result->c_str);
    ck_assert_ptr_ne(result->c_str, str1->c_str);
    ck_assert_ptr_ne(result->c_str, str2->c_str);
    ck_assert_int_eq(result->len, str1->len+str2->len);
    ck_assert_str_eq(result->c_str, "String1String2");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(result);

    result = estring_concat(str2, str1);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_nonnull(result->c_str);
    ck_assert_ptr_ne(result->c_str, str1->c_str);
    ck_assert_ptr_ne(result->c_str, str2->c_str);
    ck_assert_int_eq(result->len, str1->len+str2->len);
    ck_assert_str_eq(result->c_str, "String2String1");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(result);

    result = estring_concat(str1, empty);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_nonnull(result->c_str);
    ck_assert_ptr_ne(result->c_str, str1->c_str);
    ck_assert_ptr_ne(result->c_str, empty->c_str);
    ck_assert_int_eq(result->len, str1->len);
    ck_assert_str_eq(result->c_str, "String1");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(result);

    result = estring_concat(str1, null_str);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_nonnull(result->c_str);
    ck_assert_ptr_ne(result->c_str, str1->c_str);
    ck_assert_ptr_ne(result->c_str, empty->c_str);
    ck_assert_int_eq(result->len, str1->len);
    ck_assert_str_eq(result->c_str, "String1");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NULL_ARG);
    clear_ember_string_error();
    destroy_estring(result);

    result = estring_concat(null_str, str2);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_nonnull(result->c_str);
    ck_assert_ptr_ne(result->c_str, str2->c_str);
    ck_assert_ptr_ne(result->c_str, empty->c_str);
    ck_assert_int_eq(result->len, str1->len);
    ck_assert_str_eq(result->c_str, "String2");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NULL_ARG);
    clear_ember_string_error();
    destroy_estring(result);

    result = estring_concat(null_str, null_str);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_nonnull(result->c_str);
    ck_assert_int_eq(result->len, empty->len);
    ck_assert_str_eq(result->c_str, empty->c_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NULL_ARG);
    clear_ember_string_error();
    destroy_estring(result);

    result = estring_concat(empty, empty);
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_nonnull(result->c_str);
    ck_assert_ptr_ne(result->c_str, empty->c_str);
    ck_assert_int_eq(result->len, empty->len);
    ck_assert_str_eq(result->c_str, empty->c_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    clear_ember_string_error();

    destroy_estring(str1);
    destroy_estring(str2);
    destroy_estring(empty);
    destroy_estring(result);
}
END_TEST

START_TEST(test_ember_substring)
{
    EmberString *str = create_estring_from_cstr("TestString", 10);
    EmberString *empty = create_estring_from_cstr("", 0);

    /* Standard Substring Tests */
    EmberString *test_str = estring_substring(str, 0, 4);
    ck_assert_ptr_nonnull(test_str);
    ck_assert_ptr_nonnull(test_str->c_str);
    ck_assert_ptr_ne(test_str, str);
    ck_assert_ptr_ne(test_str->c_str, str->c_str);
    ck_assert_int_eq(test_str->len, 4);
    ck_assert_str_eq(test_str->c_str, "Test");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(test_str);

    test_str = estring_substring(str, 4, str->len);
    ck_assert_ptr_nonnull(test_str);
    ck_assert_ptr_nonnull(test_str->c_str);
    ck_assert_ptr_ne(test_str, str);
    ck_assert_ptr_ne(test_str->c_str, str->c_str);
    ck_assert_int_eq(test_str->len, str->len-4);
    ck_assert_str_eq(test_str->c_str, "String");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(test_str);

    /*
     * If the span of the indices happens to be the whole string, the effect
     * should be the same as a copy.
     */
    test_str = estring_substring(str, 0, str->len);
    ck_assert_ptr_nonnull(test_str);
    ck_assert_ptr_nonnull(test_str->c_str);
    ck_assert_ptr_ne(test_str, str);
    ck_assert_ptr_ne(test_str->c_str, str->c_str);
    ck_assert_int_eq(test_str->len, str->len);
    ck_assert_str_eq(test_str->c_str, str->c_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(test_str);

    /*
     * If both indices are the same, the result should be an empty string.
     */
    test_str = estring_substring(str, 0, 0);
    ck_assert_ptr_nonnull(test_str);
    ck_assert_ptr_nonnull(test_str->c_str);
    ck_assert_ptr_ne(test_str, str);
    ck_assert_ptr_ne(test_str->c_str, str->c_str);
    ck_assert_int_eq(test_str->len, empty->len);
    ck_assert_str_eq(test_str->c_str, empty->c_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(test_str);

    /*
     * Taking a substring of the empty string is possible, if both indices are 0
     */
    test_str = estring_substring(empty, 0, 0);
    ck_assert_ptr_nonnull(test_str);
    ck_assert_ptr_nonnull(test_str->c_str);
    ck_assert_ptr_ne(test_str, empty);
    ck_assert_ptr_ne(test_str->c_str, empty->c_str);
    ck_assert_int_eq(test_str->len, empty->len);
    ck_assert_str_eq(test_str->c_str, empty->c_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(test_str);

    /* NULL strings are never valid arguments */
    test_str = estring_substring(NULL, 0, 0);
    ck_assert_ptr_null(test_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NULL_ARG);
    clear_ember_string_error();

    /* The ending index should always be within the bounds */
    test_str = estring_substring(str, 0, str->len + 1);
    ck_assert_ptr_null(test_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_OUT_OF_BOUNDS);
    clear_ember_string_error();

    destroy_estring(str);
    destroy_estring(empty);
}
END_TEST

START_TEST(test_ember_string_strip)
{
    EmberString *empty = create_estring_from_cstr("", 0);
    EmberString *test1 = create_estring_from_cstr("\n \t\t\n \v\v\v TEST \n\v\v"
                                                 "\t \t  ", 23);
    EmberString *test2 = create_estring_from_cstr("\nTEST whitespace exists "
                                                 "inside \t\v END\t\t", 39);
    EmberString *test3 = create_estring_from_cstr("TEST 3", 6);

    EmberString *test_str = estring_strip(test1);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    ck_assert_ptr_nonnull(test_str);
    ck_assert_ptr_nonnull(test_str->c_str);
    ck_assert_ptr_ne(test_str, test1);
    ck_assert_ptr_ne(test_str->c_str, test1->c_str);
    ck_assert_int_eq(test_str->len, 4);
    ck_assert_str_eq(test_str->c_str, "TEST");
    destroy_estring(test_str);

    test_str = estring_strip(test2);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    ck_assert_ptr_nonnull(test_str);
    ck_assert_ptr_nonnull(test_str->c_str);
    ck_assert_ptr_ne(test_str, test2);
    ck_assert_ptr_ne(test_str->c_str, test2->c_str);
    ck_assert_int_eq(test_str->len, 36);
    ck_assert_str_eq(test_str->c_str, "TEST whitespace exists inside \t\v END");
    destroy_estring(test_str);

    test_str = estring_strip(test3);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    ck_assert_ptr_nonnull(test_str);
    ck_assert_ptr_nonnull(test_str->c_str);
    ck_assert_ptr_ne(test_str, test3);
    ck_assert_ptr_ne(test_str->c_str, test3->c_str);
    ck_assert_int_eq(test_str->len, test3->len);
    ck_assert_str_eq(test_str->c_str, "TEST 3");
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    destroy_estring(test_str);

    test_str = estring_strip(empty);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NO_ERR);
    ck_assert_ptr_nonnull(test_str);
    ck_assert_ptr_nonnull(test_str->c_str);
    ck_assert_ptr_ne(test_str, empty);
    ck_assert_ptr_ne(test_str->c_str, empty->c_str);
    ck_assert_int_eq(test_str->len, 0);
    ck_assert_str_eq(test_str->c_str, empty->c_str);
    destroy_estring(test_str);

    test_str = estring_strip(NULL);
    ck_assert_ptr_null(test_str);
    ck_assert_int_eq(ember_string_error(), EMBER_STRING_NULL_ARG);
    clear_ember_string_error();

    destroy_estring(test1);
    destroy_estring(test2);
    destroy_estring(test3);
    destroy_estring(empty);
}
END_TEST

Suite *ember_string_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Arraylist_New");

    /* Core Test Case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_ember_string_from_cstr);
    tcase_add_test(tc_core, test_ember_string_concat);
    tcase_add_test(tc_core, test_ember_substring);
    tcase_add_test(tc_core, test_ember_string_strip);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = ember_string_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
