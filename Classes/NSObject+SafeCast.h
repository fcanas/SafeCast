//
//  NSObject+SafeCast.h
//  Pods
//
//  Created by Fabian Canas on 2/13/14.
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

#import <Foundation/Foundation.h>

/**
 Conditional casting into any class.

 This category facilitates conditional casting and code execution of objects.
 */
@interface NSObject (SafeCast)

/**
 Returns its parameter if it is of the callee's kind, i.e. a member or a member of a subclass.
 
 The following segments of code are equivalent, and are possible with any class that inherits from NSObject (almost all classes).

 @code
 NSMutableArray *ma;
 if ([a isKindOfClass:[NSMutableArray class]]) {
     ma = a;
 } else {
     ma = nil;
 }
 @endcode

 @code
 NSMutableArray *ma = [NSMutableArray cast:a];
 @endcode

 @param obj An object you would like to cast to the receiving class, only if it is safe to do so.
 @return The very same object passed as a parameter in a form recognized by the compiler to be an instance of the receiving class.
 */
+ (nullable instancetype)safe_cast:(nullable id)obj;

/**
 Executes a block with the passed object as a parameter only if the passed object is of the target class kind.

 @param obj An object you would like to cast to the receiving class, only if it is safe to do so.
 @param block A block that is executed only if the passed object is is an instance of the receiving class or its subclasses. Its parameter, while listed as @code id @/code, is guaranteed to be an instance of the receiving class.
 @return The very same object passed as a parameter in a form recognized by the compiler to be an instance of the receiving class.
 */
+ (nullable instancetype)safe_cast:(nullable id)obj intoBlock:(nonnull void(^)(__nonnull id))block;

@end
