# c-foundation

## About

This project provides a basic implementation of the C Object/Class system (think CGImageRef) found in Apple's Core Foundation and Core Graphics frameworks.

The object system used in these frameworks offers several key features that can be a big help in building a great C API.

* Memory management with reference counting.
* Full object encapsulation. (Clean headers!)
* Mutable and immutable objects.
* Polymorphic methods for core operations (retain, release, autorelease, copy, etc).

## Example 

A simplified string and array class are included to demonstrate the object system.

```C

// Create a mutable object
ISMutableStringRef mutable = ISStringCreateMutable("a mutable string", ISASCIIStringEncoding);
ISStringRef string = ISStringCreate("a static string", ISASCIIStringEncoding);

// functions work on both mutable and nonmutable objects
int stringLength = ISStringLength(string);

int length = ISStringLength(mutable);

// certain functions only work on mutable objects
ISStringReplaceCharacters(mutable, 's', 'q');

// release
ISRelease(string);

```

## Project License

MIT License

Copyright (c) 2017 Justin Meiners

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
