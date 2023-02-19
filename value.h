#ifndef clox_value_h
#define clox_value_h

#include "common.h"

// Abstract data type for values. Allows the implementation to be independent of
// the underlying representation.
typedef double Value;

typedef struct {
    int capacity;
    int count;
    Value *values;
} ValueArray;

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);
void printValue(Value value);

#endif