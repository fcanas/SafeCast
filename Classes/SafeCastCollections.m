//
//  SafeCastCollections.m
//  Pods
//
//  Created by Fabian Canas on 2/15/14.
//
//

#import "SafeCastCollections.h"

@implementation NSArray (SafeCast)

#pragma mark - Responds to Selector

- (void)makeObjectsSafelyPerformSelector:(SEL)aSelector;
{
    if (aSelector == NULL) {
        [[[NSException alloc] initWithName:NSInvalidArgumentException reason:@"A selector passed to -makeObjectsSafelyPerformSelector: must not be nil" userInfo:nil] raise];
    }
    
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj respondsToSelector:aSelector]) {
            [obj performSelector:aSelector];
        }
    }];
}

- (void)makeObjectsSafelyPerformSelector:(SEL)aSelector withObject:(id)anObject
{
    if (aSelector == NULL) {
        [[[NSException alloc] initWithName:NSInvalidArgumentException reason:@"A selector passed to -makeObjectsSafelyPerformSelector:withObject: must not be nil" userInfo:nil] raise];
    }
    
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj respondsToSelector:aSelector]) {
            [obj performSelector:aSelector withObject:anObject];
        }
    }];
}

#pragma mark - Kind of Class

- (void)enumerateObjectsOfKind:(Class)class usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
{
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj isKindOfClass:class]) {
            block(obj, idx, stop);
        }
    }];
}

- (void)enumerateObjectsOfKind:(Class)class withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
{
    [self enumerateObjectsWithOptions:opts usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj isKindOfClass:class]) {
            block(obj, idx, stop);
        }
    }];
}

- (void)enumerateObjectsOfKind:(Class)class AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
{
    [self enumerateObjectsAtIndexes:indexSet options:opts usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj isKindOfClass:class]) {
            block(obj, idx, stop);
        }
    }];
}

- (NSIndexSet *)indexesOfObjectsOfKind:(Class)class
{
    return [self indexesOfObjectsPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
        return [obj isKindOfClass:class];
    }];
}

#pragma mark Protocols

- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
{
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj conformsToProtocol:protocol]) {
            block(obj, idx, stop);
        }
    }];
}

- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol withOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
{
    [self enumerateObjectsWithOptions:opts usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj conformsToProtocol:protocol]) {
            block(obj, idx, stop);
        }
    }];
}

- (void)enumerateObjectsConformingToProtocol:(Protocol *)protocol AtIndexes:(NSIndexSet *)indexSet options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block
{
    [self enumerateObjectsAtIndexes:indexSet options:opts usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if ([obj conformsToProtocol:protocol]) {
            block(obj, idx, stop);
        }
    }];
}

- (NSIndexSet *)indexesOfObjectsConformingToProtocol:(Protocol *)protocol
{
    return [self indexesOfObjectsPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
        return [obj conformsToProtocol:protocol];
    }];
}

@end
