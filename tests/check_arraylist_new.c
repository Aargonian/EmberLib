#include <arraylist_new.h>
#include "check_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <check.h>

START_TEST(test_arraylist_int_create_destroy)
{
    size_t expected_size = sizeof(size_t) * 3 + sizeof(int);
    int *array = NULL;
    array = init_arraylist(int);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), ARRAYLIST_DEFAULT_CAPACITY);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);
    ck_assert_int_eq(array[0], 0);

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}

END_TEST

START_TEST(test_arraylist_int_create_capacity)
{
    size_t capacity = 16;
    size_t expected_size = sizeof(size_t) * 3 + sizeof(int) * capacity;
    int *array = NULL;

    array = init_arraylist_with_capacity(int, capacity);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), capacity);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);

    for(size_t i = 0; i < capacity; i++)
        ck_assert_int_eq(array[0], 0);

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}

END_TEST

START_TEST(test_arraylist_char_ptr_create_destroy)
{
    size_t expected_size = sizeof(size_t) * 3 + sizeof(char *);
    char **array = NULL;

    array = init_arraylist(char *);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), ARRAYLIST_DEFAULT_CAPACITY);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);
    ck_assert_ptr_null(array[0]);

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}

END_TEST

START_TEST(test_arraylist_char_ptr_capacity_create_destroy)
{
    size_t capacity = 16;
    size_t expected_size = sizeof(size_t) * 3 + sizeof(char *) * capacity;
    char **array = NULL;

    array = init_arraylist_with_capacity(char *, capacity);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), capacity);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);

    for(size_t i = 0; i < capacity; i++)
    {
        ck_assert_ptr_null(array[i]);
    }

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}

END_TEST

START_TEST(test_arraylist_struct_create_destroy)
{
    emberlib_ck_enable_test_struct_testing();
    check_struct test_struct;

    //Initialize all members of our checked structure to 0 for later checking.
    check_struct check = {0};

    size_t expected_size = sizeof(size_t) * 3 + sizeof(test_struct);

    //Explicitly make the array null to begin with so we can make sure init works.
    check_struct *array = NULL;
    array = init_arraylist(check_struct);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), 1);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);

    //All members of the struct should be their equivalent of '0'
    printf("About to do the unthinkable.\n");
    emberlib_ck_assert_test_struct_equal(array, &check);

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_arraylist_struct_capacity_create_destroy)
{
    typedef struct
    {
        int x;
        double y;
        float z;
        char *arr;
        void *test;
        char s;
    } test_struct;

    size_t capacity = 16;
    size_t expected_size = sizeof(size_t) * 3 + sizeof(test_struct) * capacity;
    test_struct *array = NULL;

    array = init_arraylist_with_capacity(test_struct, capacity);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), capacity);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}

END_TEST

START_TEST(test_arraylist_int_push)
{
    int *array;
    const int SINGLE_PUSH_TEST_VALUE = 1;
    const int SINGLE_PUSH_TEST_VALUE_2 = 2;
    const int SINGLE_PUSH_TEST_VALUE_3 = 3;
    const int MULTI_PUSH_TEST_VALUES[] = {1, 2, 3, 4, 5, 6};
    const size_t MULTI_PUSH_LEN = 6;
    const size_t SINGLE_EXPECTED = sizeof(size_t) * 3 + sizeof(int);
    const size_t SINGLE_EXPECTED_2 = sizeof(size_t) * 3 + sizeof(int) * 2;
    const size_t SINGLE_EXPECTED_3 = sizeof(size_t) * 3 + sizeof(int) * 4;
    const size_t MULTI_EXPECTED = sizeof(size_t) * 3 + sizeof(int) * 16;

    array = init_arraylist(int);

    arraylist_push(array, SINGLE_PUSH_TEST_VALUE);
    ck_assert_int_eq(arraylist_length(array), 1);
    ck_assert_int_eq(arraylist_capacity(array), 1);
    ck_assert_int_eq(arraylist_memory_footprint(array), SINGLE_EXPECTED);

    arraylist_push(array, SINGLE_PUSH_TEST_VALUE_2);
    ck_assert_int_eq(arraylist_length(array), 2);
    ck_assert_int_eq(arraylist_capacity(array), 2);
    ck_assert_int_eq(arraylist_memory_footprint(array), SINGLE_EXPECTED_2);

    arraylist_push(array, SINGLE_PUSH_TEST_VALUE_3);
    ck_assert_int_eq(arraylist_length(array), 3);
    ck_assert_int_eq(arraylist_capacity(array), 4);
    ck_assert_int_eq(arraylist_memory_footprint(array), SINGLE_EXPECTED_3);

    for(size_t i = 0; i < MULTI_PUSH_LEN; i++)
    {
        arraylist_push(array, MULTI_PUSH_TEST_VALUES[i]);
    }
    ck_assert_int_eq(arraylist_length(array), 9);
    ck_assert_int_eq(arraylist_capacity(array), 16);
    ck_assert_int_eq(arraylist_memory_footprint(array), MULTI_EXPECTED);

    destroy_arraylist(array);
}

