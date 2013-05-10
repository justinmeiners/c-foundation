/*
 By: Justin Meiners
 
 Copyright (c) 2015 Justin Meiners
 Licensed under the MIT license: http://www.opensource.org/licenses/mit-license.php
 */


#include <stdio.h>
#include "ISString.h"

int main(int argc, const char * argv[])
{
    ISAutoreleasePoolPush();

    /* create a mutable string */
    ISMutableStringRef mutableString = ISStringCreateMutable("hello world", ISASCIIStringEncoding);
    /* retain + 1 */
    ISRetain(mutableString);
    
    /* mutable string length */
    int length = ISStringLength(mutableString);
    printf("length %i\n", length);
    
    /* make a non mutable copy */
    ISStringRef otherString = ISCopy(mutableString);
    printf("%s\n", ISStringCString(otherString));
    ISRelease(otherString);
    

    /* replace chars, only works on mutable */
    ISStringReplaceChar(mutableString, 'l', 'x');

    printf("%s\n", ISStringCString(mutableString));
    
    /* release mutable string */
    ISRelease(mutableString);
    ISAutorelease(mutableString);

    ISAutoreleasePoolPop();

    return 0;
}

