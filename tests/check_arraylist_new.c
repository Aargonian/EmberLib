#include <stdlib.h>
#include <check.h>
#include <arraylist_new.h>

START_TEST(test_arraylist_int_create_destroy)
{
	size_t expected_size = sizeof(size_t)*3 + sizeof(int);
	int *array = NULL;
	array = init_arraylist(int);
	ck_assert_ptr_nonnull(array);
	ck_assert_uint_eq(arraylist_length(array), 0);
	ck_assert_uint_eq(arraylist_capacity(array), ARRAYLIST_DEFAULT_CAPACITY);
	ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);

	destroy_arraylist(array);
	ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_arraylist_int_create_capacity)
{
    size_t capacity = 16;
    size_t expected_size = sizeof(size_t)*3 + sizeof(int)*capacity;
    int *array = NULL;

    array = init_arraylist_with_capacity(int, capacity);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), capacity);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_arraylist_char_ptr_create_destroy)
{
    size_t expected_size = sizeof(size_t)*3 + sizeof(char *);
    char **array = NULL;

    array = init_arraylist(char *);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), ARRAYLIST_DEFAULT_CAPACITY);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_arraylist_char_ptr_capacity_create_destroy)
{
    size_t capacity = 16;
    size_t expected_size = sizeof(size_t)*3 + sizeof(char *)*capacity;
    char **array = NULL;

    array = init_arraylist_with_capacity(char *, capacity);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), capacity);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_arraylist_struct_create_destroy)
{
    typedef struct {
        int x;
        double y;
        float z;
        char *arr;
        void *test;
        char s;
    } test_struct;

    size_t expected_size = sizeof(size_t)*3 + sizeof(test_struct);
    test_struct *array = NULL;

    array = init_arraylist(test_struct);
    ck_assert_ptr_nonnull(array);
    ck_assert_uint_eq(arraylist_length(array), 0);
    ck_assert_uint_eq(arraylist_capacity(array), 1);
    ck_assert_uint_eq(arraylist_memory_footprint(array), expected_size);

    destroy_arraylist(array);
    ck_assert_ptr_null(array);
}
END_TEST

START_TEST(test_arraylist_struct_capacity_create_destroy)
{
    typedef struct {
        int x;
        double y;
        float z;
        char *arr;
        void *test;
        char s;
    } test_struct;

    size_t capacity = 16;
    size_t expected_size = sizeof(size_t)*3 + sizeof(test_struct)*capacity;
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