END_TEST

START_TEST(test_arraylist_str_push)
{
    char *to_push[9];
    to_push[0] = "This is Test String Number 1";
    to_push[1] = "This is Test String Number 2 a";
    to_push[2] = "This is Test String Number 3 ab";
    to_push[3] = "This is Test String Number 4 abc";
    to_push[4] = "This is Test String Number 5 abcd";
    to_push[5] = "This is Test String Number 6 abcde";
    to_push[6] = "This is Test String Number 7 abcdef";
    to_push[7] = "This is Test String Number 8 abcdefg";
    to_push[8] = "This is Test String Number 9 abcdefgh";

    size_t SINGLE_PUSH1_INDEX = 0;
    size_t SINGLE_PUSH1_LENGTH = 1;
    size_t SINGLE_PUSH1_CAPACITY = 1;
    size_t SINGLE_PUSH1_EXPECTED = sizeof(size_t) * 3 + sizeof(char *) * SINGLE_PUSH1_CAPACITY;

    size_t SINGLE_PUSH2_INDEX = 1;
    size_t SINGLE_PUSH2_LENGTH = 2;
    size_t SINGLE_PUSH2_CAPACITY = 2;
    size_t SINGLE_PUSH2_EXPECTED = sizeof(size_t) * 3 + sizeof(char *) * SINGLE_PUSH2_CAPACITY;

    size_t SINGLE_PUSH3_INDEX = 2;
    size_t SINGLE_PUSH3_LENGTH = 3;
    size_t SINGLE_PUSH3_CAPACITY = 4;
    size_t SINGLE_PUSH3_EXPECTED = sizeof(size_t) * 3 + sizeof(char *) * SINGLE_PUSH3_CAPACITY;

    size_t MULTI_PUSH_START_INDEX = SINGLE_PUSH3_INDEX + 1;
    size_t MULTI_PUSH_END_INDEX = 9;
    size_t MULTI_PUSH_CAPACITY = 16;
    size_t MULTI_PUSH_EXPECTED = sizeof(size_t) * 3 + sizeof(char *) * 16;

    char **string_list = init_arraylist(char *);

    arraylist_push(string_list, to_push[SINGLE_PUSH1_INDEX]);
    ck_assert_int_eq(arraylist_length(string_list), SINGLE_PUSH1_LENGTH);
    ck_assert_int_eq(arraylist_capacity(string_list), SINGLE_PUSH1_CAPACITY);
    ck_assert_int_eq(arraylist_memory_footprint(string_list), SINGLE_PUSH1_EXPECTED);
    ck_assert_str_eq(arraylist_get(string_list, SINGLE_PUSH1_INDEX, NULL), to_push[SINGLE_PUSH1_INDEX]);

    arraylist_push(string_list, to_push[SINGLE_PUSH2_INDEX]);
    ck_assert_int_eq(arraylist_length(string_list), SINGLE_PUSH2_LENGTH);
    ck_assert_int_eq(arraylist_capacity(string_list), SINGLE_PUSH2_CAPACITY);
    ck_assert_int_eq(arraylist_memory_footprint(string_list), SINGLE_PUSH2_EXPECTED);
    ck_assert_str_eq(arraylist_get(string_list, SINGLE_PUSH2_INDEX, NULL), to_push[SINGLE_PUSH2_INDEX]);

    arraylist_push(string_list, to_push[SINGLE_PUSH3_INDEX]);
    ck_assert_int_eq(arraylist_length(string_list), SINGLE_PUSH3_LENGTH);
    ck_assert_int_eq(arraylist_capacity(string_list), SINGLE_PUSH3_CAPACITY);
    ck_assert_int_eq(arraylist_memory_footprint(string_list), SINGLE_PUSH3_EXPECTED);
    ck_assert_str_eq(arraylist_get(string_list, SINGLE_PUSH3_INDEX, NULL), to_push[SINGLE_PUSH3_INDEX]);

    for(size_t i = MULTI_PUSH_START_INDEX; i < MULTI_PUSH_END_INDEX; i++)
    {
        arraylist_push(string_list, to_push[i]);
        ck_assert_str_eq(arraylist_get(string_list, i, NULL), to_push[i]);
    }

    ck_assert_int_eq(arraylist_length(string_list), MULTI_PUSH_END_INDEX);
    ck_assert_int_eq(arraylist_capacity(string_list), MULTI_PUSH_CAPACITY);
    ck_assert_int_eq(arraylist_memory_footprint(string_list), MULTI_PUSH_EXPECTED);

    destroy_arraylist(string_list);
}

