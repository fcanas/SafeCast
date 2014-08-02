# SafeCast

[![CI Status](http://img.shields.io/travis/fcanas/SafeCast.svg?style=flat)](https://travis-ci.org/fcanas/SafeCast)

* Cast objects in Objective-C, not in C
* Enumerate objects in collections only if they're of a certain kind, or conform to a protocol
* Be Safe
* Be Concice

Objective-C is C, and C is perilous. Don't blindly cast objects. Stick to high-level language features, and write more readable code.

Quite simply, you can do things like this:

```
NSMutableArray *mArray = [NSMutableArray cast:array];
// `mArray` is nil if `array` is not a mutable array, or `array` if it is.
```

Or only call methods on collection members that can respond to the selector.

```
[array makeObjectsSafelyPerformSelector:@selector(method)];
```

Or enumerate with a block on objects that are of a specific kind.

```
[array enumerateObjectsOfKind:[MyObject class]
                   usingBlock:^(MyObject *obj, NSUInteger idx, BOOL *stop) {
                       [obj setNumber:@3];
                   }]
```

Or a protocol

```
[array enumerateObjectsConformingToProtocol:@protocol(MyProtocol)
                                 usingBlock:^(id<MyProtocol> *obj, NSUInteger idx, BOOL *stop) {
                                     [obj setNumber:@3];
                                 }]
```

SafeCast has quite a few methods like this, covering `NSArray`, `NSSet`, `NSDictionary`, and `NSOrderedSet`.

I doubt it would be a good idea to give coverage to collections like `NSMapTable` or `NSHashTable`.

## A Whole Library for _that_?

Well, first of all, it's _really_ small. The documentation in the headers is _much_ bigger than the code. And it's tested. You may not need it. But it has a lot of things going for it.

### Easy to integrate 

When it's done, I'll release SafeCast as a [CocoaPod](http://guides.cocoapods.org/using/getting-started.html), and it'll be trivial to include in a project. Then it will be just as if it were an Objective-C language feature. For now, you'll have to tinker with it as a local pod (if you don't know, don't try).

### Be concice and direct with your intent

It definitely takes fewer lines of code. It's my opinion that it's easier to read and think about than the more verbose, safe way of doing it. It keeps your safety concerns and checks up front and at a high level.

### Be Safe

Maybe you know what you're doing. But do you always do the right thing? Do you use `NSStringFromSelector` _every_ time you handle KVO strings? SafeCast wants to make it easier to safely cast.

But how many people are in your code base? And how well do they all know Objective-C's C underbelly? More and more developers are coming in having worked with higher-level or dynamic languages, and may not realize what's safe and what's not.

## Status

It works. It's usable and stable. But I want to get some feedback on it before pushing out version 0.0.1 on CocoaPods. Method signatures _will_ change. 

### TODO

* Methods on categories in a reusable libarary should be namespaced. I haven't done that yet.

Please send feedback, pull-requests, and coffee.
