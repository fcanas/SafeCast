# SafeCast

[![CI Status](http://img.shields.io/travis/fcanas/SafeCast.svg?style=flat)](https://travis-ci.org/fcanas/SafeCast)

* Cast objects in Objective-C, not in C
* Enumerate objects in collections only if they're of a certain kind, or conform to a protocol
* Be Safe
* Be Concice

Objective-C is C, and C is perilous. Don't blindly cast objects. Stick to high-level language features, and write more readable code.

Quite simply, you can do things like this:

```
NSMutableArray *mArray = [NSMutableArray safe_cast:array];
// `mArray` is nil if `array` is not a mutable array, or `array` if it is.
```

Or only call methods on collection members that can respond to the selector.

```
[array safe_makeObjectsSafelyPerformSelector:@selector(method)];
```

Or enumerate with a block on objects that are of a specific kind.

```
[array safe_enumerateObjectsOfKind:[MyObject class]
                        usingBlock:^(MyObject *obj, NSUInteger idx, BOOL *stop) {
                            [obj setNumber:@3];
                        }];
```

Or a protocol

```
[array safe_enumerateObjectsConformingToProtocol:@protocol(MyProtocol)
                                      usingBlock:^(id<MyProtocol> *obj, NSUInteger idx, BOOL *stop) {
                                          [obj setNumber:@3];
                                      }];
```

SafeCast has quite a few methods like this, covering `NSArray`, `NSSet`, `NSDictionary`, and `NSOrderedSet`.

I doubt it would be a good idea to give coverage to collections like `NSMapTable` or `NSHashTable`, so that's not planned.

## A Whole Library for _that_?

Well, first of all, it's _really_ small. The documentation in the headers is _much_ bigger than the code. And it's tested. You may not need it. But it has a lot of things going for it.

### Easy to integrate 

When it's done, I'll release SafeCast as a [CocoaPod](http://guides.cocoapods.org/using/getting-started.html). Until the podspec is published, you'll have to include a reference to this repository directly in your Podfile:

```
pod 'SafeCase', git: 'https://github.com/fcanas/SafeCast.git'
```

### Be concice and direct with your intent

It definitely takes fewer lines of code. In my opinion it's easier to read and think about than the more verbose, way of doing it safely. It keeps your type-safety checks up front and at a high level.

### Be Safe

Maybe you know what you're doing. But do you always do the right thing? How many people are in your code base? And how well do they all know Objective-C's C underbelly? More and more developers are coming in having worked with higher-level or dynamic languages, and may not realize what's safe and what's not.

SafeCast wants to make it easier to safely cast ... to cast only when it's safe to do so.

## Status

Please send feedback, pull-requests, and coffee.