END_TEST

START_TEST(test_arraylist_struct_push)
{
    emberlib_ck_enable_test_struct_testing();
    check_struct to_push[9];
    for(int i = 0; i < 9; i++)
    {
        init_test_struct(to_push + i, i);
    }

    size_t SINGLE_PUSH1_INDEX = 0;
    size_t SINGLE_PUSH1_LENGTH = 1;
    size_t SINGLE_PUSH1_CAPACITY = 1;
    size_t SINGLE_PUSH1_EXPECTED = sizeof(size_t) * 3 + sizeof(check_struct) * SINGLE_PUSH1_CAPACITY;

    size_t SINGLE_PUSH2_INDEX = 1;
    size_t SINGLE_PUSH2_LENGTH = 2;
    size_t SINGLE_PUSH2_CAPACITY = 2;
    size_t SINGLE_PUSH2_EXPECTED = sizeof(size_t) * 3 + sizeof(check_struct) * SINGLE_PUSH2_CAPACITY;

    size_t SINGLE_PUSH3_INDEX = 2;
    size_t SINGLE_PUSH3_LENGTH = 3;
    size_t SINGLE_PUSH3_CAPACITY = 4;
    size_t SINGLE_PUSH3_EXPECTED = sizeof(size_t) * 3 + sizeof(check_struct) * SINGLE_PUSH3_CAPACITY;

    size_t MULTI_PUSH_START_INDEX = SINGLE_PUSH3_INDEX + 1;
    size_t MULTI_PUSH_END_INDEX = 9;
    size_t MULTI_PUSH_CAPACITY = 16;
    size_t MULTI_PUSH_EXPECTED = sizeof(size_t) * 3 + sizeof(check_struct) * 16;

    check_struct *struct_list = init_arraylist(check_struct);

    arraylist_push(struct_list, to_push[SINGLE_PUSH1_INDEX]);
    ck_assert_int_eq(arraylist_length(struct_list), SINGLE_PUSH1_LENGTH);
    ck_assert_int_eq(arraylist_capacity(struct_list), SINGLE_PUSH1_CAPACITY);
    ck_assert_int_eq(arraylist_memory_footprint(struct_list), SINGLE_PUSH1_EXPECTED);
    emberlib_ck_assert_test_struct_equal(struct_list + SINGLE_PUSH1_INDEX, to_push + SINGLE_PUSH1_INDEX);

    arraylist_push(struct_list, to_push[SINGLE_PUSH2_INDEX]);
    ck_assert_int_eq(arraylist_length(struct_list), SINGLE_PUSH2_LENGTH);
    ck_assert_int_eq(arraylist_capacity(struct_list), SINGLE_PUSH2_CAPACITY);
    ck_assert_int_eq(arraylist_memory_footprint(struct_list), SINGLE_PUSH2_EXPECTED);
    emberlib_ck_assert_test_struct_equal(struct_list + SINGLE_PUSH2_INDEX, to_push + SINGLE_PUSH2_INDEX);

    arraylist_push(struct_list, to_push[SINGLE_PUSH3_INDEX]);
    ck_assert_int_eq(arraylist_length(struct_list), SINGLE_PUSH3_LENGTH);
    ck_assert_int_eq(arraylist_capacity(struct_list), SINGLE_PUSH3_CAPACITY);
    ck_assert_int_eq(arraylist_memory_footprint(struct_list), SINGLE_PUSH3_EXPECTED);
    emberlib_ck_assert_test_struct_equal(struct_list + SINGLE_PUSH3_INDEX, to_push + SINGLE_PUSH3_INDEX);

    for(size_t i = MULTI_PUSH_START_INDEX; i < MULTI_PUSH_END_INDEX; i++)
    {
        arraylist_push(struct_list, to_push[i]);
        emberlib_ck_assert_test_struct_equal(struct_list + i, to_push + i);
    }

    ck_assert_int_eq(arraylist_length(struct_list), MULTI_PUSH_END_INDEX);
    ck_assert_int_eq(arraylist_capacity(struct_list), MULTI_PUSH_CAPACITY);
    ck_assert_int_eq(arraylist_memory_footprint(struct_list), MULTI_PUSH_EXPECTED);

    destroy_arraylist(struct_list);
}

END_TEST

