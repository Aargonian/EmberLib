/*
 * Created by Aaron Helton on 11/24/19.
 */
#include <check.h>
#include <string.h>

#define __EL_MAX_MESSAGE_LENGTH 512

/* Should be at the beginning of any test that needs to test structs */
#define emberlib_ck_enable_test_struct_testing()\
char __emberlib_struct_test_msg[__EL_MAX_MESSAGE_LENGTH]

/*
 * Macro in the style of Check so that it integrates easily and no mistakes are
 * accidentally made.
 */
#define emberlib_ck_assert_test_struct_equal(X, Y)\
memset(__emberlib_struct_test_msg, 0,\
       __EL_MAX_MESSAGE_LENGTH*sizeof(char));\
ck_assert_msg(struct_equal((X), (Y), __emberlib_struct_test_msg),\
              __emberlib_struct_test_msg)

/*
 * Simple struct defining many types for testing the arraylist on structs
 */
typedef struct
{
    char _test_char;
    unsigned char _test_unsigned_char;
    short _test_short;
    unsigned short _test_unsigned_short;
    int _test_int;
    unsigned int _test_unsigned_int;
    long _test_long;
    unsigned long _test_unsigned_long;
    long long _test_long_long;
    unsigned long long _test_unsigned_long_long;
    float _test_float;
    double _test_double;
    long double _test_long_double;
    char *_test_str;
    void *_test_void_ptr;
} check_struct;

void init_test_struct(check_struct *cs, size_t index);
int struct_equal(check_struct *cs, check_struct *other, char *msg);

