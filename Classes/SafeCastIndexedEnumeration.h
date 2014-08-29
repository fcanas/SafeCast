//
//  SafeCastIndexedEnumeration.h
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

#undef SAFE_CAST_TEST

#define SAFE_CAST_INDEXED_ENUMERATION [self enumerateObjectsAtIndexes:indexSet \
options:opts usingBlock:^SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE \
{if SAFE_CAST_TEST {block(obj, idx, stop);}}];

#define SAFE_CAST_INDEXES_OF_OBJECTS return [self indexesOfObjectsPassingTest:^SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE {\
return SAFE_CAST_TEST;}];

#pragma mark - Kind of Class
#undef SAFE_CAST_TEST
#define SAFE_CAST_TEST ([obj isKindOfClass:class])

- (void)safe_enumerateObjectsOfKind:(Class)class atIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)block
{SAFE_CAST_INDEXED_ENUMERATION}

- (NSIndexSet *)safe_indexesOfObjectsOfKind:(Class)class {SAFE_CAST_INDEXES_OF_OBJECTS}

#pragma mark - Protocols
#undef SAFE_CAST_TEST
#define SAFE_CAST_TEST ([obj conformsToProtocol:protocol])

- (void)safe_enumerateObjectsConformingToProtocol:(Protocol *)protocol atIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)block
{SAFE_CAST_INDEXED_ENUMERATION}

- (NSIndexSet *)safe_indexesOfObjectsConformingToProtocol:(Protocol *)protocol {SAFE_CAST_INDEXES_OF_OBJECTS}

#pragma mark - Selectors
#undef SAFE_CAST_TEST
#define SAFE_CAST_TEST ([obj respondsToSelector:selector])

- (void)safe_enumerateObjectsRespondingToSelector:(SEL)selector atIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE)block
{SAFE_CAST_INDEXED_ENUMERATION}