START_TEST(test_arraylist_int_push_with_capacity)
{
    int *array = init_arraylist_with_capacity(int, 8);
    size_t expected_empty_memory = sizeof(size_t) * 3 + sizeof(int) * 8;
    size_t expected_expanded_memory = sizeof(size_t) * 3 + sizeof(int) * 16;

    ck_assert_int_eq(arraylist_length(array), 0);
    ck_assert_int_eq(arraylist_capacity(array), 8);
    ck_assert_int_eq(arraylist_memory_footprint(array), expected_empty_memory);

    arraylist_push(array, 1);
    arraylist_push(array, 1);
    arraylist_push(array, 1);

    ck_assert_int_eq(arraylist_length(array), 3);
    ck_assert_int_eq(arraylist_capacity(array), 8);
    ck_assert_int_eq(arraylist_memory_footprint(array), expected_empty_memory);

    arraylist_push(array, 2);
    arraylist_push(array, 3);
    arraylist_push(array, 4);
    arraylist_push(array, 5);
    arraylist_push(array, 6);

    ck_assert_int_eq(arraylist_length(array), 8);
    ck_assert_int_eq(arraylist_capacity(array), 8);
    ck_assert_int_eq(arraylist_memory_footprint(array), expected_empty_memory);

    arraylist_push(array, 9);
    ck_assert_int_eq(arraylist_length(array), 9);
    ck_assert_int_eq(arraylist_capacity(array), 16);
    ck_assert_int_eq(arraylist_memory_footprint(array), expected_expanded_memory);

    destroy_arraylist(array);
}

END_TEST

START_TEST(test_arraylist_get)
{
    int DEFAULT_VALUE = 0x7071996;
    int *array = init_arraylist(int);

    ck_assert_int_eq(arraylist_err, 0);

    int value = arraylist_get(array, -1, DEFAULT_VALUE);
    ck_assert_int_eq(value, DEFAULT_VALUE);
    ck_assert_int_eq(arraylist_err, AL_ERR_OUT_OF_BOUNDS);
    clear_arraylist_err();

    // A new arraylist with no pushes should have no (valid) element at index 0
    value = arraylist_get(array, 0, DEFAULT_VALUE);
    ck_assert_int_eq(value, DEFAULT_VALUE);
    ck_assert_int_eq(arraylist_err, AL_ERR_OUT_OF_BOUNDS);
    clear_arraylist_err();

    //Push an item, and slot 0 should no longer be invalid
    arraylist_push(array, 1);
    value = arraylist_get(array, 0, DEFAULT_VALUE);
    ck_assert_int_eq(value, 1);
    ck_assert_int_eq(arraylist_err, 0);

    //Although we have pushed something, slot 1 should still be an error.
    value = arraylist_get(array, 1, DEFAULT_VALUE);
    ck_assert_int_eq(value, DEFAULT_VALUE);
    ck_assert_int_eq(arraylist_err, AL_ERR_OUT_OF_BOUNDS);
    clear_arraylist_err();

    //Push a second thing and slot 1 should now be filled
    arraylist_push(array, 2);
    value = arraylist_get(array, 1, DEFAULT_VALUE);
    ck_assert_int_eq(value, 2);
    ck_assert_int_eq(arraylist_err, 0);

    //Push another value to make sure our capacity is higher than length
    arraylist_push(array, 3);
    value = arraylist_get(array, 2, DEFAULT_VALUE);
    ck_assert_int_eq(value, 3);
    ck_assert_int_eq(arraylist_err, 0);

    //Although capacity should now be 4, index 3 should still be an error.
    ck_assert_int_eq(arraylist_length(array), 3);
    ck_assert_int_eq(arraylist_capacity(array), 4);
    value = arraylist_get(array, 3, DEFAULT_VALUE);
    ck_assert_int_eq(value, DEFAULT_VALUE);
    ck_assert_int_eq(arraylist_err, AL_ERR_OUT_OF_BOUNDS);
    clear_arraylist_err();

    destroy_arraylist(array);
}

END_TEST

Suite *arraylist_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Arraylist_New");

    /* Core Test Case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_arraylist_int_create_destroy);
    tcase_add_test(tc_core, test_arraylist_int_create_capacity);
    tcase_add_test(tc_core, test_arraylist_char_ptr_create_destroy);
    tcase_add_test(tc_core, test_arraylist_char_ptr_capacity_create_destroy);
    tcase_add_test(tc_core, test_arraylist_struct_create_destroy);
    tcase_add_test(tc_core, test_arraylist_struct_capacity_create_destroy);
    tcase_add_test(tc_core, test_arraylist_int_push);
    tcase_add_test(tc_core, test_arraylist_str_push);
    tcase_add_test(tc_core, test_arraylist_struct_push);
    tcase_add_test(tc_core, test_arraylist_int_push_with_capacity);
    tcase_add_test(tc_core, test_arraylist_get);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = arraylist_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
