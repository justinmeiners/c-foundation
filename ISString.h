/* Created By: Justin Meiners (2013) */
#ifndef IS_STRING_H
#define IS_STRING_H

#include "ISObject.h"

/* NOTE: this is a sample ISObject class, not a complete string implementation */

typedef enum
{
    ISASCIIStringEncoding = 0,
    
} ISStringEncoding;

typedef const struct ISString* ISStringRef;
typedef struct ISString* ISMutableStringRef;

/* static */
extern ISStringRef ISStringCreate(const char* cstring, ISStringEncoding encoding);
extern int ISStringLength(ISStringRef string);
extern const char* ISStringCString(ISStringRef string);

/* mutable */
extern ISMutableStringRef ISStringCreateMutable(const char* cstring, ISStringEncoding encoding);
extern void ISStringReplaceChar(ISMutableStringRef string, char character, char replacement);

#endif
