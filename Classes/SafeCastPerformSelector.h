//
//  SafeCastPerformSelector.h
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

#undef SAFE_CAST_WITH_OBJECT
#undef SAFE_CAST_PERFORM
#define SAFE_CAST_PERFORM -(void)makeObjectsSafelyPerformSelector:(SEL)aSelector SAFE_CAST_WITH_OBJECT {\
if (aSelector == NULL) {[[[NSException alloc] initWithName:NSInvalidArgumentException \
reason:[NSString stringWithFormat: @"Selector passed to %@ must not be nil", NSStringFromSelector(_cmd)]\
userInfo:nil] raise];}\
[self enumerateObjectsUsingBlock:^SAFE_CAST_ENUMERATE_BLOCK_SIGNATURE {\
if ([obj respondsToSelector:aSelector]) {[obj performSelector:aSelector SAFE_CAST_WITH_OBJECT];}}];}

#undef SAFE_CAST_WITH_OBJECT
#define SAFE_CAST_WITH_OBJECT
SAFE_CAST_PERFORM

#undef SAFE_CAST_WITH_OBJECT
#define SAFE_CAST_WITH_OBJECT withObject:(id)anObject
SAFE_CAST_PERFORM
