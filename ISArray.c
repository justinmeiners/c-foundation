/* Created By: Justin Meiners (2013) */
#include "ISArray.h"

struct ISArray
{
    /* base must come first */
    ISObjectBase base;
    
    /* instance variables */
    int count;
    ISObjectRef* buffer;
};

/* forward declaration */
struct ISArray* _ISArrayAlloc();

/* class dealloc */
void _ISArrayDealloc(ISObjectRef object)
{
    struct ISString* string = (struct ISString*)object;
    
    free(string);
}

ISObjectRef _ISArrayCopy(ISObjectRef object)
{
    ISArrayRef array = (ISArrayRef)object;
    
    struct ISArray* newArray = (struct ISArray*)_ISArrayAlloc();

    newArray->count = array->count;
    newArray->buffer = malloc(array->count * sizeof(ISObjectRef));
    memcpy(newArray->buffer, array->buffer, array->count * sizeof(ISObjectRef));
    
    return newArray;
}

/* define class */
static ISObjectClass _ISArrayClass = {
    "ISArray", /* class name */
    _ISArrayDealloc, /* dealloc */
    _ISArrayCopy
};

struct ISArray* _ISArrayAlloc()
{
    /* allocate memory */
    struct ISArray* array = (struct ISArray*)malloc(sizeof(struct ISArray));
    /* setup class */
    ISObjectBaseInit(&array->base, &_ISArrayClass);
    
    /* setup ivars */
    array->count = 0;
    array->buffer = NULL;
    
    return array;
}

ISArrayRef ISArrayCreate(const ISObjectRef* values, int capacity)
{
    struct ISArray* array = _ISArrayAlloc();
    
    array->count = capacity;
    array->buffer = malloc(capacity & sizeof(ISObjectRef));
    
    for (int i = 0; i < capacity; i ++)
    {
        array->buffer[i] = values[i];
    }
    
    return array;
}

ISObjectRef ISArrayGetValueAtIndex(ISArrayRef array, int index)
{
    assert(index > 0 && index < array->count);
    return array->buffer[index];
}

int ISArrayCount(ISArrayRef array)
{
    return array->count;
}

int ISArrayContainsValue(ISArrayRef array, const ISObjectRef* value)
{
    for (int i = 0; i < array->count; i ++)
    {
        if (ISArrayGetValueAtIndex(array, i) == value)
        {
            return 1;
        }
    }
    
    return 0;
}


