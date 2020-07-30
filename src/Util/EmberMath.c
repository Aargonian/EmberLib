#include <EmberLib/Util/EmberMath.h>

/* 
 * Actual function definitions are in macros, to easily type them for many types
 * o
 * Declarations are at the bottom.
 */
#define DEFINE_CLAMP_FUNC(TYPE, TYPE_AFFIX)                                \
    TYPE clamp##TYPE_AFFIX(TYPE value, TYPE lower_bound, TYPE upper_bound) \
    {                                                                      \
        if(value > lower_bound)                                            \
        {                                                                  \
            if(value < upper_bound)                                        \
            {                                                              \
                return value;                                              \
            }                                                              \
            return upper_bound;                                            \
        }                                                                  \
        return lower_bound;                                                \
    }

#define DEFINE_MAP_FUNC_BASE()                                             \
    double ratio = (double) (value - value_min) / (value_max - value_min); \
    double new_value = ratio * (target_max - target_min) + target_min;

#define DEFINE_MAP_INTEGER_FUNC(TYPE, TYPE_AFFIX)                    \
    TYPE map##TYPE_AFFIX(TYPE value, TYPE value_min, TYPE value_max, \
                         TYPE target_min, TYPE target_max)           \
    {                                                                \
        DEFINE_MAP_FUNC_BASE()                                       \
        return (TYPE)(new_value + 0.5);                              \
    }

#define DEFINE_MAP_FLOATING_FUNC(TYPE, TYPE_AFFIX)                   \
    TYPE map##TYPE_AFFIX(TYPE value, TYPE value_min, TYPE value_max, \
                         TYPE target_min, TYPE target_max)           \
    {                                                                \
        DEFINE_MAP_FUNC_BASE()                                       \
        return new_value;                                            \
    }

DEFINE_CLAMP_FUNC(uint8, u8)
DEFINE_CLAMP_FUNC(uint16, u16)
DEFINE_CLAMP_FUNC(uint32, u32)
DEFINE_CLAMP_FUNC(uint64, u64)
DEFINE_CLAMP_FUNC(int8, 8)
DEFINE_CLAMP_FUNC(int16, 16)
DEFINE_CLAMP_FUNC(int32, 32)
DEFINE_CLAMP_FUNC(int64, 64)
DEFINE_CLAMP_FUNC(float, f)
DEFINE_CLAMP_FUNC(double, d)

DEFINE_MAP_INTEGER_FUNC(uint8, u8)
DEFINE_MAP_INTEGER_FUNC(uint16, u16)
DEFINE_MAP_INTEGER_FUNC(uint32, u32)
DEFINE_MAP_INTEGER_FUNC(uint64, u64)
DEFINE_MAP_INTEGER_FUNC(int8, 8)
DEFINE_MAP_INTEGER_FUNC(int16, 16)
DEFINE_MAP_INTEGER_FUNC(int32, 32)
DEFINE_MAP_INTEGER_FUNC(int64, 64)
DEFINE_MAP_FLOATING_FUNC(float, f)
DEFINE_MAP_FLOATING_FUNC(double, d)
