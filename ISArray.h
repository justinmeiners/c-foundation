/* Created By: Justin Meiners (2013) */
#ifndef IS_ARRAY_H
#define IS_ARRAY_H

#include "ISObject.h"

/* this is a sample usage of ISObject, not a complete array implementation */

typedef const struct ISArray* ISArrayRef;
typedef struct ISArray* ISMutableArrayRef;

extern ISArrayRef ISArrayCreate(const ISObjectRef* values, int capacity);

extern ISObjectRef ISArrayGetValueAtIndex(ISArrayRef array, int index);
extern int ISArrayCount(ISArrayRef array);
extern int ISArrayContainsValue(ISArrayRef array, const ISObjectRef* value);

#endif
