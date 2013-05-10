/* Created By: Justin Meiners (2013) */
#include "ISString.h"
#include <string.h>

struct ISString
{
    /* base must come first */
    ISObjectBase base;
    
    /* instance variables */
    char* buffer;
    ISStringEncoding enconding;
};

/* forward declaration */
struct ISString* _ISStringAlloc();

/* class dealloc */
void _ISStringDealloc(ISObjectRef object)
{
    struct ISString* string = (struct ISString*)object;

    free(string->buffer);
    free(string);
}

ISObjectRef _ISStringCopy(ISObjectRef object)
{
    ISStringRef string = object;
    
    struct ISString* newString = _ISStringAlloc();
    newString->buffer = malloc(strlen(string->buffer) + 1);
    strcpy(newString->buffer, string->buffer);
    newString->enconding = string->enconding;
    
    return newString;
}

/* define class */
static ISObjectClass _ISStringClass = {
    "ISString", /* class name */
    _ISStringDealloc, /* dealloc */
    _ISStringCopy
};


struct ISString* _ISStringAlloc()
{
    /* allocate memory */
    struct ISString* string = (struct ISString*)malloc(sizeof(struct ISString));
    /* setup class */
    ISObjectBaseInit(&string->base, &_ISStringClass);
    
    /* setup ivars */
    string->buffer = NULL;
    
    return string;
}


ISStringRef ISStringCreate(const char* cstring, ISStringEncoding encoding)
{
    return ISStringCreateMutable(cstring, encoding);
}

int ISStringLength(ISStringRef string)
{
    return (int)strlen(string->buffer);
}

const char* ISStringCString(ISStringRef string)
{
    return string->buffer;
}

ISMutableStringRef ISStringCreateMutable(const char* cstring, ISStringEncoding encoding)
{
    struct ISString* string = (struct ISString*)_ISStringAlloc();
    string->enconding = encoding;
    
    string->buffer = malloc(strlen(cstring) + 1);
    strcpy(string->buffer, cstring);
    
    return string;
}

void ISStringReplaceChar(ISMutableStringRef string, char character, char replacement)
{
    char* i = string->buffer;
    
    while (*i != '\0')
    {
        if (*i == character)
        {
            *i = replacement;
        }
        i++;
    }
}

