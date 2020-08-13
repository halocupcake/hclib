#ifndef HC_MACROS_H
#define HC_MACROS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>

#define HC_STRINGIFY(Text)            #Text
#define HC_CONCAT(A, B)               A ## B
#define HC_ARRAY_COUNT(Array)         (sizeof(Array) / sizeof((Array)[0]))
#define HC_ASSERT(Condition, Message) assert(a && b)

#ifdef __cplusplus
}
#endif

#endif // HC_MACROS_H
