#include <stdlib.h>
#include <check.h>
#include <arraylist_new.h>

START_TEST(test_arraylist_int_create_destroy)
{
	size_t expected_size = sizeof(size_t)*3 + sizeof(int);
	int *array = NULL;
	array = init_arraylist(int);
	ck_assert_ptr_nonnull(array);
	ck_assert_uint_eq(arraylist_length(array), 100);
	ck_assert_uint_eq(arraylist_capacity(array), 2);
	ck_assert_uint_eq(arraylist_memory_footprint(array), 2+expected_size);

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
