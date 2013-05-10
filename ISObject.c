/* Created By: Justin Meiners (2013) */
#include "ISObject.h"

struct ISAutoreleasePool
{
    ISObjectRef* objectBuffer;
    int bufferSize;
    int objectCount;
};

#define MAX_AUTORELEASE_STACK_DEPTH 128
#define START_AUTORELEASE_BUFFER_SIZE 256

static struct ISAutoreleasePool _poolStatck[MAX_AUTORELEASE_STACK_DEPTH];
static int _poolDepth = 0;

void ISAutoreleasePoolPush()
{
    _poolDepth++;
    assert(_poolDepth < MAX_AUTORELEASE_STACK_DEPTH);
    
    _poolStatck[_poolDepth].bufferSize = START_AUTORELEASE_BUFFER_SIZE;
    _poolStatck[_poolDepth].objectBuffer = malloc(sizeof(ISObjectRef) * _poolStatck[_poolDepth].bufferSize);
    _poolStatck[_poolDepth].objectCount = 0;
}

void ISAutoreleasePoolPop()
{
    struct ISAutoreleasePool* pool = &_poolStatck[_poolDepth];
    
    int i;
    for (i = 0; i < pool->objectCount; i ++)
    {
        ISRelease(pool->objectBuffer[i]);
    }
    
    free(pool->objectBuffer);
    _poolDepth--;
    assert(_poolDepth >= 0);
}

static void _ISAutorelease(struct ISAutoreleasePool* pool, ISObjectRef object)
{
    /* no autorelease pool */
    assert(_poolDepth > 0);
    
    if (pool->objectCount + 1 >= pool->bufferSize)
    {
        pool->bufferSize = ((pool->bufferSize + 1) * 3) / 2;
        pool->objectBuffer = realloc(pool->objectBuffer, sizeof(ISObjectRef) * pool->bufferSize);
    }
    
    pool->objectBuffer[pool->objectCount] = object;
    pool->objectCount++;
}

void ISObjectBaseInit(ISObjectBase* base, ISObjectClass* objClass)
{
    base->retainCount = 1;
    base->objectClass = objClass;
}

ISObjectRef ISRetain(ISObjectRef object)
{
    if (!object)
    {
        return NULL;
    }
    
    ISObjectBase* base = (ISObjectBase*)object;
    base->retainCount++;
    return object;
}

void ISRelease(ISObjectRef object)
{
    if (object)
    {
        ISObjectBase* base = (ISObjectBase*)object;
        base->retainCount--;
        
        if (base->retainCount < 1)
        {
            base->objectClass->_deallocFunc(object);
        }
    }
}

ISObjectRef ISAutorelease(ISObjectRef object)
{
    if (object)
    {        
        _ISAutorelease(&_poolStatck[_poolDepth], object);
    }
    
    return object;
}

int ISObjectRetainCount(ISObjectRef object)
{
    if (!object)
    {
        return 0;
    }
    
    ISObjectBase* base = (ISObjectBase*)object;
    return base->retainCount;
}

ISObjectRef ISCopy(ISObjectRef object)
{
    if (!object)
    {
        return NULL;
    }
    
    ISObjectBase* base = (ISObjectBase*)object;
    return base->objectClass->_copyFunc(object);
}
