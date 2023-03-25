#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity)                                                \
  ((capacity) < 8 ? (size_t)8 : (size_t)(capacity)*2)
#define GROW_ARRAY(type, pointer, oldCount, count)                             \
  (type *)reallocate(pointer, (size_t)sizeof(type) * (oldCount),               \
                     (size_t)sizeof(type) * (count))

#define FREE_ARRAY(type, pointer, oldCount)                                    \
  reallocate(pointer, sizeof(type) * (oldCount), 0)

void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif
