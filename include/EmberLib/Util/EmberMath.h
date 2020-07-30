#ifndef EMBERLIB_EMBERMATH_H
#define EMBERLIB_EMBERMATH_H

#include <EmberLib/Util/EmberDefines.h>

/* Generic functions in use. C11 Required! */
// clang-format off
#define clamp(X, Y, Z) \
    _Generic((X), \
        uint8:  clampu8,\
        uint16: clampu16,\
        uint32: clampu32,\
        uint64: clampu64,\
        int8:   clamp8,\
        int16:  clamp16,\
        int32:  clamp32,\
        int64:  clamp64,\
        float:  clampf,\
        double: clampd)(value, lower_bound, upper_bound)

#define map(VALUE, VALUE_MIN, VALUE_MAX, TARGET_MIN, TARGET_MAX) \
    _Generic((VALUE),\
            uint8:  mapu8,\
            uint16: mapu16,\
            uint32: mapu32,\
            uint64: mapu64,\
            int8:   map8,\
            int16:  map16,\
            int32:  map32,\
            int64:  map64,\
            float:  mapf,\
            double: mapd)(VALUE, VALUE_MIN, VALUE_MAX, TARGET_MIN, TARGET_MAX)
// clang-format on

/* Many redundant function definitions. Apologies in advance! */
uint8 clampu8(uint8 value, uint8 lower_bound, uint8 upper_bound);
uint16 clampu16(uint16 value, uint16 lower_bound, uint16 upper_bound);
uint32 clampu32(uint32 value, uint32 lower_bound, uint32 upper_bound);
uint64 clampu64(uint64 value, uint64 lower_bound, uint64 upper_bound);
int8 clamp8(int8 value, int8 lower_bound, int8 upper_bound);
int16 clamp16(int16 value, int16 lower_bound, int16 upper_bound);
int32 clamp32(int32 value, int32 lower_bound, int32 upper_bound);
int64 clamp64(int64 value, int64 lower_bound, int64 upper_bound);
float clampf(float value, float lower_bound, float upper_bound);
double clampd(double value, double lower_bound, double upper_bound);

uint8 mapu8(uint8 value, uint8 value_min, uint8 value_max, uint8 target_max, uint8 target_min);
uint16 mapu16(uint16 value, uint16 value_min, uint16 value_max, uint16 target_max, uint16 target_min);
uint32 mapu32(uint32 value, uint32 value_min, uint32 value_max, uint32 target_max, uint32 target_min);
uint64 mapu64(uint64 value, uint64 value_min, uint64 value_max, uint64 target_max, uint64 target_min);
int8 map8(int8 value, int8 value_min, int8 value_max, int8 target_max, int8 target_min);
int16 map16(int16 value, int16 value_min, int16 value_max, int16 target_max, int16 target_min);
int32 map32(int32 value, int32 value_min, int32 value_max, int32 target_max, int32 target_min);
int64 map64(int64 value, int64 value_min, int64 value_max, int64 target_max, int64 target_min);
float mapf(float value, float value_min, float value_max, float target_max, float target_min);
double mapd(double value, double value_min, double value_max, double target_max, double target_min);

#endif//EMBERLIB_EMBERMATH_H
