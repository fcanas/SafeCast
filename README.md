# SafeCast

Safe casting for Objective-C

Objective-C is C, and C can be perilous. Don't blindly cast objects. Stick to high-level language features, and write more readable code.

Quite simply, you can do things like this:

```
NSMutableArray *mArray = [NSMutableArray cast:array];
// `mArray` is nil if `array` is not a mutable array, and is `array` if it is.
```

## A Whole Library for _that_?

Well, first of all, it's _really_ small. And tested. You may not need it. But it has a lot of things going for it.

### Easy to integrate 

When it's done, I'll release SafeCast as a [CocoaPod](http://guides.cocoapods.org/using/getting-started.html), and it'll be trivial to include in a project. Then it will be just as if it were an Objective-C language feature. For now, you'll have to tinker with it as a local pod (if you don't know, don't try).

### Be concice and direct with your intent

It definitely takes fewer lines of code. It's my opinion that it's easier to read and think about than the more verbose, safe way of doing it.

### Be Safe

Maybe you know what you're doing. But do you always do the right thing? Do you use `NSStringFromSelector` _every_ time you handle KVO strings? SafeCast wants to make it easier to safely cast.

But how many people are in your code base? And how well do they all know Objective-C's C underbelly? More and more developers are coming in having worked with higher-level or dynamic languages, and may not realize what's safe and what's not.

## Examples

Turn this

```
- (void)someMethod:(NSSet *)set
{
    // Do some stuff...
    [(NSMutableSet *)set addObject:@"name"];
    // Also, you should expect this to crash.
}
```

into this

```
- (void)someMethod:(NSSet *)set
{
    // Do some stuff...
    [[NSmutableSet cast:set] addObject:@"name"];
    // Won't crash! (also, doesn't add @"name" to the set if set isn't mutable)
}
```

Or turn this less hair-raising, but still tedious code

```
- (void)someMethodOnOneSet:(NSSet *)set1 andAnotherSet:(NSSet *)set2
{
    // Do some stuff...
    if ([set1 isKindOfClass:[NSMutableSet class]]) {
        NSMutableSet *mutableSet = (NSMutableSet *)set1;
        [mutableSet addObject:@"name"];
        [mutableSet intersectSet:set2];
    }
}
```

into this

```
- (void)someMethodOnOneSet:(NSSet *)set1 andAnotherSet:(NSSet *)set2
{
    // Do some stuff...
    NSMutableSet *mutableSet = [NSMutableSet cast:set1];
    [mutableSet addObject:@"name"];
    [mutableSet intersectSet:set2];
}
```

or this, depending on how much you like blocks

```
- (void)someMethodOnOneSet:(NSSet *)set1 andAnotherSet:(NSSet *)set2
{
    // Do some stuff...
    [NSMutableSet cast:set1 intoBlock:^(NSMutableSet *mutableSet) {
        [mutableSet addObject:@"name"];
        [mutableSet intersectSet:set2];
    }];
}
```

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/fcanas/safecast/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

