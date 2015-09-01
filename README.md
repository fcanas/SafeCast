# SafeCast

[![CI Status](http://img.shields.io/travis/fcanas/SafeCast.svg?style=flat)](https://travis-ci.org/fcanas/SafeCast)
[![Version](https://img.shields.io/cocoapods/v/SafeCast.svg?style=flat)](http://cocoadocs.org/docsets/SafeCast)
[![License](https://img.shields.io/cocoapods/l/SafeCast.svg?style=flat)](http://cocoadocs.org/docsets/SafeCast)
[![Platform](https://img.shields.io/cocoapods/p/SafeCast.svg?style=flat)](http://cocoadocs.org/docsets/SafeCast)
[![Coverage Status](https://coveralls.io/repos/fcanas/SafeCast/badge.svg?branch=build)](https://coveralls.io/r/fcanas/SafeCast?branch=build)

* Cast objects in Objective-C, not in C
* Enumerate objects in collections only if they're of a certain kind, or conform to a protocol
* Be Safe
* Be Concise

Objective-C is C, and C is perilous. Don't blindly cast objects. Use high-level language constructs that communicate intent, and write more readable code.

Conditional casting, not unlike Swift's `as?` operator:

```objc
NSMutableArray *mArray = [NSMutableArray safe_cast:array];
// `mArray` is nil if `array` is not a mutable array, or `array` if it is.
```

Conditionally execute code depending on whether an object is of a type, like Swift's `if let x = x as? Y` pattern"

```objc
@interface MyModel : NSObject {
    @property (nonatomic, copy) NSString *someProperty;
}

id object;

...

[MyModel safe_cast:object intoBlock:^(MyModel *object){
    // only executes if `object` is a kind of `MyClass`
    // within this scope `object` is recognized as a `MyClass`
    object.someProperty; // Perfectly safe!
}];
```

Or only call methods on collection members that can respond to the selector.

```objc
[array safe_makeObjectsSafelyPerformSelector:@selector(method)];
```

Or enumerate with a block on objects that are of a specific kind.

```objc
[array safe_enumerateObjectsOfKind:[MyClass class]
                        usingBlock:^(MyClass *obj, NSUInteger idx, BOOL *stop) {
                            [obj setNumber:@3];
                        }];
```

Or a protocol

```objc
[array safe_enumerateObjectsConformingToProtocol:@protocol(MyProtocol)
                                      usingBlock:^(id<MyProtocol> *obj, NSUInteger idx, BOOL *stop) {
                                          [obj setNumber:@3];
                                      }];
```

SafeCast has extensive coverage for conditional type-based enumeration on the standard Foundation collections: `NSArray`, `NSSet`, `NSDictionary`, and `NSOrderedSet`.

Due to complex memory ownership, `NSMapTable`, `NSHashTable`, and other collections are not supported.

## A Whole Library for _that_?

Well, first of all, it's _really_ small. The documentation in the headers is _much_ bigger than the code. And it's tested. You may not need it. But it has a lot of things going for it.

### Easy to integrate

SafeCast is available as a [CocoaPod](http://guides.cocoapods.org/using/getting-started.html).

```ruby
pod 'SafeCast'
```

### Be concise and direct with your intent

It takes fewer lines of code than writing your own type checks. In my opinion it's easier to read and think about than the more verbose way of doing it safely. It keeps your type-safety checks up front and at a high level.

### Be Safe

Maybe you know what you're doing. But do you always do the right thing? How many people are in your code base? And how well do they all know Objective-C's C underbelly? More and more developers are coming in having worked with higher-level or dynamic languages, and may not realize what's safe and what's not.

SafeCast wants to make it easier to safely cast ... to cast only when it's safe to do so.

## Status

Please send feedback, pull-requests, and coffee.

# License

```
Copyright (c) 2014-2015 Fabian Canas. All rights reserved.

This code is distributed under the terms and conditions of the MIT license.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
