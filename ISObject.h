/* Created By: Justin Meiners (2013) */
#ifndef IS_OBJECT_H
#define IS_OBJECT_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef const void* ISObjectRef;

typedef struct
{
    /* this could also include functions for comparison, hashing, 
     or whatever core functionality objects required */
    const char* _name;
    void (*_deallocFunc)(ISObjectRef object);
    ISObjectRef (*_copyFunc)(ISObjectRef object);
} ISObjectClass;


/* C Standard 
 A pointer to a structure object, suitably converted, points to its initial member and vice versa.
 
 This allows the ISObjectBase to be accessible from any struct that contains it as the first member.
 */

typedef struct
{
    /* this structure must be the first item in every ISObject */
    int retainCount;
    ISObjectClass* objectClass;
} ISObjectBase;

extern void ISObjectBaseInit(ISObjectBase* base, ISObjectClass* objClass);
extern int ISObjectRetainCount(ISObjectRef object);

/* +1 retain count */
extern ISObjectRef ISRetain(ISObjectRef object);

/* -1 retain count, calls objects dealloc method when retainCount < 1 */
extern void ISRelease(ISObjectRef object);

/* adds the object to the current autorelease pool, object will be released when the pool is destroyed */
extern ISObjectRef ISAutorelease(ISObjectRef object);

extern ISObjectRef ISCopy(ISObjectRef object);

/* adds a new pool to the stack */
extern void ISAutoreleasePoolPush();

/* removes a pool from the stack releasing all objects */
extern void ISAutoreleasePoolPop();

#endif
