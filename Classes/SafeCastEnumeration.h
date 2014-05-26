//
//  SafeCastEnumeration.h
//  Pods
//
//  Created by Fabian Canas on 2/15/14.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2014 Fabian Canas
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in
//  the Software without restriction, including without limitation the rights to
//  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
//  the Software, and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#define SAFE_CAST_PREFIX(objects, kind, opts) -(void)safe_enumerate ## objects ## kind opts usingBlock:(void(^)

#define SAFE_CAST_ENUMERATE(objects) block{[self enumerate ## objects ## UsingBlock: ^SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE {\
if SAFE_CAST_TEST {block(SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS);}}];}

#define SAFE_CAST_ENUMERATE_WITH_OPTIONS(objects) block{[self enumerate ## objects ## WithOptions: opts usingBlock:^SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE {\
if SAFE_CAST_TEST {block(SAFE_CAST_ENUMERATE_BLOCK_PARAMETERS);}}];}

#undef SAFE_CAST_TEST
#define SAFE_CAST_TEST ([obj isKindOfClass:class])

#ifdef SAFE_CAST_KEYED_ENUMERATION
SAFE_CAST_PREFIX(KeysAndObjects,OfKind:(Class)class,) SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)SAFE_CAST_ENUMERATE(KeysAndObjects)
SAFE_CAST_PREFIX(KeysAndObjects,OfKind:(Class)class,withOptions:(NSEnumerationOptions)opts) SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE) SAFE_CAST_ENUMERATE_WITH_OPTIONS(KeysAndObjects)
#else
SAFE_CAST_PREFIX(Objects,OfKind:(Class)class,) SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)SAFE_CAST_ENUMERATE(Objects)
SAFE_CAST_PREFIX(Objects,OfKind:(Class)class,withOptions:(NSEnumerationOptions)opts)SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)SAFE_CAST_ENUMERATE_WITH_OPTIONS(Objects)
#endif

#undef SAFE_CAST_TEST
#define SAFE_CAST_TEST ([obj conformsToProtocol:protocol])

#ifdef SAFE_CAST_KEYED_ENUMERATION
SAFE_CAST_PREFIX(KeysAndObjects,ConformingToProtocol:(Protocol*)protocol,) SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)SAFE_CAST_ENUMERATE(KeysAndObjects)
SAFE_CAST_PREFIX(KeysAndObjects,ConformingToProtocol:(Protocol*)protocol,withOptions:(NSEnumerationOptions)opts)SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)SAFE_CAST_ENUMERATE_WITH_OPTIONS(KeysAndObjects)
#else
SAFE_CAST_PREFIX(Objects,ConformingToProtocol:(Protocol*)protocol,) SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)SAFE_CAST_ENUMERATE(Objects)
SAFE_CAST_PREFIX(Objects,ConformingToProtocol:(Protocol*)protocol,withOptions:(NSEnumerationOptions)opts) SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)SAFE_CAST_ENUMERATE_WITH_OPTIONS(Objects)
#endif
